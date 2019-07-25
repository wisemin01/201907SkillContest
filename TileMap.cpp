#include "DXUT.h"
#include "TileMap.h"

#include "TileMapLoader.h"

void TileMap::Init()
{
	AC(Transform);
}

void TileMap::Update()
{
	if (INPUT.GetKeyDown('K'))
		transform->rotation.y += 10;
}

void TileMap::Render()
{

}

void TileMap::Destroy()
{

}

void TileMap::Load(const string& tileMapData)
{
	TileMapLoader loader;

	loader.LoadFromFile(tileMapData);
	loader.Spawn(this);
}
