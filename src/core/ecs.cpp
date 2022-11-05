#include "ecs.h"

Entity* World::create()
{
	auto ent = new Entity();
	entities.push_back(ent);
	return ent;
}

void World::update()
{
	for (auto ent : entities)
	{
		for (auto comp : ent->components)
		{
			comp->update();
		}
	}
}

void World::render(Renderer* ren)
{
	for (auto ent : entities)
	{
		for (auto comp : ent->components)
		{
			comp->render(ren);
		}
	}
}

template<typename T>
void Entity::add()
{
	
}

template<typename T>
T* Entity::get()
{

}


void Entity::update()
{

}

void Entity::render(Renderer* ren)
{

}
