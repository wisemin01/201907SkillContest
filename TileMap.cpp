#include "DXUT.h"
#include "TileMap.h"

#include "TileMapRenderer.h"

void TileMap::Init()
{
	AC(Transform);
}

void TileMap::Update()
{
	if (INPUT.GetKeyPress('L'))
		transform->rotation.y += D3DXToRadian(1);
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

	AC(Collider)->SetAsSphere(renderer.GetWidth());
}
