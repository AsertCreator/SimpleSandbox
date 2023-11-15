#pragma once
#include "Common.hpp"
#include <string>
#include <vector>

class Utilities {
public:
	static std::vector<std::string> Split(std::string str, std::string delim);
	static std::string ReadFile(std::string filepath);
	static std::string FormatText(std::string fmt, ...);
	static void WriteFile(std::string filepath, std::string data);

	NO_CCTOR(Utilities);
};