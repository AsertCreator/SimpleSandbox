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
	static void InitializeEngine();
	static void LoadConfig();
	static void SaveConfig();
	static void Die(std::string str);
	static World* GetCurrentWorld();
	static void SetCurrentWorld(World* world);
	static bool IsAppRunning();
	static void Shutdown();
	static std::string GetConfigValue(std::string key);
	static std::string SetConfigValue(std::string key, std::string val);
	static void RegisterWorldEntity(std::string cl, std::string sp, WorldEntityRegistrationDelegate deleg);
	static void UnregisterWorldEntity(std::string cl, std::string sp);
	static bool IsWorldEntityRegistered(std::string cl, std::string sp);
	static WorldEntity* MakeWorldEntity(std::string cl, std::string sp);
private:
	static bool initialized;
	static bool appRunning;
	static std::vector<WorldEntityRegistration> worldEntityReg;
	static EnginePropList* config;
	static World* currentWorld;

	NO_CCTOR(EngineManager);
};