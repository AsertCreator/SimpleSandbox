#pragma once
#include "UIElement.hpp"
#include "EngineRenderer.hpp"
#include <functional>

class UIWindow : public UIElement {
public:
	void AddElement(UIElement* el);
	void RemoveElement(int eln);
	int GetElementCount();
	UIElement* GetElement(int eln);
	std::string GetUIClass();
	void Render() override;

	UIWindow(std::string text, UICoord pos, UICoord size);
private:
	std::vector<UIElement*> elem;
};