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

		if (com)
		{
			com->Destroy();
			delete com;
			com = nullptr;
		}
	}

	componentContainer.clear();
}

void GameObject::OnCollisionBase(Collider* other)
{	
	if (rigidbody)
	{
		GameObject* other_obj = other->gameObject;

		rigidbody->OnCollision(other_obj->transform, other_obj->rigidbody);
	}

	OnCollision(other);
}

void GameObject::SetRenderBegin(function<void()> begin)
{
	if (renderer)
		renderer->renderBegin = begin;
}

void GameObject::SetRenderEnd(function<void()> end)
{
	if (renderer)
		renderer->renderEnd = end;
}
