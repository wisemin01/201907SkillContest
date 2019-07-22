#include "DXUT.h"
#include "RenderManager.h"

#include "Renderer.h"

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
	for each (auto iter in rendererList)
	{
		iter->Render();
	}
}
