#version 330 core
in vec2 vTexCoord;
		
uniform vec3 u_color;
uniform float u_opacity;

out vec4 FragColor;

void main()
{
	FragColor = vec4(u_color, u_opacity);
}
