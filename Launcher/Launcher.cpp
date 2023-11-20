#include "../Backend/EngineManager.hpp"
#include "../Backend/EngineLogger.hpp"
#include "../Backend/Utilities.hpp"
#include <Windows.h>

// this is the main launcher for ss.
// all the actual code is in backend.dll

int main() {
	EngineLogger::LogInfo(Utilities::FormatText("Starting SimpleSandbox, version %d.%d.%d", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH));
	EngineManager::InitializeEngine();

	while (EngineManager::IsAppRunning()); // engine manager does everything

	EngineLogger::LogInfo("Everything is down, exiting...");

	*((uint8_t*)0) = 0;

	return 0;
}
