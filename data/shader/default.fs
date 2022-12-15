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
	tex.y = -tex.y;
	FragColor = texture(u_tex, tex) * vec4(1.0f, 1.0f, 1.0f, u_opacity);
}
