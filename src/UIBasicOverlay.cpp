#include "UIBasicOverlay.hpp"
#include "UIButton.hpp"
#include "UIManager.hpp"
#include "UIDebugConsole.hpp"
#include "EngineResources.hpp"
#include "EngineRenderer.hpp"
#include "EngineManager.hpp"
#include "Utilities.hpp"
#include <raylib.hpp>

UICoord UIBasicOverlay::GetPosition() {
	return { 0, 0 };
}
UICoord UIBasicOverlay::GetSize() {
	return { GetScreenWidth(), GetScreenHeight() };
}
std::string UIBasicOverlay::GetUIClass() {
	return "UIBasicOverlay";
}
void UIBasicOverlay::Render() {
	Font mainFont = EngineResources::GetFont("res/main.ttf");

	DrawTextEx(mainFont, Utilities::FormatText("SimpleSandbox, version: %d.%d.%d", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH).c_str(), { 10, 10 + 21 * 0 }, 16, 1.6f, WHITE);
	DrawTextEx(mainFont, Utilities::FormatText("Frame #%d, fps: %d", EngineRenderer::GetFrameCount(), GetFPS()).c_str(), { 10, 10 + 21 * 1 }, 16, 1.6f, WHITE);
	DrawTextEx(mainFont, ((EngineRenderer::IsGamePaused() ? "Game Paused. " : "") + UIManager::GetUIStatus()).c_str(), { 10, 10 + 21 * 2 }, 16, 1.6f, WHITE);

	for (int i = 0; i < elems.size(); i++) {
		elems[i]->Render();
	}
}

UIBasicOverlay::UIBasicOverlay() {
	elems = std::vector<UIElement*>();

	elems.push_back(new UIButton("Shutdown", { 10, 10 + 21 * 3 }, { 250, 20 }, [](UIButton*) {
		EngineManager::Shutdown();
	}));
	elems.push_back(new UIButton("Reload resources", { 10, 10 + 21 * 4 }, { 250, 20 }, [](UIButton*) {
		EngineResources::ReloadResources();
		UIManager::SetUIStatus("Resources had reloaded!");
	}));
	elems.push_back(new UIButton("Open debug console", { 10, 10 + 21 * 5 }, { 250, 20 }, [](UIButton*) {
		if (UIManager::FirstElementWithSpecies("DebugConsole")) return;

		UIManager::AddElement(new UIDebugConsole());
	}));
}