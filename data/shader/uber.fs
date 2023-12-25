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
	float angle;
	float radius;
	float width;
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

        sum += ((1.0 - smoothstep(-0.2, light.radius, light_dist)) * light.color) * u_pointLightAvailability[i][0];
	}

	for (int i = 0; i < MAX_SPOT_LIGHTS; i++)
	{
		SpotLight light = u_spotLights[i];

		float light_dist = distance(FragPos, light.pos);
		vec2 lightDir = normalize(light.pos - FragPos);

		float angleCosine = dot(lightDir, normalize(vec2(cos(radians(light.angle)), sin(radians(light.angle)))));

		if (light_dist < light.radius && angleCosine > cos(radians(light.width) / 2.0)) {
			sum += 1.0 - smoothstep(0.0, light.radius, light_dist);
		}
	}

	vec3 final = (ambient + sum) * texture(u_tex, tex).xyz;
	FragColor = vec4(final, 1.0f);
}
