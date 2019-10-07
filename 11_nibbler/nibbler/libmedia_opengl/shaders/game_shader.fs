#version 330 core

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;
in vec4 FragPosLightSpace;  

uniform sampler2D diffuseTexture;
uniform sampler2D shadowMap;
uniform vec3 pos;
uniform vec3 light_pos;

out vec4 FragColor;

float Shadow(vec4 fragPosLightSpace, float bias) {
	vec3 projCoords = fragPosLightSpace.xyz;
	projCoords = projCoords * 0.5 + 0.5;
	float closestDepth = texture(shadowMap, projCoords.xy).r;
	float currentDepth = projCoords.z;
	if(projCoords.z > 1.0)
        return 0.0;

	//return currentDepth - bias > closestDepth ? 1.0 : 0.0;
	//linearize with surrounding
	float shadow = 0.0;
	vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
	for(int x = -1; x <= 1; ++x)
	{
		for(int y = -1; y <= 1; ++y)
		{
			float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
			shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;        
		}    
	}
	shadow /= 9.0;
	return shadow;
}

void main()
{
	vec4 color = texture(diffuseTexture, TexCoords);
	vec3 lightColor = vec3(1.0);
	vec3 normal = normalize(Normal);

	vec3 ambient = 0.4 * lightColor;

	vec3 lightDir = normalize(light_pos - FragPos); 
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	vec3 viewDir = normalize(pos - FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 16.0);
    vec3 specular = spec * lightColor;  

	float bias = max(0.005 * (1.0 - dot(normal, lightDir)), 0.0005);
	float shadow  = Shadow(FragPosLightSpace, bias);

	vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * vec3(color);

	FragColor = vec4(lighting * vec3(color), color.a);
}
