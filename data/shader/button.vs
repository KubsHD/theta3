#version 330 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTexCoord;
		
uniform mat4 u_mvp;
uniform float u_time;

float rand(vec2 co){
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}

vec2 diversify_vector(vec2 a)
{
	vec2 new;
	new.x = a.x > 0 ? a.x - 0.1 : a.x + 0.1;
	new.y = a.y > 0 ? a.y - 0.1 : a.y + 0.1;
	return new;
}

float gen_offset_sin() {
	return (rand(diversify_vector(aPos)) * sin(u_time * 15)) / 20;
}

float gen_offset_cos() {
	return (rand(diversify_vector(aPos)) * cos(u_time * 15)) / 20;
}

out vec2 vTexCoord;

void main()
{
	vTexCoord = aTexCoord;
	gl_Position = u_mvp * vec4( gen_offset_sin() + aPos.x, gen_offset_cos() + aPos.y, 0.0, 1.0);
}
