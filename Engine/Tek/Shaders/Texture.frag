#version 460 core

#define M_PI 3.1415926535897932384626433832795

layout(binding = 5) uniform samplerCube skyboxCube;
layout(binding = 6) uniform samplerCube shadowCubes[10];

out vec4 FragColor;

in vec2 TexCoords;
in vec3 fragPosition;
in vec3 fragViewPos;
in vec4 fragLightSpacePos;

in vec3 T;
in vec3 N;

struct Light{
    //W = type
    vec4 position;
    //W = cutOff
    vec4 direction;
    //W = intensity
    vec4 lightColor;

    //directional light only
    mat4 projection;
    mat4 view;
};

layout(std140, binding = 1) buffer LightingBuffer {
    Light lights[];
};

uniform float constant = 1.0f;
uniform float linear = 0.14f;
uniform float quadratic = 0.07f;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_normal1;
uniform sampler2D texture_shininess1;
uniform sampler2D texture_metallic1;

uniform sampler2D shadowMap;

uniform float far_plane;

float AdditionalShadowCalculation(vec3 fragPos, Light light, int index){
    // get vector between fragment position and light position
    vec3 fragToLight = fragPos - light.position.xyz;
    // use the light to fragment vector to sample from the depth map
    float closestDepth = texture(shadowCubes[index], fragToLight).r;
    // it is currently in linear range between [0,1]. Re-transform back to original value
    closestDepth *= far_plane;
    // now get current linear depth as the length between the fragment and light position
    float currentDepth = length(fragToLight);
    // now test for shadows
    float bias = 0.05;
    float shadow = currentDepth -  bias > closestDepth ? 1.0 : 0.0;

    return shadow;
}

float MainShadowCalculation(vec4 fragPosLightSpace)
{
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords.xyz = projCoords.xyz * 0.5 + 0.5;
    float currentDepth = projCoords.z;
    float bias = max(0.005 * (1.0 - dot(normalize(N), normalize(lights[0].position.xyz-lights[0].direction.xyz))), 0.0005);

    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for (int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;

    if(projCoords.z > 1.0)
        shadow = 0.0;

    return shadow;
}

void main()
{
    vec3 fragNormal = normalize(N);
    vec3 fragTangent = normalize(T);
    fragTangent = normalize(fragTangent - dot(fragTangent, fragNormal) * fragNormal);
    vec3 fragBiTangent = cross(fragNormal, fragTangent);

    mat3 TBN = mat3(fragTangent, fragBiTangent, fragNormal);

    vec4 diffuseColor = texture(texture_diffuse1, TexCoords).xyzw;
    float shininess = texture(texture_shininess1, TexCoords).r;
    float metallic = texture(texture_metallic1, TexCoords).r;

    vec3 normal = texture(texture_normal1, TexCoords).rgb;
    normal.y * -1;
    normal = normalize(normal * 2.0 - 1.0);
    normal = normalize((TBN) * normal);

    if(diffuseColor.a < 0.7)
        discard;

    int pointLightCount = 0;
    vec4 finalColor = vec4(0);
    if(lights.length() == 0){
        FragColor = vec4(diffuseColor.xyz, diffuseColor.w);
        return;
    }
    for (int i = 0; i < lights.length(); i++) {
        if(lights[i].position.w == 0){
            // TODO: SPOT LIGHT CALCULATION
            vec3 lightDir   = normalize(lights[i].position.xyz - fragPosition);

            float theta = dot(lightDir, normalize(-lights[i].direction.xyz));

            if(theta > lights[i].direction.w)
            {
                float dis = abs(distance(fragPosition, lights[i].position.xyz));

                vec3 viewDir    = normalize(fragViewPos - fragPosition);
                vec3 halfwayDir = normalize(lightDir + viewDir);

                float spotEffect = smoothstep(0.9, 1.0, theta); // Gradual fade from 90% to 100%

                float diffuse = max(dot(normal, lightDir), 0.0);
                diffuse = diffuse / (constant + linear * dis + quadratic * dis * dis);
                float specular = pow(max(dot(normal, halfwayDir), 0.0), 10);
                specular = specular / (constant + linear * dis + quadratic * dis * dis);

                finalColor += ((diffuseColor * diffuse + diffuseColor * specular) * vec4(lights[i].lightColor.xyz,1)) * lights[i].lightColor.w * (spotEffect);
            }
        }
        else if(lights[i].position.w == 1){
            // TODO: DIRECTIONAL LIGHT CALCULATION
            vec3 lightDir = normalize(-lights[i].direction.xyz);

            vec3 halfwayDir = normalize(lightDir + 0);

            float diffuse = max(dot(normal, lightDir), 0.0);
            float specular = pow(max(dot(normal, halfwayDir), 0.0), 70);

            float shadow = MainShadowCalculation(fragLightSpacePos);

            finalColor += ((diffuseColor * diffuse + diffuseColor * specular) * vec4(lights[i].lightColor.xyz,1) * (1.0 - shadow)) * lights[i].lightColor.w;
        }
        else if(lights[i].position.w == 2){
            // TODO: AMBIENT LIGHT CALCULATION
            finalColor += diffuseColor * vec4(lights[i].lightColor.xyz,1) * lights[i].lightColor.w;
        }
        else if(lights[i].position.w == 3){
            // POINT LIGHT CALCULATION
            float disSquared = dot(fragPosition - lights[i].position.xyz, fragPosition - lights[i].position.xyz);
            float attenuation = pow(max(1.0 - (disSquared / (/*lights[i].radius * lights[i].radius*/800)), 0.0), 2.0) * lights[i].lightColor.w;

            if(attenuation > 0.0)
            {
                vec3 lightDir   = normalize(lights[i].position.xyz - fragPosition);
                vec3 viewDir    = normalize(fragViewPos - fragPosition);
                vec3 halfwayDir = normalize(lightDir + viewDir);

                vec3 specularColor = mix(vec3(0.04), diffuseColor.rgb, metallic);
                vec3 specular = specularColor * pow(max(dot(normal, halfwayDir), 0.0), max(shininess * 256.0, 0.0001));

                vec3 radiance = lights[i].lightColor.xyz * attenuation;
                vec3 diffuse = (vec3(1.0) - specular) * (1.0 - 0) * diffuseColor.xyz / M_PI;
                float NdotL = max(dot(normal, lightDir), 0.0);

                float shadow = AdditionalShadowCalculation(fragPosition, lights[i], pointLightCount++);

                finalColor += vec4((diffuse + specular) * (1-shadow) * radiance * NdotL, 1);
            }
        }
    }

    int skyboxMipMaps = textureQueryLevels(skyboxCube);

    if(skyboxMipMaps > 0){
        vec3 viewDir    = normalize(fragPosition - fragViewPos);
        vec3 samplingDir = normalize(reflect(-viewDir, normal));
        vec3 diffuse = textureLod(skyboxCube, samplingDir, 6).xyz;
        finalColor += vec4(diffuse, 1.0f); // = vec4(samplingDir, 1.0f);
    }

    finalColor += vec4(diffuseColor.xyz * 0.1f, 1);
    FragColor = vec4(finalColor.xyz, diffuseColor.w);

    //FragColor = vec4(skyboxMipMaps - 12);

//    float shadow = 1 - AdditionalShadowCalculation(fragPosition, lights[1].position.xyz, shadowCubes);
//    FragColor = vec4(shadow, shadow, shadow, 1.0f);
}