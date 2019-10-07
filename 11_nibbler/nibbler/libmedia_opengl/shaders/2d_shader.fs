#version 330 core

in vec2 TexCoords;

uniform sampler2D diffuseTexture;

out vec4 FragColor;

void main()
{
	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);//texture(diffuseTexture, TexCoords);
}
