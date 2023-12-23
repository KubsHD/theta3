#version 330 core

#define MAX_POINT_LIGHTS 50
#define MAX_SPOT_LIGHTS 50

in vec2 vTexCoord;
in vec2 FragPos;



struct PointLight {
	vec2 pos;
	float radius;
    vec3 color;
};

struct SpotLight {
	vec2 pos;
    vec2 direction;
	float angle;
    vec3 color;
};
		
uniform sampler2D u_tex;

uniform vec2 u_spritePos;
uniform vec2 u_spriteSize;

uniform float u_opacity;
layout (std140) uniform LightData
{
	PointLight u_pointLights[MAX_POINT_LIGHTS];
	SpotLight u_spotLights[MAX_SPOT_LIGHTS];
	vec4 u_pointLightAvailability[MAX_POINT_LIGHTS];
	vec4 u_spotLightAvailability[MAX_SPOT_LIGHTS];
};
uniform int u_pointLightCount;
uniform int u_spotLightCount;



uniform float u_ambientStrength;

out vec4 FragColor;

void main()
{
	vec2 tex = vTexCoord;
	tex.y = -tex.y;

	if (texture(u_tex, tex).a <= 0.0) {
		discard;
	}

	vec3 ambient = u_ambientStrength * vec3(1,1,1);
	vec3 sum;

	for (int i = 0; i < MAX_POINT_LIGHTS; i++)
	{
		PointLight light = u_pointLights[i];
        float light_dist = distance(FragPos, light.pos);

		if (u_pointLightAvailability[i].x == 0)
			continue;

        sum += ((1.0 - smoothstep(-0.2, light.radius, light_dist)) * light.color) * u_pointLightAvailability[i][0];
	}

	for (int i = 0; i < u_spotLightCount; i++)
	{
		SpotLight light = u_spotLights[i];

		float light_dist = distance(FragPos, light.pos);
		vec2 lightDir = normalize(light.pos - FragPos);

		float theta = dot(lightDir, light.direction);

	
		if (theta > light.angle)
		{
			float epsilon = light.angle - light.angle * 2;
			float intensity = clamp((theta - light.angle * 2) / epsilon, 0, 1);

			sum += ((1.0 - smoothstep(-0.2, 140, light_dist)) * light.color) * u_spotLightAvailability[i].x;
		}
	}

	vec3 final = (ambient + sum) * texture(u_tex, tex).xyz;
	FragColor = vec4(final, 1.0f);
}
