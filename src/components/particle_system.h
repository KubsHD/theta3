/*****************************************************************//**
 * \file   particle_system.h
 * \brief  component responsible for creating particles
 * 
 * \date   January 2023
 *********************************************************************/
#pragma once 

#include <core/types.h>
#include <core/ecs.h>

#include <core/random.h>
#include <core/log.h>

#include <lib/glad/glad.h>
#include <main.h>


/// <summary>
/// particle shape
/// </summary>
enum class ParticleShape
{
	Rectangle,
	Circle,
	Triangle,
	Animation,
	Sprite
};


/// <summary>
/// particle properties
/// </summary>
struct ParticleProps
{
	/// <summary>
	/// position of the particle
	/// </summary>
	Vec2 Position;

	/// <summary>
	/// Lifetime of the particle
	/// </summary>
	float LifeTime;

	/// <summary>
	/// velocity of the particle
	/// </summary>
	Vec2 Velocity;
	
	/// <summary>
	/// color of the particle
	/// </summary>
	Vec3 Color;

	/// <summary>
	/// size of the particle
	/// </summary>
	Vec2 Size;
	
	/// <summary>
	/// shape of the particle
	/// </summary>
	ParticleShape Shape;
};

/// <summary>
/// class responsible for particle spawning
/// </summary>
class ParticleSystem : public Component
{
public:
	ParticleSystem() {
		m_particles.resize(1000);
	};

	void update() override
	{
		for (auto& p : m_particles)
		{
			if (p.Active == false)
				continue;

			if (p.RemainingLifeTime <= 0.0f)
			{
				p.Active = false;
				continue;
			}

			p.RemainingLifeTime -= get_delta();

			p.Position += p.Velocity;
			// rot maybe
		}
	};

	void render(Renderer* ren) override
	{
		if (!m_particle_vao)
		{
			// init particle
			float vertices[] = {
			 -0.5f, -0.5f, 0.0f,
			  0.5f, -0.5f, 0.0f,
			  0.5f,  0.5f, 0.0f,
			 -0.5f,  0.5f, 0.0f
			};

			glGenVertexArrays(1, &m_particle_vao);
			glBindVertexArray(m_particle_vao);

			GLuint vb, ib;
			
			glGenBuffers(1, &vb);
			glBindBuffer(GL_ARRAY_BUFFER, vb);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			int indices[] = {
				0, 1, 2, 2, 3, 0
			};
			
			glGenBuffers(1, &ib);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(0);

			m_ptl_shader = new Shader("particle");
		}

		// draw particle

		for (auto& p : m_particles)
		{
			if (!p.Active)
				continue;

			float life = p.RemainingLifeTime / p.LifeTime;
			glm::vec4 color = glm::vec4(p.Color, 1.0f);
			color.a *= life;

			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, Vec3(p.Position, 0.0f));
			model = glm::rotate(model, get_time(), Vec3(0, 0, 1));
			model = glm::scale(model, Vec3(p.Size, 1.0f));


			m_ptl_shader->set_uniform_vec4("u_color", color);

			ren->draw_vao(m_particle_vao, m_ptl_shader, model);

		}


	};

	/// <summary>
	/// this function emit particles
	/// </summary>
	/// <param name="prop">it's properties of particles</param>
	void emit(const ParticleProps& prop)
	{
		ParticleData& p = m_particles[m_idx];

		p.Shape = prop.Shape;
		p.Active = true;
		p.Position = prop.Position;

		p.LifeTime = prop.LifeTime;
		p.RemainingLifeTime = prop.LifeTime;

		p.Rotation = 0.0f;
		p.Velocity = prop.Velocity;
		p.Size = prop.Size;
		p.Color = prop.Color;

		m_idx = --m_idx % m_particles.size();
	}

private:
	/// <summary>
	/// Runtime particle data
	/// </summary>
	struct ParticleData {
		Vec2 Position;
		float LifeTime;
		Vec2 Velocity;
		Vec3 Color;
		Vec2 Size;
		ParticleShape Shape;
		float RemainingLifeTime;

		bool Active = false;
		float Rotation = 0.0f;
	};

	GLuint m_particle_vao = 0;

	/// <summary>
	/// particle data array
	/// </summary>
	Vector<ParticleData> m_particles;
	uint32_t m_idx = 999;

	/// <summary>
	/// shader for particle
	/// </summary>
	Shader* m_ptl_shader;
};