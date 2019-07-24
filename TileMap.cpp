#include "DXUT.h"
#include "TileMap.h"

#include "TileMapRenderer.h"

void TileMap::Init()
{
	AC(Transform);
}

void TileMap::Update()
{
}

void TileMap::Render()
{

}

void TileMap::Destroy()
{

}

void TileMap::Load(const string& tileMapData)
{
	auto &renderer = ACR(TileMapRenderer);
	renderer.LoadFromFile(tileMapData).SetShader(FIND(Shader, "LightShader"));
}
