#include "EngineManager.hpp"
#include "EnginePropList.hpp"
#include "EngineLogger.hpp"
#include "EngineRenderer.hpp"
#include "EngineControls.hpp"
#include "Utilities.hpp"
#include <atomic>
#include <Windows.h>

static std::atomic_bool config_mutex;

bool EngineManager::initialized;
bool EngineManager::appRunning;
EnginePropList* EngineManager::config;
World* EngineManager::currentWorld;

void EngineManager::InitializeEngine() {
	if (!initialized) {
		initialized = true;
		appRunning = true;

		LoadConfig();
		EngineControls::LoadControls();

		currentWorld = new World("Noworld");

		EngineRenderer::CreateRenderThread();
	}
}
void EngineManager::LoadConfig() {
	try {
		std::string data = Utilities::ReadFile(GENERAL_CONFIG_PATH);
		config = new EnginePropList(data);

		EngineLogger::LogInfo("Successfully loaded config!");
	}
	catch (std::exception ex) {
		EngineLogger::LogInfo("Failed to load configuration!");
		Die("Failed to load configuration!");
	}
}
void EngineManager::SaveConfig() {
	try {
		config->UpdatePropList();
		std::string data = config->GetPropList();

		Utilities::WriteFile(GENERAL_CONFIG_PATH, data);

		EngineLogger::LogInfo("Successfully saved config!");
	}
	catch (std::exception ex) {
		EngineLogger::LogInfo("Failed to save configuration!");
		Die("Failed to save configuration!");
	}
}
void EngineManager::Die(std::string str) { // hehe
	MessageBoxA(0, str.c_str(), "Fatal Error", MB_OK | MB_ICONERROR);
	exit(EXIT_FAILURE);
}
World* EngineManager::GetCurrentWorld() {
	return currentWorld;
}
void EngineManager::SetCurrentWorld(World* world) {
	currentWorld = world;
}
bool EngineManager::IsAppRunning() {
	return appRunning;
}
void EngineManager::Shutdown() {
	EngineLogger::LogInfo("Shutting down...");
	SaveConfig();
	appRunning = false;
}
std::string EngineManager::GetConfigValue(std::string key) {
	while (config_mutex);
	config_mutex = true;
	std::string res = config->GetValue(key);
	config_mutex = false;
	return res;
}
std::string EngineManager::SetConfigValue(std::string key, std::string val) {
	while (config_mutex);
	config_mutex = true;
	std::string res = config->SetValue(key, val);
	config_mutex = false;
	return res;
}