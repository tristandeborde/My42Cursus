#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aColor;

uniform mat4 model;
uniform mat4 perspective;
uniform mat4 view;
out vec3 ourColor;
out vec2 TexCoord;

void main()
{
    gl_Position = perspective * view * model * vec4(aPos, 1.0);
    ourColor = aColor;
    TexCoord = aTexCoord;
}