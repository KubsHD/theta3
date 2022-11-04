#pragma once

#include <core/types.h>

class Renderer;

class Component {
	friend class World;
	friend class Entity;
public:
	Component() {};
	Entity* entity;

	virtual void update() = 0;
	virtual void render(Renderer* ren) = 0;
};

class World final {
public:
	World() {};

	Entity* create();

	void update();
	void render(Renderer* ren);

	Vector<Entity*> entities;
};



class Entity final {
public:
	Entity() : position(0,0) {};

	Vec2 position;

	template<typename T>
	T* add(T&& comp = T());

	template<typename T>
	void add();

	template<typename T>
	T* get();

	void update();
	void render(Renderer* ren);

	Vector<Component*> components;
};

template<typename T>
T* Entity::add(T&& comp /*= T()*/)
{

	T* instance = new T();

	*instance = std::forward<T>(comp);

	instance->entity = this;

	components.push_back(instance);
	return instance;
}