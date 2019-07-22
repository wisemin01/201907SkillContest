#pragma once
#include "Renderer.h"

class Mesh;

class MeshRenderer :
	public Renderer
{
private:
	Mesh* mesh;

	std::function<void()> renderBegin;
	std::function<void()> renderEnd;
public:

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();
};

