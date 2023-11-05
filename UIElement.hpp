#pragma once
#include "UICommon.hpp"
#include <string>

class UIElement {
public:
	virtual std::string GetUIClass() = 0;
	virtual std::string GetUIText();
	virtual std::string SetUIText(std::string text);
	virtual UICoord GetPosition();
	virtual UICoord SetPosition(UICoord c);
	virtual UICoord GetSize();
	virtual UICoord SetSize(UICoord c);
	virtual void Render();
protected:
	UICoord defPosition;
	UICoord defSize;
	std::string defText;
};