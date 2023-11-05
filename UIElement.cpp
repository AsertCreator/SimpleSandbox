#include "UIElement.hpp"

std::string UIElement::GetUIText() {
	return this->defText;
}
std::string UIElement::SetUIText(std::string text) {
	this->defText = text;
	return this->defText;
}
UICoord UIElement::GetPosition() {
	return this->defPosition;
}
UICoord UIElement::SetPosition(UICoord c) {
	this->defPosition = c;
	return this->defPosition;
}
UICoord UIElement::GetSize() {
	return this->defSize;
}
UICoord UIElement::SetSize(UICoord c) {
	this->defSize = c;
	return this->defSize;
}
void UIElement::Render() {
	// do nothing.
}