#include "EngineControls.hpp"
#include "EngineManager.hpp"

int EngineControls::KcPauseRendering;
int EngineControls::KcPauseGame;
int EngineControls::KcAbrutlyEnd;

void EngineControls::LoadControls() {
	KcPauseRendering = std::stoi(EngineManager::GetConfigValue("keyboard.controls.pauseRendering")); // should be F10
	KcPauseGame      = std::stoi(EngineManager::GetConfigValue("keyboard.controls.pauseGame"));      // should be F9
	KcAbrutlyEnd     = std::stoi(EngineManager::GetConfigValue("keyboard.controls.abruptlyEnd"));    // should be F8
}
void EngineControls::SaveControls() {
	EngineManager::SetConfigValue("keyboard.controls.pauseRendering", std::to_string(KcPauseRendering));
	EngineManager::SetConfigValue("keyboard.controls.pauseGame",      std::to_string(KcPauseGame));
	EngineManager::SetConfigValue("keyboard.controls.abruptlyEnd",    std::to_string(KcAbrutlyEnd));

	EngineManager::SaveConfig();
}