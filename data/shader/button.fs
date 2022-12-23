#version 330 core
in vec2 vTexCoord;
		
uniform sampler2D u_tex;

uniform vec2 u_spritePos;
uniform vec2 u_spriteSize;

uniform float u_opacity;

out vec4 FragColor;

void main()
{
	vec2 tex = vTexCoord;
	FragColor = vec4(0.3f, 0.3f, 0.3f, 1.0f);
}
