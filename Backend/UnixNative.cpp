#ifndef _WIN32
#include "Native.hpp"
#include <unistd.h>

void Native::ShowMessageBox(std::string text, std::string caption, int icon) {
	// do smth
}
void Native::ImmediatelyExit(int code) {
	_exit(code);
}
#endif