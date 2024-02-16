#version 420 core
in vec2 vTexCoord;
in vec3 vNormal;
		
uniform sampler2D u_tex;

uniform float u_opacity;

out vec4 FragColor;

in vec3 FragPos;


void main()
{
	vec2 tex = vTexCoord;
	tex.y = -tex.y;

    float ambientStrength = 0.9;
    vec3 ambient = ambientStrength * vec3(0.5, 0.3, 0.1);

	vec3 norm = normalize(vNormal);
	vec3 lightDir = normalize(vec3(0.0, 0.0, 0.0) - FragPos);  

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * vec3(0.8, 0.7, 0.4);

	FragColor = vec4((ambient + diffuse) * texture(u_tex, vTexCoord).xyz, 1.0f);
}
