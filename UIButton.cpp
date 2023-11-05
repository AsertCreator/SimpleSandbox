#include "UIButton.hpp"
#include "EngineResources.hpp"
#include <raylib.hpp>

void UIButton::Activate() {
	onActivate(this);
}
bool UIButton::GetEnabled() {
	return isEnabled;
}
bool UIButton::SetEnabled(bool e) {
	isEnabled = e;
	return isEnabled;
}
void UIButton::SetActivationEvent(std::function<void(UIButton*)> act) {
	onActivate = act;
}
std::string UIButton::GetUIClass() {
	return "UIButton";
}
void UIButton::Render() {
	Font fnt = EngineResources::GetFont("res/main.ttf");
	float width = MeasureTextEx(fnt, defText.c_str(), 16.0f, 1.6f).x;

	DrawRectangle(defPosition.X, defPosition.Y, defSize.X, defSize.Y, { 80, 80, 80, 120 });
	DrawTextEx(fnt, defText.c_str(), { (float)defPosition.X + defSize.X / 2 - width / 2, (float)defPosition.Y + defSize.Y / 2 - 8 }, 16, 1.6f, WHITE);

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && COLLIDE(GetMouseX(), GetMouseY(), defPosition.X, defPosition.Y, defSize.X, defSize.Y)) {
		Activate();
	}
}

UIButton::UIButton(std::string text, UICoord pos, UICoord size, std::function<void(UIButton*)> act) {
	this->defText = text;
	this->defPosition = pos;
	this->defSize = size;
	this->onActivate = act;
}