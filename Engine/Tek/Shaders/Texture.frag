#version 460 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 fragPosition;
in vec3 fragNormal;
in vec3 fragViewPos;

struct Light{
    //W = type
    vec4 position;
    //W = cutOff
    vec4 direction;
    //W = intensity
    vec4 lightColor;
};

layout(std140, binding = 1) buffer LightingBuffer {
    Light lights[];
};

uniform float constant = 1.0f;
uniform float linear = 0.14f;
uniform float quadratic = 0.07f;

uniform sampler2D texture1;

void main()
{
    vec3 fragNormal = normalize(fragNormal);
    vec4 diffuseColor = texture(texture1, TexCoords).xyzw;
    if(diffuseColor.a < 0.2)
        discard;
    vec4 finalColor = vec4(0);
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

                float diffuse = max(dot(fragNormal, lightDir), 0.0);
                diffuse = diffuse / (constant + linear * dis + quadratic * dis * dis);
                float specular = pow(max(dot(fragNormal, halfwayDir), 0.0), 10);
                specular = specular / (constant + linear * dis + quadratic * dis * dis);

                finalColor += ((diffuseColor * diffuse + diffuseColor * specular) * vec4(lights[i].lightColor.xyz,1)) * lights[i].lightColor.w * (spotEffect);
            }
        }
        else if(lights[i].position.w == 1){
            // TODO: DIRECTIONAL LIGHT CALCULATION
            vec3 lightDir = normalize(-lights[i].direction.xyz);

            vec3 halfwayDir = normalize(lightDir + 0);

            float diffuse = max(dot(fragNormal, lightDir), 0.0);
            float specular = pow(max(dot(fragNormal, halfwayDir), 0.0), 70);

            finalColor += ((diffuseColor * diffuse + diffuseColor * specular) * vec4(lights[i].lightColor.xyz,1)) * lights[i].lightColor.w;
        }
        else if(lights[i].position.w == 2){
            // TODO: AMBIENT LIGHT CALCULATION
            finalColor += diffuseColor * vec4(lights[i].lightColor.xyz,1) * lights[i].lightColor.w;
        }
        else if(lights[i].position.w == 3){
            // POINT LIGHT CALCULATION
            float dis = abs(distance(fragPosition, lights[i].position.xyz));

            vec3 lightDir   = normalize(lights[i].position.xyz - fragPosition);
            vec3 viewDir    = normalize(fragViewPos - fragPosition);
            vec3 halfwayDir = normalize(lightDir + viewDir);

            vec3 debugColor = fragNormal * 0.5 + 0.5;
            //finalColor.rgb += debugColor;

            float diffuse = max(dot(normalize(fragNormal), lightDir), 0.0);
            diffuse = diffuse / (constant + linear * dis + quadratic * dis * dis);
            float specular = pow(max(dot(normalize(fragNormal), halfwayDir), 0.0), 10);
            specular = specular / (constant + linear * dis + quadratic * dis * dis);

            finalColor += ((diffuseColor * diffuse + diffuseColor * specular) * vec4(lights[i].lightColor.xyz,1)) * lights[i].lightColor.w;
        }
    }

    FragColor = vec4(finalColor.xyz, diffuseColor.w);
}