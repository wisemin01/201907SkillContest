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
	ACR(TileMapRenderer).LoadFromFile(tileMapData).SetShader(FIND(Shader,"LightShader"));
	// AC(MeshRenderer)->SetMesh(FIND(Mesh, "Test")).SetShader(FIND(Shader, "LightShader"));
}
