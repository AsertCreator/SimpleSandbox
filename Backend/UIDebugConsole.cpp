#include "UIDebugConsole.hpp"
#include "UIManager.hpp"
#include "UIButton.hpp"
#include "EngineManager.hpp"

std::string UIDebugConsole::GetUISpecies() {
	return "DebugConsole";
}

UIDebugConsole::UIDebugConsole() : UIWindow("Debug Console", { 150, 150 }, { 800, 600 }) {
	this->AddElement(new UIButton("Memory Leak (10 MB)", { 10 + 255 * 0, 10 + 25 * 0 }, { 250, 20 }, [](UIButton*) {
		malloc(10 * 1024 * 1024); // its useless
	}));
	this->AddElement(new UIButton("Memory Leak (100 MB)", { 10 + 255 * 0, 10 + 25 * 1}, { 250, 20 }, [](UIButton*) {
		malloc(100 * 1024 * 1024); // its useless
	}));
	this->AddElement(new UIButton("Memory Leak (1 GB)", { 10 + 255 * 0, 10 + 25 * 2 }, { 250, 20 }, [](UIButton*) {
		UIManager::MessageBox("You'd better not...", "Debug Console", true, [](int st) {
			if (st == 1)
				malloc(1024 * 1024 * 1024); // its useless
		});
	}));
	this->AddElement(new UIButton("Test Message Box", { 10 + 255 * 0, 10 + 25 * 3 }, { 250, 20 }, [](UIButton*) {
		UIManager::MessageBox("test test ets etstete defyehfehffhi help me its 9 p.m. i dont want to do this", "testing", true, [](int st) {
			UIManager::MessageBox("pressed thing is " + std::to_string(st), "testing", false, [](int st) {});
		});
	}));
	this->AddElement(new UIButton("Reload Map", { 10 + 255 * 0, 10 + 25 * 4 }, { 250, 20 }, [](UIButton*) {
	}));
}