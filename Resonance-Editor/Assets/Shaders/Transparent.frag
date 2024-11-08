#version 460 core

#define NUM_LIGHTS 1

out vec4 FragColor;

in vec2 TexCoords;
in vec3 fragPosition;
in vec3 fragNormal;
in vec3 fragViewDir;

struct Light{
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
    float intensity;
    vec3 lightColor;
};

uniform Light lights[NUM_LIGHTS];

uniform float constant = 0.5f;
uniform float linear = 0.3f;
uniform float quadratic = 0.1f;

uniform sampler2D texture1;

void main()
{
    vec3 diffuseColor = texture(texture1, TexCoords).xyz;
    for (int i = 0; i < NUM_LIGHTS; i++) {
        float dis = abs(distance(fragPosition, lights[i].position));

        vec3 lightDir = normalize(lights[i].position - fragPosition);
        vec3 halfwayDir = normalize(lightDir + fragViewDir);

        float diffuse = max(dot(fragNormal, lightDir), 0.0);
        diffuse = diffuse / (constant + linear * dis + quadratic * dis * dis);
        float specular = pow(max(dot(fragNormal, halfwayDir), 0.0), 70);
        specular = specular / (constant + linear * dis + quadratic * dis * dis);

        diffuseColor = diffuseColor * diffuse + diffuseColor * specular;
    }

    FragColor = vec4(diffuseColor, 1);
}