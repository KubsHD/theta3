#version 330 core
in vec2 vTexCoord;
		
uniform vec3 u_color;
uniform float u_opacity;
uniform sampler2D u_tex;
uniform sampler2D u_tex2;
uniform float u_time;

out vec4 FragColor;

void main()
{
	float noiseValue = texture(u_tex, (vTexCoord + vec2(0, u_time * 0.5))).x;

	float gradientValue = texture(u_tex2, vTexCoord).x;

	vec3 a = vec3(1,1,1);
	vec3 b = vec3(.7,.7,.7);
	vec3 dark = vec3(.4,.4,.4);

	float step1 = step(noiseValue, gradientValue);
	float step2 = step(noiseValue, gradientValue-0.2);
	float step3 = step(noiseValue, gradientValue-0.4);

	vec4 c = vec4(mix(a,dark,step2-step1), step1);

	//c.xyz = mix(c.xyz, b, step2 - step3);

	FragColor = c;
}