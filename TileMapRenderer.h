#pragma once
#include "Component.h"

struct TileInfo
{
	int x = -1;
	int y = -1;

	float rotation = -1.0f;

	int tileNumber = -1;
};

class TileMapRenderer
	: public MeshRenderer
{
private:
	std::vector<Mesh*>* meshTypeContainer;
	std::vector<TileInfo*>* tileMap;

	float tileWidth = -1.0;
	float tileHeight = -1.0;

	int mapWidthIndex = 0;
	int mapHeightIndex = 0;

public:

	void LoadFromFile(const string& path);

	// Component을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Destroy() override;

	// Renderer을(를) 통해 상속됨
	virtual void Render() override;

private:
	bool ParseLine(ifstream &stream);
	void Parse(const string& fileName);
};

