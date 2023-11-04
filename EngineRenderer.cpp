#include "EngineRenderer.hpp"
#include "EngineManager.hpp"
#include "EngineLogger.hpp"
#include "EngineControls.hpp"
#include <raylib.hpp>

static struct Camera3D mainCamera = {
	{ 0, 0, 0 }, { 0, 0, 1 }, { 0, 1, 0 }, 90.0f, CAMERA_PERSPECTIVE
};

std::thread EngineRenderer::renderThread;
long long EngineRenderer::frameCount;
bool EngineRenderer::initialized;
bool EngineRenderer::paused;

void EngineRenderer::CreateRenderThread() {
	if (!initialized) {
		renderThread = std::thread(RenderThreadCallback);
		paused = false;

		EngineLogger::LogInfo("Waiting for renderer intialization...");
		while (!initialized);
		EngineLogger::LogInfo("Renderer is up!");
	}
}
bool EngineRenderer::IsRenderingPaused() {
	return paused;
}
void EngineRenderer::PauseRendering() {
	paused = true;
}
void EngineRenderer::ResumeRendering() {
	paused = false;
}
long long EngineRenderer::GetFrameCount() {
	return frameCount;
}
float EngineRenderer::GetFramesPerSecond() {
	return NAN;
}
void EngineRenderer::RenderThreadCallback() {
	if (!initialized) {
		initialized = true;

		InitWindow(std::stoi(EngineManager::GetConfigValue("screen.resolution.x")), std::stoi(EngineManager::GetConfigValue("screen.resolution.y")), "Simple Sandbox");
		SetTargetFPS(std::stoi(EngineManager::GetConfigValue("screen.fps")));
	}

	while (EngineManager::IsAppRunning()) {
		if (paused) goto renderEnd;

		BeginDrawing();
		ClearBackground(BLACK);
		BeginMode3D(mainCamera);

		EngineManager::GetCurrentWorld()->RenderWorld();

		EndMode3D();

		DrawFPS(10, 10);
		DrawText(("Frame #" + std::to_string(frameCount)).c_str(), 10, 30, 20, WHITE);

		EndDrawing();

		frameCount++;

	renderEnd:

		if (IsKeyPressed(EngineControls::KcPauseRendering)) {
			paused = !paused;
		}
		if (IsKeyPressed(EngineControls::KcAbrutlyEnd)) {
			EngineManager::Shutdown();
		}

		if (WindowShouldClose()) 
			EngineManager::Shutdown();
	}

	CloseWindow();

	// ...

	EngineLogger::LogInfo("Renderer has shut down!");

	for (;;); // i forgot that c++ threads cannot terminate :skull:
}