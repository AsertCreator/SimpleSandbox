#pragma once
#include "UIElement.hpp"
#include "EngineRenderer.hpp"
#include <functional>

#define UIButton_Act 0x0100

class UIButton : public UIElement {
public:
	void Activate();
	bool GetEnabled();
	bool SetEnabled(bool e);
	void SetActivationEvent(std::function<void(UIButton*)> act);
	std::string GetUIClass();
	void Render() override;

	UIButton(std::string text, UICoord pos, UICoord size, std::function<void(UIButton*)> act);
private:
	std::function<void(UIButton*)> onActivate;
	bool isEnabled;
};