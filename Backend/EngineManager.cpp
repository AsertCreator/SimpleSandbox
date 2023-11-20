#include "EngineManager.hpp"
#include "EnginePropList.hpp"
#include "EngineLogger.hpp"
#include "EngineRenderer.hpp"
#include "EngineControls.hpp"
#include "Utilities.hpp"
#include "Native.hpp"
#include <atomic>

#include "AllEntities.hpp"

static std::atomic_bool config_mutex;

bool EngineManager::initialized;
bool EngineManager::appRunning;
std::vector<WorldEntityRegistration> EngineManager::worldEntityReg;
EnginePropList* EngineManager::config;
World* EngineManager::currentWorld;

EXPORT void EngineManager::InitializeEngine() {
	if (!initialized) {
		initialized = true;
		appRunning = true;
		worldEntityReg = std::vector<WorldEntityRegistration>();

		LoadConfig();

		EngineRenderer::CreateRenderThread();
		EngineControls::LoadControls();

		worldEntityReg.push_back({ EntityCube::Class, EntityCube::Species, MAKER(EntityCube) });

		currentWorld = new World(Utilities::ReadFile("./res/maps/map_simple.ssm"));
	}
}
EXPORT void EngineManager::LoadConfig() {
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
EXPORT void EngineManager::SaveConfig() {
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
EXPORT void EngineManager::Die(std::string str) { // hehe
	Native::ShowMessageBox(str, "Fatal error", MB_ERROR);
	Native::ImmediatelyExit(EXIT_FAILURE);
}
EXPORT World* EngineManager::GetCurrentWorld() {
	return currentWorld;
}
EXPORT void EngineManager::SetCurrentWorld(World* world) {
	currentWorld = world;
}
EXPORT bool EngineManager::IsAppRunning() {
	return appRunning;
}
EXPORT void EngineManager::Shutdown() {
	EngineLogger::LogInfo("Shutting down...");
	SaveConfig();
	appRunning = false;

	Native::ImmediatelyExit(0);
}
EXPORT std::string EngineManager::GetConfigValue(std::string key) {
	while (config_mutex);
	config_mutex = true;
	std::string res = config->GetValue(key);
	config_mutex = false;
	return res;
}
EXPORT std::string EngineManager::SetConfigValue(std::string key, std::string val) {
	while (config_mutex);
	config_mutex = true;
	std::string res = config->SetValue(key, val);
	config_mutex = false;
	return res;
}
EXPORT void EngineManager::RegisterWorldEntity(std::string cl, std::string sp, WorldEntityRegistrationDelegate deleg) {
	if (IsWorldEntityRegistered(cl, sp)) return;

	worldEntityReg.push_back({ cl, sp, deleg });
}
EXPORT void EngineManager::UnregisterWorldEntity(std::string cl, std::string sp) {
	auto begin = worldEntityReg.begin();
	for (int i = 0; i < worldEntityReg.size(); i++) {
		auto reg = *begin;

		if (reg.Class == cl && reg.Species == sp) {
			worldEntityReg.erase(begin);
			return;
		}

		begin++;
	}
}
EXPORT bool EngineManager::IsWorldEntityRegistered(std::string cl, std::string sp) {
	auto begin = worldEntityReg.begin();
	for (int i = 0; i < worldEntityReg.size(); i++) {
		auto reg = *begin;

		if (reg.Class == cl && reg.Species == sp) {
			return true;
		}

		begin++;
	}
	return false;
}
EXPORT WorldEntity* EngineManager::MakeWorldEntity(std::string cl, std::string sp) {
	auto begin = worldEntityReg.begin();
	for (int i = 0; i < worldEntityReg.size(); i++) {
		auto reg = *begin;

		if (reg.Class == cl && reg.Species == sp) {
			return reg.Cctor();
		}

		begin++;
	}

	return 0;
}