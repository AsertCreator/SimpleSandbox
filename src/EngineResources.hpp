#pragma once
#include "Common.hpp"
#include <raylib.hpp>
#include <map>
#include <string>

class EngineResources {
public:
	static void Initialize();
	static Font GetFont(std::string family);
	static Model GetModel(std::string name);
	static Texture GetTexture(std::string name);
	static void UnloadResource(std::string name);
	// THIS RELOADS EVERYTHING!! TOO LONG
	static void ReloadResources();

	NO_CCTOR(EngineResources);
private:
	static std::map<std::string, Font> loadedFonts;
	static std::map<std::string, Model> loadedModels;
	static std::map<std::string, Texture> loadedTextures;
};