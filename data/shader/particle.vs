#version 330 core
layout(location = 0) in vec3 aPos;
		
uniform mat4 u_mvp;

void main()
{
	gl_Position = u_mvp * vec4(aPos.x, aPos.y, -10.0, 1.0);
}
