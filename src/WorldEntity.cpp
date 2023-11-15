#include "WorldEntity.hpp"

std::string WorldEntity::GetName() {
	return this->name;
}
void WorldEntity::SetName(std::string name) {
	this->name = name;
}
std::string WorldEntity::GetPropertyValue(std::string key) {
	return this->props[key];
}
std::string WorldEntity::SetPropertyValue(std::string key, std::string value) {
	this->props[key] = value;
	return this->props[key];
}
bool WorldEntity::IsEnabled() {
	return this->enabled;
}
void WorldEntity::SetEnabled(bool val) {
	enabled = val;
}
std::string WorldEntity::GetEntitySpecies() {
	return "Default";
}

WorldEntity::WorldEntity() {
	this->name = "";
	this->props = std::map<std::string, std::string>();
	this->enabled = true;
}