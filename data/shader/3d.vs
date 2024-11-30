#version 410 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

layout(binding = 1) uniform SceneData
{
	uniform mat4 u_mvp;
	uniform mat4 u_model;
} sd;

out vec3 vNormal;
out vec2 vTexCoord;
out vec3 FragPos;


void main()
{
	vNormal = mat3(transpose(inverse(sd.u_model))) * aNormal;
	vTexCoord = aTexCoord;
	gl_Position = sd.u_mvp * vec4(aPos.x, aPos.y, aPos.z, 1.0);
	FragPos = vec3(sd.u_model * vec4(aPos, 1.0)).xyz;
}
