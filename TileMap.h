#pragma once
#include "Component.h"

struct TileInfo
{
	int x = -1;
	int y = -1;

	int rotation = -1;

	int tileNumber = -1;
};

class TileMapRenderer
	: public MeshRenderer
{
private:
	std::vector<Mesh*> meshTypeContainer;

	std::vector<TileInfo*> tileMap;

	float tileWidth = -1;
	float tileHeight = -1;

	int tileMapWidth = -1;
	int tileMapHeight = -1;

public:

	void LoadFromFile(const string& path);

	// Component��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Destroy() override;

	// Renderer��(��) ���� ��ӵ�
	virtual void Render() override;

private:
	bool ParseLine(ifstream &stream);
	void Parse(const string& fileName);
};

