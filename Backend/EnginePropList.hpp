#pragma once
#include "Common.hpp"
#include <vector>
#include <string>
#include <map>

class EnginePropList {
public:
	std::string GetValue(std::string key);
	std::string SetValue(std::string key, std::string val);
	std::string GetPropList();
	std::vector<std::string> GetKeys();
	void UpdatePropList();
	int Size();

	EnginePropList(std::string str);
private:
	std::map<std::string, std::string> data;
	std::string rawText;
};