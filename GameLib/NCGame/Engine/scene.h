#pragma once
#include "id.h"
#include "engine.h"
#include <list>

class Entity;

class ENGINE_API Scene
{
public:
	Scene() {}
	~Scene() {}

	bool Initialize();
	void Shutdown();
	void Update();
	void Draw();

	void AddEntity(Entity* entity);
	void RemoveEntity(Entity* entity, bool destroy = true);

	Entity* FindEntity(const ID& id);

protected:
	std::list<Entity*> m_entities;
};
