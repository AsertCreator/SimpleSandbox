#pragma once
#include "Common.hpp"
#include "EnginePropList.hpp"
#include "World.hpp"

#define GENERAL_CONFIG_PATH "general.cfg"

typedef WorldEntity* (*WorldEntityRegistrationDelegate)();

typedef struct {
	std::string Class;
	std::string Species;
	WorldEntityRegistrationDelegate Cctor;
} WorldEntityRegistration;

class EngineManager {
public:
	static EXPORT void InitializeEngine();
	static EXPORT void LoadConfig();
	static EXPORT void SaveConfig();
	static EXPORT void Die(std::string str);
	static EXPORT World* GetCurrentWorld();
	static EXPORT void SetCurrentWorld(World* world);
	static EXPORT bool IsAppRunning();
	static EXPORT void Shutdown();
	static EXPORT std::string GetConfigValue(std::string key);
	static EXPORT std::string SetConfigValue(std::string key, std::string val);
	static EXPORT void RegisterWorldEntity(std::string cl, std::string sp, WorldEntityRegistrationDelegate deleg);
	static EXPORT void UnregisterWorldEntity(std::string cl, std::string sp);
	static EXPORT bool IsWorldEntityRegistered(std::string cl, std::string sp);
	static EXPORT WorldEntity* MakeWorldEntity(std::string cl, std::string sp);
private:
	static bool initialized;
	static bool appRunning;
	static std::vector<WorldEntityRegistration> worldEntityReg;
	static EnginePropList* config;
	static World* currentWorld;

	NO_CCTOR(EngineManager);
};