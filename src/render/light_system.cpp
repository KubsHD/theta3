#include "light_system.h"

#include <render/Shader.h>

void LightSystem::prepare_shader(Shader* m_uberShader)
{
	m_uberShader->set_uniform_float("u_ambientStrength", ambient_strength);

	//m_uberShader->set_uniform_float("pointLightCount", m_pointLightCount);
	//m_uberShader->set_uniform_float("spotLightCount", m_spotLightCount);
}

