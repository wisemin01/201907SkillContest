#include "DXUT.h"
#include "RenderManager.h"

#include "Renderer.h"
#include "SkyBox.h"

RenderManager::RenderManager()
{
	DXUTGetD3D9Device()->SetRenderState(D3DRS_LIGHTING, false);
}

RenderManager::~RenderManager()
{
	DXUTGetD3D9Device()->SetRenderState(D3DRS_LIGHTING, true);

	rendererList.clear();
	SkyBox::RemoveAll();
}

void RenderManager::Add(Renderer* renderer)
{
	rendererList.push_back(renderer);
}

void RenderManager::Remove(Renderer* renderer)
{
	rendererList.remove(renderer);
}

void RenderManager::Render()
{
	CAMERA.SetViewMatrix();

	// SKY BOX RENDERING
	CAMERA.DrawSkyBox(true);

	DXUTGetD3D9Device()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	for each (auto iter in rendererList)
	{
		iter->Render();
	}

	RESOURCE.RenderBegin();

	// DRAW UI OBJECTS

	RESOURCE.RenderEnd();
}
