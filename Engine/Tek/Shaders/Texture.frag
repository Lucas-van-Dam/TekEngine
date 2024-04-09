#version 460 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 fragPosition;
in vec3 fragNormal;
in vec3 fragViewDir;

struct Light{
    //W = innerCutOff
    vec4 position;
    //W = outerCutOff
    vec4 direction;
    //W = intensity
    vec4 lightColor;
};

layout(std140, binding = 1) buffer LightingBuffer {
    Light lights[];
};

uniform float constant = 0.5f;
uniform float linear = 0.3f;
uniform float quadratic = 0.1f;

uniform sampler2D texture1;

void main()
{
    vec3 diffuseColor = texture(texture1, TexCoords).xyz;
    vec3 finalColor = vec3(0);
    for (int i = 0; i < lights.length(); i++) {
        if(lights[i].position.w >= 0){
            // TODO: SPOT LIGHT CALCULATION
        }
        else if(lights[i].position.x > 1000000){
            // TODO: DIRECTIONAL LIGHT CALCULATION
            vec3 lightDir = normalize(-lights[i].direction.xyz);

            vec3 halfwayDir = normalize(lightDir + fragViewDir);

            float diffuse = max(dot(fragNormal, lightDir), 0.0);
            float specular = pow(max(dot(fragNormal, halfwayDir), 0.0), 70);

            finalColor += ((diffuseColor * diffuse + diffuseColor * specular) * lights[i].lightColor.xyz) * lights[i].lightColor.w;
        }
        else if(lights[i].position.y > 1000000){
            // TODO: AMBIENT LIGHT CALCULATION
            finalColor += diffuseColor * lights[i].lightColor.xyz * lights[i].lightColor.w;
        }
        else{
            float dis = abs(distance(fragPosition, lights[i].position.xyz));

            vec3 lightDir = normalize(lights[i].position.xyz - fragPosition);
            vec3 halfwayDir = normalize(lightDir + fragViewDir);

            float diffuse = max(dot(fragNormal, lightDir), 0.0);
            diffuse = diffuse / (constant + linear * dis + quadratic * dis * dis);
            float specular = pow(max(dot(fragNormal, halfwayDir), 0.0), 70);
            specular = specular / (constant + linear * dis + quadratic * dis * dis);

            finalColor += ((diffuseColor * diffuse + diffuseColor * specular) * lights[i].lightColor.xyz) * lights[i].lightColor.w;
    }
    }

    FragColor = vec4(finalColor, 1);
}