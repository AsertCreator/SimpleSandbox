#pragma once
#include "Common.hpp"
#include <string>

class EngineLogger {
public:
	static EXPORT std::string GetLog();
	static EXPORT void LogInfo(std::string msg);
	static EXPORT void LogWarn(std::string msg);
	static EXPORT void LogErro(std::string msg);
private:
	static std::string log;

	NO_CCTOR(EngineLogger);
};