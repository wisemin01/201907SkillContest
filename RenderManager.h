#pragma once
#include "Singleton.h"

class Renderer;
class RenderManager :
	public Singleton<RenderManager>
{
private:
	std::list<Renderer*> rendererList;
public:
	RenderManager();
	~RenderManager();

	void Add(Renderer* renderer);
	void Remove(Renderer* renderer);

	void operator +=(Renderer* value)
	{
		Add(value);
	}

	void operator -=(Renderer* value)
	{
		Remove(value);
	}

	void Render();
};

#define RENDER RenderManager::GetInstance()