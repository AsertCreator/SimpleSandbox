#pragma once
#include "UIElement.hpp"
#include <raylib.hpp>

class UILabel : public UIElement {
public:
	std::string GetUIClass();
	void Render() override;

	UILabel(UICoord pos, std::string text);
};