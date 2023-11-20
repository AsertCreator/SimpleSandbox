#include "UIWindow.hpp"
#include "UIManager.hpp"
#include "EngineResources.hpp"
#include <raylib.hpp>

void UIWindow::AddElement(UIElement* el) {
	elem.push_back(el);
}
void UIWindow::RemoveElement(int eln) {
	if (GetElementCount() <= eln) return;

	auto begin = elem.begin();

	for (int i = 0; i < eln; i++)
		begin++;

	elem.erase(begin);
}
int UIWindow::GetElementCount() {
	return (int)elem.size();
}
UIElement* UIWindow::GetElement(int eln) {
	return elem[eln];
}
std::string UIWindow::GetUIClass() {
	return "UIWindow";
}
void UIWindow::Render() {
	Font fnt = EngineResources::GetFont("res/main.ttf");
	float width = MeasureTextEx(fnt, defText.c_str(), 16.0f, 1.6f).x;

	DrawRectangle(defPosition.X, defPosition.Y, defSize.X, defSize.Y, { 40, 40, 40, 120 });
	DrawRectangle(defPosition.X + defSize.X - 30, defPosition.Y + 5, 25, 15, { 255, 0, 0, 255 });
	DrawRectangle(defPosition.X + 5, defPosition.Y + 26, defSize.X - 10, defSize.Y - 31, { 40, 40, 40, 120 });
	DrawTextEx(fnt, defText.c_str(), { defPosition.X + 5.0f, defPosition.Y + 5.0f }, 16, 1.6f, WHITE);

	for (int i = 0; i < GetElementCount(); i++) {
		auto elem = GetElement(i);

		auto orgpos = elem->GetPosition();
		elem->SetPosition({ orgpos.X + defPosition.X + 5, orgpos.Y + defPosition.Y + 26 });
		elem->Render();
		elem->SetPosition(orgpos);
	}

	if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && COLLIDE(GetMouseX(), GetMouseY(), defPosition.X + defSize.X - 30, defPosition.Y + 5, 25, 15)) {
		UIManager::RemoveElement(this);
		delete this;
	}
}

UIWindow::UIWindow(std::string text, UICoord pos, UICoord size) {
	this->defText = text;
	this->defPosition = pos;
	this->defSize = size;
}