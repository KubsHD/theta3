#version 330 core
in vec2 vTexCoord;
in vec2 FragPos;

struct PointLight {
	vec2 pos;
    vec2 angle;
    vec2 width;
    vec3 color;
	float radius;
};

struct SpotLight {
	vec2 pos;
    vec3 color;
    float radius;
};
		
uniform sampler2D u_tex;

uniform vec2 u_spritePos;
uniform vec2 u_spriteSize;

uniform float u_opacity;

uniform vec2 u_lightPos;
uniform vec2 u_lightDirection;
uniform float u_lightAngle;

out vec4 FragColor;

void main()
{

	vec2 tex = vTexCoord;
	tex.y = -tex.y;

	if (texture(u_tex, tex).a <= 0.0) {
		discard;
	}

	// spot light
	if (false)
	{

		vec3 light_color = vec3(0.902, 0.745, 0.035);

		vec3 ambient = 0 * vec3(1,1,1);

		float light_dist = distance(FragPos, u_lightPos);
		vec3 d = (1.0 - smoothstep(-0.2, 70, light_dist)) * light_color;

		vec3 final = (ambient + d) * texture(u_tex, tex).xyz;
	}	

	vec3 light_color = vec3(0.902, 0.745, 0.035);

	vec3 ambient = 0.1 * vec3(1,1,1);

	float light_dist = distance(FragPos, u_lightPos);

	vec2 lightDir = normalize(u_lightPos - FragPos);
	

	float theta = dot(lightDir, u_lightDirection);

	vec3 d;
	
	if (theta > u_lightAngle)
	{
		float epsilon = u_lightAngle - u_lightAngle * 2;
		float intensity = clamp((theta - u_lightAngle * 2) / epsilon, 0, 1);

		d = (1.0 - smoothstep(-0.2, 140, light_dist)) * light_color;
		d *= intensity;
	}

	vec3 final = (ambient + d) * texture(u_tex, tex).xyz;


	FragColor = vec4(final, 1.0f);
}
