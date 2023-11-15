#include "EntityCube.hpp"
#include <raylib.hpp>

std::string EntityCube::Class = "EntityCube";
std::string EntityCube::Species = "Default";

std::string EntityCube::GetClassProperty(std::string key) {
	return 0;
}
std::string EntityCube::GetEntityClass() {
	return Class;
}
void EntityCube::RenderEntity() {
	float sx = std::stof(GetPropertyValue("entity.size.x"));
	float sy = std::stof(GetPropertyValue("entity.size.y"));
	float sz = std::stof(GetPropertyValue("entity.size.z"));

	float px = std::stof(GetPropertyValue("entity.position.x"));
	float py = std::stof(GetPropertyValue("entity.position.y"));
	float pz = std::stof(GetPropertyValue("entity.position.z"));

	unsigned char cr = (unsigned char)std::stoi(GetPropertyValue("entity.color.r"));
	unsigned char cg = (unsigned char)std::stoi(GetPropertyValue("entity.color.g"));
	unsigned char cb = (unsigned char)std::stoi(GetPropertyValue("entity.color.b"));

	DrawCube({ px, py, pz }, sx, sy, sz, { cr, cg, cb, 255 });
}

EntityCube::EntityCube() {
	// um nothing
}