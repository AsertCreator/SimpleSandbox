#include "EngineManager.hpp"
#include "EngineLogger.hpp"
#include <Windows.h>

int wWinMain(HINSTANCE hInstance, HINSTANCE, LPWSTR, int) {
	EngineLogger::LogInfo("Starting SimpleSandbox...");
	EngineManager::InitializeEngine();

	while (EngineManager::IsAppRunning()); // engine manager does everything

	EngineLogger::LogInfo("Everything is down, exiting...");

	return 0;
}
