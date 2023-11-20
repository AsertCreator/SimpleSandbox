#include "EngineResources.hpp"

std::map<std::string, Font> EngineResources::loadedFonts;
std::map<std::string, Model> EngineResources::loadedModels;
std::map<std::string, Texture> EngineResources::loadedTextures;

void EngineResources::Initialize() {
	loadedFonts = std::map<std::string, Font>();
	loadedModels = std::map<std::string, Model>();
	loadedTextures = std::map<std::string, Texture>();
}
Font EngineResources::GetFont(std::string family) {
	auto begin = loadedFonts.begin();
	for (int i = 0; i < loadedFonts.size(); i++) {
		auto pair = *begin;
		if (pair.first == family) return pair.second;
		begin++;
	}

	loadedFonts[family] = LoadFont(family.c_str());
	return loadedFonts[family];
}
Model EngineResources::GetModel(std::string name) {
	auto begin = loadedModels.begin();
	for (int i = 0; i < loadedModels.size(); i++) {
		auto pair = *begin;
		if (pair.first == name) return pair.second;
		begin++;
	}

	loadedModels[name] = LoadModel(name.c_str());
	return loadedModels[name];
}
Texture EngineResources::GetTexture(std::string name) {
	auto begin = loadedTextures.begin();
	for (int i = 0; i < loadedTextures.size(); i++) {
		auto pair = *begin;
		if (pair.first == name) return pair.second;
		begin++;
	}

	loadedTextures[name] = LoadTexture(name.c_str());
	return loadedTextures[name];
}
void EngineResources::UnloadResource(std::string name) {
	auto begin = loadedFonts.begin();
	for (int i = 0; i < loadedFonts.size(); i++) {
		auto pair = *begin;
		if (pair.first == name) {
			UnloadFont(pair.second);
			loadedFonts.erase(pair.first);
			return;
		}
		begin++;
	}
	auto begin2 = loadedModels.begin();
	for (int i = 0; i < loadedModels.size(); i++) {
		auto pair = *begin2;
		if (pair.first == name) {
			UnloadModel(pair.second);
			loadedFonts.erase(pair.first);
			return;
		}
		begin2++;
	}
	auto begin3 = loadedTextures.begin();
	for (int i = 0; i < loadedTextures.size(); i++) {
		auto pair = *begin3;
		if (pair.first == name) {
			UnloadTexture(pair.second);
			loadedFonts.erase(pair.first);
			return;
		}
		begin3++;
	}
}
void EngineResources::ReloadResources() {
	auto begin = loadedFonts.begin();
	for (int i = 0; i < loadedFonts.size(); i++) {
		auto pair = *begin;
		UnloadFont(pair.second);
		loadedFonts[pair.first] = LoadFont(pair.first.c_str());
		begin++;
	}
	auto begin2 = loadedModels.begin();
	for (int i = 0; i < loadedModels.size(); i++) {
		auto pair = *begin2;
		UnloadModel(pair.second);
		loadedModels[pair.first] = LoadModel(pair.first.c_str());
		begin2++;
	}
	auto begin3 = loadedTextures.begin();
	for (int i = 0; i < loadedTextures.size(); i++) {
		auto pair = *begin3;
		UnloadTexture(pair.second);
		loadedTextures[pair.first] = LoadTexture(pair.first.c_str());
		begin3++;
	}
}