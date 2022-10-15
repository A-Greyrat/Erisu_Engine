#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec2 TexCoord;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 mainLightDir;
uniform vec3 mainLightColor;

vec3 TransformObjToWorldNormal(mat4 model, vec3 normal)
{
    return normalize(mat3(transpose(inverse(model))) * normal);
}

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    Normal = TransformObjToWorldNormal(model, aNormal);
    TexCoord = aTexCoord;
}