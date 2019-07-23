#pragma once

class GameObject;
class Component abstract
{
	friend class GameObject;
private:
	GameObject* baseObject = nullptr;
public:
	Component() {}
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

public:
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Destroy() = 0;
};

