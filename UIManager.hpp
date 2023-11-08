#pragma once
#include "UICommon.hpp"
#include "UIElement.hpp"
#include <functional>
#include <vector>

class UIManager {
public:
	static void RenderUI();
	static void DisableUI();
	static void EnableUI();
	static void AddElement(UIElement* el);
	static void RemoveElement(int eln);
	static void RemoveElement(UIElement* el);
	static int GetElementCount();
	static UIElement* GetElement(int eln);
	static std::string GetUIStatus();
	static std::string SetUIStatus(std::string str);
	static void MessageBox(std::string text, std::string caption, bool yesno, std::function<void(int)> callback);

	NO_CCTOR(UIManager);
private:
	static bool enabled;
	static std::string status;
	static std::vector<UIElement*> uiElems;
};