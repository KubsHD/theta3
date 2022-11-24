#include "ecs.h"

Entity* Scene::create(String name)
{
	auto ent = new Entity();
	ent->world = this;
	ent->name = name;

	m_entities.push_back(ent);
	
	return ent;
}

void Scene::update()
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

void Scene::render()
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

Scene::~Scene()
{
	for (Entity* ent : m_entities)
	{
		for (Component* comp : ent->m_components)
		{
			delete comp;
		}
		delete ent;
	}
}