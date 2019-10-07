#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 view;
uniform vec3 pos;
uniform mat4 projection;
uniform mat4 light_view;
uniform vec3 light_pos;
uniform mat4 light_projection;
uniform mat4 model;
uniform vec3 size;

out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;  
out vec4 FragPosLightSpace;

void main()
{
    TexCoords = aTexCoords;
    gl_Position = projection * view * model * vec4(size * aPos, 1.0);
	Normal = mat3(transpose(inverse(model))) * aNormal;
	FragPos = vec3(model * vec4(size * aPos, 1.0));
	FragPosLightSpace = light_projection * light_view * vec4(FragPos, 1.0);
}


