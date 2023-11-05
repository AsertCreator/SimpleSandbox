#include "EnginePropList.hpp"
#include "Utilities.hpp"

std::string EnginePropList::GetValue(std::string key) {
	return this->data[key];
}
std::string EnginePropList::SetValue(std::string key, std::string val) {
	this->data[key] = val;
	return this->data[key];
}
std::string EnginePropList::GetPropList() {
	std::string str = "";
	auto iter = data.end();
	iter--;
	for (int i = 0; i < data.size() - 1; i++) {
		str += (*iter).first + "=" + (*iter).second + "\n";
		iter--;
	}
	str += (*iter).first + "=" + (*iter).second;
	return str;
}
void EnginePropList::UpdatePropList() {
	if (this->rawText.size() == 0) return;

	std::vector<std::string> lines = Utilities::Split(this->rawText, "\n");

	for (int i = 0; i < lines.size(); i++) {
		std::vector<std::string> parts = Utilities::Split(lines[i], "=");
		data[parts[0]] = parts[1];
	}
}

EnginePropList::EnginePropList(std::string str) {
	this->rawText = str;
	this->data = std::map<std::string, std::string>();
	UpdatePropList();
}