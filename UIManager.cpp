#include "UIManager.hpp"
#include "UIWindow.hpp"
#include "UILabel.hpp"
#include "UIButton.hpp"
#include "EngineResources.hpp"
#include <raylib.hpp>

bool UIManager::enabled = false;
std::string UIManager::status = "";
std::vector<UIElement*> UIManager::uiElems = std::vector<UIElement*>();

void UIManager::RenderUI() {
	if (!enabled) return;

	for (int i = 0; i < GetElementCount(); i++) {
		uiElems[i]->Render();
	}
}
void UIManager::DisableUI() {
	enabled = false;
}
void UIManager::EnableUI() {
	enabled = true;
}
void UIManager::AddElement(UIElement* el) {
	uiElems.push_back(el);
}
void UIManager::RemoveElement(int eln) {
	if (GetElementCount() <= eln) return;

	auto begin = uiElems.begin();

	for (int i = 0; i < eln; i++)
		begin++;

	uiElems.erase(begin);
}
void UIManager::RemoveElement(UIElement* el) {
	auto begin = uiElems.begin();

	for (int i = 0; i < GetElementCount(); i++) {
		if (*begin == el) {
			uiElems.erase(begin);
			return;
		}
		begin++;
	}
}
int UIManager::GetElementCount() {
	return uiElems.size();
}
UIElement* UIManager::GetElement(int eln) {
	return uiElems[eln];
}
std::string UIManager::GetUIStatus() {
	return status;
}
std::string UIManager::SetUIStatus(std::string str) {
	status = str;
	return status;
}
void UIManager::MessageBox(std::string text, std::string caption, bool yesno, std::function<void(int)> callback) {
	Font fnt = EngineResources::GetFont("res/main.ttf");
	Vector2 vct = MeasureTextEx(fnt, text.c_str(), 16.0f, 1.6f);
	UICoord size = { vct.x + 30, 95 };

	UIWindow* win = new UIWindow(caption, { GetScreenWidth() / 2 - size.X / 2, GetScreenHeight() / 2 - size.Y / 2 }, size);

	win->AddElement(new UILabel({ 10, 10 }, text));

	if (!yesno) {
		win->AddElement(new UIButton("OK", { 5, 40 }, { 50, 20 }, [win, callback](UIButton*) {
			UIManager::RemoveElement(win);
			delete win;
			callback(1);
		}));
	}
	else {
		win->AddElement(new UIButton("Yes", { 5, 40 }, { 50, 20 }, [win, callback](UIButton*) {
			UIManager::RemoveElement(win);
			delete win;
			callback(1);
		}));
		win->AddElement(new UIButton("No", { 60, 40 }, { 50, 20 }, [win, callback](UIButton*) {
			UIManager::RemoveElement(win);
			delete win;
			callback(0);
		}));
	}

	uiElems.push_back(win);
}