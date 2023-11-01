#version 330 core
in vec2 vTexCoord;
in vec2 FragPos;
		
uniform sampler2D u_tex;

uniform vec2 u_spritePos;
uniform vec2 u_spriteSize;

uniform float u_opacity;

uniform vec2 u_lightPos;

out vec4 FragColor;


void main()
{
	vec2 tex = vTexCoord;


	vec3 light_color = vec3(0.902, 0.745, 0.035);

	vec3 ambient = 0.1 * vec3(1,1,1);

	float light_dist = distance(FragPos, u_lightPos);
	vec3 d = (1.0 - smoothstep(-0.2, 70, light_dist)) * light_color;

	vec3 final = (ambient + d) * texture(u_tex, tex).xyz;
	FragColor = vec4(final, 1.0f);
}
