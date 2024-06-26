#version 330 core
layout(location = 0) in vec2 aPos;
		
uniform mat4 u_mvp;

void main()
{
	vTexCoord = aTexCoord;
	gl_Position = u_mvp * vec4(aPos.x, aPos.y, 0.0, 1.0);
}
