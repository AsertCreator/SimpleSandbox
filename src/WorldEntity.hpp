#pragma once
#include "Common.hpp"
#include <string>
#include <map>

class WorldEntity {
public:
	std::string GetName();
	void SetName(std::string name);
	bool IsEnabled();
	void SetEnabled(bool val);
	// entity property values are entity-specific
	std::string GetPropertyValue(std::string key);
	// entity property values are entity-specific
	std::string SetPropertyValue(std::string key, std::string value);
	// class properties are constant for all entities of the same class or species
	virtual std::string GetClassProperty(std::string key) = 0;
	virtual std::string GetEntityClass() = 0;
	virtual std::string GetEntitySpecies();
	virtual void RenderEntity() = 0;

	WorldEntity();
protected:
	std::string name;
	std::map<std::string, std::string> props;
	bool enabled;
};