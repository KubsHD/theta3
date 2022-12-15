#version 330 core



layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTexCoord;
		
uniform mat4 u_mvp;

out vec2 vTexCoord;

void main()
{
	vTexCoord = aTexCoord;
	gl_Position = u_mvp * vec4(aPos.x, aPos.y, 0.0, 1.0);
}