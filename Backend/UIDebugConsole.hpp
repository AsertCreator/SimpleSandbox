#pragma once
#include "UICommon.hpp"
#include "UIWindow.hpp"

class UIDebugConsole : public UIWindow {
public:
	std::string GetUISpecies() override;

	UIDebugConsole();
};