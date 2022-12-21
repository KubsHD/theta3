#version 330 core

in vec2 vTexCoord;
		
uniform sampler2D u_tex;

uniform vec2 u_spritePos;
uniform vec2 u_spriteSize;

uniform float u_opacity;

out vec4 FragColor;

void main()
{
    vec2 center = vec2(0.5, 0.5);
    float radius = 0.5;

    float dist = distance(vTexCoord, center);

    if (dist > radius)
    {
        discard;
    }

    FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}