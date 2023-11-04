#include "World.hpp"

World::World(std::string name) {
	this->entities = std::vector<WorldEntity*>();
	this->name = name;
}

std::string World::GetWorldName() {
	return this->name;
}
std::vector<WorldEntity*> World::GetWorldEntities() {
	return this->entities;
}
void World::AddWorldEntity(WorldEntity* entity) {
	for (int i = 0; i < this->entities.size(); i++) {
		if (this->entities[i] == entity) return;
	}
	this->entities.push_back(entity);
}
void World::RemoveWorldEntity(WorldEntity* entity) {
	auto iter = this->entities.begin();
	for (int i = 0; i < this->entities.size(); i++) {
		if (this->entities[i] == entity) {
			this->entities.erase(iter);
			return;
		}
		iter++;
	}
}
void World::RenderWorld() {
	for (int i = 0; i < this->entities.size(); i++) {
		WorldEntity* ent = this->entities[i];
		if (ent->IsRenderable() && ent->IsEnabled())
			ent->RenderEntity();
	}
}