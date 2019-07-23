#include "DXUT.h"
#include "Renderer.h"

void Renderer::Init()
{
	gameObject->renderer = this;

	RENDER.Add(this);
}

void Renderer::Update()
{
}

void Renderer::Destroy()
{
	if (gameObject->renderer == this)
		gameObject->renderer = nullptr;

	RENDER.Remove(this);
}