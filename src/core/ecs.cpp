#include "ecs.h"

Entity* World::create(String name)
{
	auto ent = new Entity();
	ent->world = this;
	ent->name = name;

	m_entities.push_back(ent);
	
	return ent;
}

void World::update()
{
	for (auto ent : m_entities)
	{
		for (auto comp : ent->m_components)
		{
			if (comp->enabled)
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
			if (comp->enabled)
				comp->render(ren);
		}
	}
}

