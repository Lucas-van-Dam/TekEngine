#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 fragPosition;
out vec3 fragNormal;
out vec3 fragViewPos;

void main()
{
    TexCoords = aTexCoords;
    fragPosition = vec3(model * vec4(aPos, 1.0));
    fragNormal = normalize(mat3(transpose(inverse(model))) * aNormal);
    fragViewPos = vec3(inverse(view)[3]);
    gl_Position = projection * view * vec4(fragPosition, 1.0);
}