#include "ecs.h"

Entity* World::create()
{
	auto ent = new Entity();
	ent->world = this;

	m_entities.push_back(ent);
	
	return ent;
}

void World::update()
{
	for (auto ent : m_entities)
	{
		for (auto comp : ent->m_components)
		{
			if (!comp->enabled)
				return;

			comp->update();
		}
	}
}

void World::render(Renderer* ren)
{
	for (auto ent : m_entities)
	{
		for (auto comp : ent->m_components)
		{
			if (!comp->enabled)
				return;

			comp->render(ren);
		}
	}
}

template<typename T>
T* Entity::get()
{

}

