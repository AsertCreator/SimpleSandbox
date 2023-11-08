#pragma once
#include "UICommon.hpp"
#include "UIElement.hpp"
#include <vector>

class UIBasicOverlay : public UIElement {
public:
	UICoord GetPosition() override;
	UICoord GetSize() override;
	std::string GetUIClass();
	void Render() override;

	UIBasicOverlay();
private:
	std::vector<UIElement*> elems;
};