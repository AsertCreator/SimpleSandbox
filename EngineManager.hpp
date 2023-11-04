#pragma once
#include "Common.hpp"
#include "EnginePropList.hpp"
#include "World.hpp"

#define GENERAL_CONFIG_PATH "general.cfg"

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
private:
	static bool initialized;
	static bool appRunning;
	static EnginePropList* config;
	static World* currentWorld;

	NO_CCTOR(EngineManager);
};