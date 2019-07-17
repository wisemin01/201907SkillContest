#pragma once

class GameObject;
class Component
{
private:
	GameObject* baseObject;
public:
	Component(GameObject* base)
	{
		gameObject = base;
	}

	__declspec(property(get = GetBaseObject, put = SetBaseObject)) GameObject* gameObject;

	GameObject* GetBaseObject()
	{
		return baseObject;
	}

private:
	void SetBaseObject(GameObject* owner)
	{
		baseObject = owner;
	}
};

