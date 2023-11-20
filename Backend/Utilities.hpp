#pragma once
#include "Common.hpp"
#include <string>
#include <vector>

class Utilities {
public:
	static EXPORT std::vector<std::string> Split(std::string str, std::string delim);
	static EXPORT std::string ReadFile(std::string filepath);
	static EXPORT std::string FormatText(std::string fmt, ...);
	static EXPORT void WriteFile(std::string filepath, std::string data);

	NO_CCTOR(Utilities);
};