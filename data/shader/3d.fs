#version 330 core
in vec2 vTexCoord;
		
uniform sampler2D u_tex;

uniform float u_opacity;

out vec4 FragColor;

void main()
{
	vec2 tex = vTexCoord;
	tex.y = -tex.y;
	FragColor = vec4(1.0f, 0.5f, 1.0f, 1.0f);
}
