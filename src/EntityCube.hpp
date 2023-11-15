#pragma once
#include "WorldEntity.hpp"

class EntityCube : public WorldEntity {
public:
	static std::string Class;
	static std::string Species;

	std::string GetClassProperty(std::string key);
	std::string GetEntityClass();
	void RenderEntity();

	EntityCube();
};