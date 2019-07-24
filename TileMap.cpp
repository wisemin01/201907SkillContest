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
	ACR(TileMapRenderer).LoadFromFile(tileMapData);

	SetRenderBegin(LAMBDA{ DXUTGetD3D9Device()->SetRenderState(D3DRS_LIGHTING, false); });
	SetRenderEnd(LAMBDA{ DXUTGetD3D9Device()->SetRenderState(D3DRS_LIGHTING, true); });
}
