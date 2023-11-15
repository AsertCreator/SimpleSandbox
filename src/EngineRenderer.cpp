#include "EngineRenderer.hpp"
#include "EngineManager.hpp"
#include "EngineLogger.hpp"
#include "EngineControls.hpp"
#include "UIButton.hpp"
#include "UIManager.hpp"
#include "UIBasicOverlay.hpp"
#include "EngineResources.hpp"
#include "Utilities.hpp"
#include <raylib.hpp>
#include <rlgl.h>

static struct Camera3D mainCamera = {
	{ 0, 0, 0 }, { 0, 0, 1 }, { 0, 1, 0 }, 90.0f, CAMERA_PERSPECTIVE
};

std::thread EngineRenderer::renderThread;
long long EngineRenderer::frameCount;
bool EngineRenderer::initialized;
bool EngineRenderer::gamePaused;
bool EngineRenderer::paused;

#define DCPE_FRONT 1
#define DCPE_BACK  2
#define DCPE_LEFT  4
#define DCPE_RIGHT 8
#define DCPE_UP    16
#define DCPE_DOWN  32
#define DCPE_ALL DCPE_FRONT | DCPE_BACK | DCPE_LEFT | DCPE_RIGHT | DCPE_UP | DCPE_DOWN

void DrawCubeProEx(Vector3 position, float width, float height, float length, Color color, int flags)
{
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	rlPushMatrix();
	// NOTE: Transformation is applied in inverse order (scale -> rotate -> translate)
	rlTranslatef(position.x, position.y, position.z);
	//rlRotatef(45, 0, 1, 0);
	//rlScalef(1.0f, 1.0f, 1.0f);   // NOTE: Vertices are directly scaled on definition

	rlBegin(RL_TRIANGLES);
	rlColor4ub(color.r, color.g, color.b, color.a);

	// Front face
	if (flags & DCPE_FRONT) {
		rlVertex3f(x - width / 2, y - height / 2, z + length / 2);  // Bottom Left
		rlVertex3f(x + width / 2, y - height / 2, z + length / 2);  // Bottom Right
		rlVertex3f(x - width / 2, y + height / 2, z + length / 2);  // Top Left

		rlVertex3f(x + width / 2, y + height / 2, z + length / 2);  // Top Right
		rlVertex3f(x - width / 2, y + height / 2, z + length / 2);  // Top Left
		rlVertex3f(x + width / 2, y - height / 2, z + length / 2);  // Bottom Right
	}

	// Back face
	if (flags & DCPE_BACK) {
		rlVertex3f(x - width / 2, y - height / 2, z - length / 2);  // Bottom Left
		rlVertex3f(x - width / 2, y + height / 2, z - length / 2);  // Top Left
		rlVertex3f(x + width / 2, y - height / 2, z - length / 2);  // Bottom Right

		rlVertex3f(x + width / 2, y + height / 2, z - length / 2);  // Top Right
		rlVertex3f(x + width / 2, y - height / 2, z - length / 2);  // Bottom Right
		rlVertex3f(x - width / 2, y + height / 2, z - length / 2);  // Top Left
	}

	// Top face
	if (flags & DCPE_UP) {
		rlVertex3f(x - width / 2, y + height / 2, z - length / 2);  // Top Left
		rlVertex3f(x - width / 2, y + height / 2, z + length / 2);  // Bottom Left
		rlVertex3f(x + width / 2, y + height / 2, z + length / 2);  // Bottom Right

		rlVertex3f(x + width / 2, y + height / 2, z - length / 2);  // Top Right
		rlVertex3f(x - width / 2, y + height / 2, z - length / 2);  // Top Left
		rlVertex3f(x + width / 2, y + height / 2, z + length / 2);  // Bottom Right
	}

	// Bottom face
	if (flags & DCPE_DOWN) {
		rlVertex3f(x - width / 2, y - height / 2, z - length / 2);  // Top Left
		rlVertex3f(x + width / 2, y - height / 2, z + length / 2);  // Bottom Right
		rlVertex3f(x - width / 2, y - height / 2, z + length / 2);  // Bottom Left

		rlVertex3f(x + width / 2, y - height / 2, z - length / 2);  // Top Right
		rlVertex3f(x + width / 2, y - height / 2, z + length / 2);  // Bottom Right
		rlVertex3f(x - width / 2, y - height / 2, z - length / 2);  // Top Left
	}

	// Right face
	if (flags & DCPE_RIGHT) {
		rlVertex3f(x + width / 2, y - height / 2, z - length / 2);  // Bottom Right
		rlVertex3f(x + width / 2, y + height / 2, z - length / 2);  // Top Right
		rlVertex3f(x + width / 2, y + height / 2, z + length / 2);  // Top Left

		rlVertex3f(x + width / 2, y - height / 2, z + length / 2);  // Bottom Left
		rlVertex3f(x + width / 2, y - height / 2, z - length / 2);  // Bottom Right
		rlVertex3f(x + width / 2, y + height / 2, z + length / 2);  // Top Left
	}

	// Left face
	if (flags & DCPE_LEFT) {
		rlVertex3f(x - width / 2, y - height / 2, z - length / 2);  // Bottom Right
		rlVertex3f(x - width / 2, y + height / 2, z + length / 2);  // Top Left
		rlVertex3f(x - width / 2, y + height / 2, z - length / 2);  // Top Right

		rlVertex3f(x - width / 2, y - height / 2, z + length / 2);  // Bottom Left
		rlVertex3f(x - width / 2, y + height / 2, z + length / 2);  // Top Left
		rlVertex3f(x - width / 2, y - height / 2, z - length / 2);  // Bottom Right
	}

	rlEnd();
	rlPopMatrix();
}

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
bool EngineRenderer::IsGamePaused() {
	return gamePaused;
}
void EngineRenderer::PauseGame() {
	gamePaused = true;
}
void EngineRenderer::ResumeGame() {
	gamePaused = false;
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

		SetTraceLogLevel(LOG_ALL);

		InitWindow(std::stoi(EngineManager::GetConfigValue("screen.resolution.x")), std::stoi(EngineManager::GetConfigValue("screen.resolution.y")), "Simple Sandbox");
		SetTargetFPS(std::stoi(EngineManager::GetConfigValue("screen.fps")));
		SetExitKey(KEY_NULL);

		UIManager::AddElement(new UIBasicOverlay());
		UIManager::EnableUI();
	}

	DisableCursor();

	while (EngineManager::IsAppRunning()) {
		float skyboxsize = 10;

		if (paused) goto renderEnd;

		BeginDrawing();
		ClearBackground(BLACK);
		BeginMode3D(mainCamera);

		DrawCubeProEx({ -skyboxsize, 0, 0 }, skyboxsize, skyboxsize, skyboxsize, { 255, 0, 0, 255 }, DCPE_RIGHT);
		DrawCubeProEx({ 0, -skyboxsize, 0 }, skyboxsize, skyboxsize, skyboxsize, { 0, 255, 0, 255 }, DCPE_UP);
		DrawCubeProEx({ 0, 0, -skyboxsize }, skyboxsize, skyboxsize, skyboxsize, { 0, 0, 255, 255 }, DCPE_FRONT);
		DrawCubeProEx({ skyboxsize, 0, 0 } , skyboxsize, skyboxsize, skyboxsize, { 255, 0, 0, 255 }, DCPE_LEFT);
		DrawCubeProEx({ 0, skyboxsize, 0 } , skyboxsize, skyboxsize, skyboxsize, { 0, 255, 0, 255 }, DCPE_DOWN);
		DrawCubeProEx({ 0, 0, skyboxsize } , skyboxsize, skyboxsize, skyboxsize, { 0, 0, 255, 255 }, DCPE_BACK);

		EngineManager::GetCurrentWorld()->RenderWorld();

		EndMode3D();

		UIManager::RenderUI();

		if (!gamePaused) {
			UpdateCamera(&mainCamera, CAMERA_FIRST_PERSON);

			if (IsKeyDown(KEY_SPACE)) {
				mainCamera.position.y += 0.1f;
				mainCamera.target.y += 0.1f;
			}
			if (IsKeyDown(KEY_LEFT_SHIFT)) {
				mainCamera.position.y -= 0.1f;
				mainCamera.target.y -= 0.1f;
			}
		}

		if (IsKeyPressed(KEY_ESCAPE)) {
			gamePaused = !gamePaused;

			if (gamePaused) {
				EnableCursor();
			}
			else {
				DisableCursor();
			}

			UIManager::SetUIStatus("");
			
			for (int i = 0; i < UIManager::GetElementCount(); i++) {
				auto el = UIManager::GetElement(i);

				if (el->GetUIClass() == "UIWindow") {
					UIManager::RemoveElement(i);
					delete el;
					i--;
				}
			}
		}

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