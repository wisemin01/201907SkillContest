#include "DXUT.h"
#include "RenderManager.h"

#include "Renderer.h"
#include "SkyBox.h"

RenderManager::RenderManager()
{
}

RenderManager::~RenderManager()
{
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

	for each (auto iter in rendererList)
	{
		iter->Render();
	}

	RESOURCE.RenderBegin();

	// DRAW UI OBJECTS

	RESOURCE.RenderEnd();
}
