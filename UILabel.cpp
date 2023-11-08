#include "UILabel.hpp"
#include "EngineResources.hpp"

std::string UILabel::GetUIClass() {
	return "UILabel";
}
void UILabel::Render() {
	Font fnt = EngineResources::GetFont("res/main.ttf");
	DrawTextEx(fnt, defText.c_str(), { (float)defPosition.X, (float)defPosition.Y }, 16.0f, 1.6f, WHITE);
}

UILabel::UILabel(UICoord pos, std::string text) {
	this->defPosition = pos;
	this->defText = text;
}