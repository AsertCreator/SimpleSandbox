#pragma once
#include "Common.hpp"
#include "WorldEntity.hpp"
#include <string>
#include <vector>

class World {
public:
	std::string GetWorldName();
	std::vector<WorldEntity*> GetWorldEntities();
	void AddWorldEntity(WorldEntity* entity);
	void RemoveWorldEntity(WorldEntity* entity);
	void RenderWorld();

	World(std::string name);
private:
	std::string name;
	std::vector<WorldEntity*> entities;
};