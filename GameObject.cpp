#include "DXUT.h"
#include "GameObject.h"

void GameObject::ComUpdate()
{
	for each (auto iter in componentContainer)
		iter.second->Update();
}

void GameObject::ComDestroy()
{
	for each (auto iter in componentContainer)
	{
		auto com = iter.second;

		if (com) {
			com->Destroy();
			delete com;
			com = nullptr;
		}
	}

	componentContainer.clear();
}

void GameObject::SetRenderBegin(function<void()> begin)
{
	renderer->renderBegin = begin;
}

void GameObject::SetRenderEnd(function<void()> end)
{
	renderer->renderEnd = end;
}
