#version 330 core
layout (location = 0) in vec3 aPos;
precision highp float;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 TexCoords;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    TexCoords = vec3(aPos.x, aPos.y, -aPos.z);
}