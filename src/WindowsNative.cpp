#ifdef _WIN32
#include "Native.hpp"
#include <Windows.h>

void Native::ShowMessageBox(std::string text, std::string caption, int icon) {
	int flags = MB_OK;

	if (icon == MB_ERROR) flags |= MB_ICONERROR;
	if (icon == MB_WARN) flags |= MB_ICONWARNING;
	if (icon == MB_INFO) flags |= MB_ICONINFORMATION;

	MessageBoxA(0, text.c_str(), caption.c_str(), flags);
}
void Native::ImmediatelyExit(int code) {
	TerminateProcess(GetCurrentProcess(), code);
}
#endif