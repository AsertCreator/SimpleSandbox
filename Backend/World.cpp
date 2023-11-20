#include "World.hpp"
#include "UIManager.hpp"
#include "EngineManager.hpp"
#include "EnginePropList.hpp"
#include "Utilities.hpp"

#include "EntityCube.hpp"

#include <raylib.hpp>

// very unpredictable help
World::World(std::string data) {
	this->entities = std::vector<WorldEntity*>();
	this->rawData = data;
	
	EnginePropList info(data);
	auto keys = info.GetKeys();

	std::vector<std::string> entityList = Utilities::Split(info.GetValue("map.entities"), ",");
	std::map<std::string, WorldEntity*> cached = std::map<std::string, WorldEntity*>();

	for (int i = 0; i < entityList.size(); i++) {
		auto entityName = entityList[i];
		auto entityClass = info.GetValue(entityName + "@class");
		auto entitySpecies = info.GetValue(entityName + "@species");
		auto entity = EngineManager::MakeWorldEntity(entityClass, entitySpecies);

		if (entity == 0) {
			UIManager::MessageBox("Loaded world has invalid data! Show more information?", "World loading error", true, [entityClass, entitySpecies](int c) {
				if (c == 1) {
					UIManager::MessageBox("Failed to load entity with class \"" + entityClass + "\" and species \"" + entitySpecies + "\"!", "World loading error", false, [](int) {});
				}
			});

			return;
		}

		entity->SetName(entityName);
		entities.push_back(entity);

		cached[entityName] = entity;
	}

	for (int i = 0; i < info.Size(); i++) {
		auto key = keys[i];
		auto ix = key.find("@");

		if (ix != std::string::npos) {
			auto name = key.substr(0, ix);
			auto entity = cached[name];

			auto propkey = key.substr(ix + 1);
			auto propval = info.GetValue(key);

			if (propkey == "class" || propkey == "species")
				continue;

			entity->SetPropertyValue(propkey, propval);
		}
	}
}

std::string World::GetWorldRawData() {
	return this->rawData;
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
		if (ent->IsEnabled()) {
			float sx = std::stof(ent->GetPropertyValue("entity.size.x"));
			float sy = std::stof(ent->GetPropertyValue("entity.size.y"));
			float sz = std::stof(ent->GetPropertyValue("entity.size.z"));

			float px = std::stof(ent->GetPropertyValue("entity.position.x"));
			float py = std::stof(ent->GetPropertyValue("entity.position.y"));
			float pz = std::stof(ent->GetPropertyValue("entity.position.z"));

			ent->RenderEntity();

			DrawCubeWires({ px, py, pz }, px, py, pz, { 255, 0, 0 });
		}
	}
}