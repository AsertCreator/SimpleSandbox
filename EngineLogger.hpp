#pragma once
#include "Common.hpp"
#include <string>

class EngineLogger {
public:
	static std::string GetLog();
	static void LogInfo(std::string msg);
	static void LogWarn(std::string msg);
	static void LogErro(std::string msg);
private:
	static std::string log;

	NO_CCTOR(EngineLogger);
};