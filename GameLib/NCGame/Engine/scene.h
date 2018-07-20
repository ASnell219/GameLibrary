#pragma once
#include "id.h"
#include "engine.h"
#include <vector>

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
	void RemoveEntity(Entity* entity);

	Entity* FindEntity(const ID& id);

protected:
	std::vector<Entity*> m_entities;
};
