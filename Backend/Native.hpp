#pragma once
#include "Common.hpp"
#include <string>

#define MB_ERROR 1
#define MB_WARN 2
#define MB_INFO 3

class Native {
public:
	static void ShowMessageBox(std::string text, std::string caption, int icon);
	static void ImmediatelyExit(int code);

	NO_CCTOR(Native);
};