#pragma once
#include "Common.hpp"
#include <string>
#include <map>

class EnginePropList {
public:
	std::string GetValue(std::string key);
	std::string SetValue(std::string key, std::string val);
	std::string GetPropList();
	void UpdatePropList();

	EnginePropList(std::string str);
private:
	std::map<std::string, std::string> data;
	std::string rawText;
};