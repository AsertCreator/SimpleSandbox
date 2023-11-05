#include "EngineManager.hpp"
#include "EngineLogger.hpp"
#include "Utilities.hpp"
#include <Windows.h>

int main() {
	EngineLogger::LogInfo(Utilities::FormatText("Starting SimpleSandbox, version %d.%d.%d", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH));
	EngineManager::InitializeEngine();

	while (EngineManager::IsAppRunning()); // engine manager does everything

	EngineLogger::LogInfo("Everything is down, exiting...");

	return 0;
}
