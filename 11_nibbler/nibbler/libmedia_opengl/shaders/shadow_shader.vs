#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

uniform sampler2D diffuseTexture;

uniform mat4 light_view;
uniform mat4 light_projection;
uniform mat4 model;
uniform vec3 size;

out vec3 FragPos;  

void main()
{
    vec4 color = texture(diffuseTexture, aTexCoords);

    if (color.a < 0.99) {
        gl_Position = vec4(1000.0, 1000.0, 1000.0, 1.0);
    } else {
        gl_Position = light_projection * light_view * model * vec4(size * aPos, 1.0);
    }
    FragPos = vec3(model * vec4(size * aPos, 1.0));
}