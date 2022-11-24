#include "ecs.h"

Entity* Scene::create(String name)
{
	auto ent = new Entity();
	ent->world = this;
	ent->name = name;

	for (auto ent : m_entities)
		if (ent->name == name)
			throw std::invalid_argument("Entity with this name already exists!");

	m_entities.push_back(ent);
	
	return ent;
}

Entity* Scene::get(String name)
{
	for (auto ent : m_entities)
		if (ent->name == name)
			return ent;

	throw std::invalid_argument("Entity not found!");
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

Component::Component()
{

}

void Component::init()
{

}
