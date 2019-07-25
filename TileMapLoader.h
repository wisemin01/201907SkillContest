#pragma once
#include "Component.h"

class TileMapLoader
{
public:
	struct TileInfo
	{
		int x = -1;
		int y = -1;

		float rotation = -1.0f;

		int tileNumber = -1;
	};
private:
	std::vector<std::pair<Mesh*, float>>* meshTypeContainer; // first = mesh , second = mesh height
	std::vector<TileInfo*>* tileMap;

	float tileWidth = -1.0;
	float tileHeight = -1.0;

	int mapWidthIndex = 0;
	int mapHeightIndex = 0;

	Shader* shader = nullptr;

public:
	TileMapLoader();
	~TileMapLoader();

	void LoadFromFile(const string& path);

	void Spawn(GameObject* baseTileMap);

	float GetWidth();
	float GetHeight();

private:
	bool ParseLine(ifstream &stream);
	void Parse(const string& fileName);

public:
};

