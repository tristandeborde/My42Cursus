#version 330 core

in vec3 FragPos;

out vec4 FragColor;

void main()
{    
	FragColor = vec4(vec3(FragPos.z / 30 + 0.5), 1.0);
}  