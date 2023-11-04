#include "EngineLogger.hpp"
#include <iostream>
#include <atomic>
#include <Windows.h>

static std::atomic_bool mutex = false;
std::string EngineLogger::log = "";

std::string EngineLogger::GetLog() {
	return log;
}
void EngineLogger::LogInfo(std::string msg) {
	while (mutex);
	mutex = true;

	std::string fullmsg = "[info] " + msg + "\n";

	log += fullmsg;
	std::cout << fullmsg;
	OutputDebugStringA(fullmsg.c_str());

	mutex = false;
}										    
void EngineLogger::LogWarn(std::string msg) {
	while (mutex);
	mutex = true;

	std::string fullmsg = "[warn] " + msg + "\n";

	log += fullmsg;
	std::cout << fullmsg;
	OutputDebugStringA(fullmsg.c_str());

	mutex = false;
}										    
void EngineLogger::LogErro(std::string msg) {
	while (mutex);
	mutex = true;

	std::string fullmsg = "[erro] " + msg + "\n";

	log += fullmsg;
	std::cout << fullmsg;
	OutputDebugStringA(fullmsg.c_str());

	mutex = false;
}