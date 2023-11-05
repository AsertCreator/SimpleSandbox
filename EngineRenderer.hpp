#pragma once
#include "Common.hpp"
#include "UIElement.hpp"
#include <string>
#include <thread>
#include <vector>

class EngineRenderer {
public:
	static void CreateRenderThread();
	static bool IsRenderingPaused();
	static void PauseRendering();
	static void ResumeRendering();
	static long long GetFrameCount();
	static float GetFramesPerSecond();

	NO_CCTOR(EngineRenderer);
private:
	static std::vector<UIElement*> uiElems;
	static std::thread renderThread;
	static long long frameCount;
	static bool initialized;
	static bool paused;

	static void RenderThreadCallback();
};