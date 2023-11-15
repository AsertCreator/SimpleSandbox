#pragma once
#include "Common.hpp"

class EngineControls {
public:
	static int KcPauseRendering;
	static int KcPauseGame;
	static int KcAbrutlyEnd;

	static void LoadControls();
	static void SaveControls();

	NO_CCTOR(EngineControls);
};