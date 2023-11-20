#pragma once
#include "Common.hpp"
#include "WorldEntity.hpp"
#include <string>
#include <vector>

class World {
public:
	std::string GetWorldRawData();
	std::vector<WorldEntity*> GetWorldEntities();
	void AddWorldEntity(WorldEntity* entity);
	void RemoveWorldEntity(WorldEntity* entity);
	void RenderWorld();

	World(std::string data);
private:
	std::string rawData;
	std::vector<WorldEntity*> entities;
};