#include "UIDebugConsole.hpp"
#include "UIManager.hpp"
#include "UIButton.hpp"

UIDebugConsole::UIDebugConsole() : UIWindow("Debug Console", { 150, 150 }, { 800, 600 }) {
	this->AddElement(new UIButton("Memory Leak (10 MB)", { 10, 10 + 25 * 0 }, { 250, 20 }, [](UIButton*) {
		malloc(10 * 1024 * 1024); // its useless
	}));
	this->AddElement(new UIButton("Memory Leak (100 MB)", { 10, 10 + 25 * 1}, { 250, 20 }, [](UIButton*) {
		malloc(100 * 1024 * 1024); // its useless
	}));
	this->AddElement(new UIButton("Memory Leak (1 GB)", { 10, 10 + 25 * 2 }, { 250, 20 }, [](UIButton*) {
		malloc(1024 * 1024 * 1024); // its useless
	}));
	this->AddElement(new UIButton("Test Message Box", { 10, 10 + 25 * 3 }, { 250, 20 }, [](UIButton*) {
		UIManager::MessageBox("test test ets etstete defyehfehffhi help me its 9 p.m. i dont want to do this", "testing", true, [](int st) {
			UIManager::MessageBox("pressed thing is " + std::to_string(st), "testing", false, [](int st) {});
		});
	}));
}