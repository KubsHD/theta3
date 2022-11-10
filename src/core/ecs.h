#pragma once

#include <core/types.h>

class Renderer;

class Component {
	friend class World;
	friend class Entity;
public:
	Component() {};

	Entity* entity;
	bool enabled = true;

	virtual void update() = 0;
	virtual void render(Renderer* ren) = 0;
};

class World final {
public:
	World() {};

	Entity* create(String name);

	void update();
	void render(Renderer* ren);

private:
	Vector<Entity*> m_entities;
};



class Entity final {

	friend class World;

public:
	Entity() : position(100,100) {};

	String name;

	Vec2 position;
	World* world;

	template<typename T>
	T* add(T&& comp = T());

	template<typename T>
	T* get()
	{
		T* m = nullptr;

		for (auto& comp : m_components)
		{
			if (m = dynamic_cast<T*>(comp))
				return m;
		}

		throw std::runtime_error("Component not found!");
		return nullptr;
	};

private:
	Vector<Component*> m_components;
};

template<typename T>
T* Entity::add(T&& comp /*= T()*/)
{
	T* instance = new T();

	*instance = std::forward<T>(comp);

	instance->entity = this;

	m_components.push_back(instance);
	return instance;
}