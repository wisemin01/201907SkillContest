#pragma once
#include "Singleton.h"

class GameObject;

class ObjectManager
	: public Singleton<ObjectManager>
{
private:
	list<GameObject*> objectList;
public:
	ObjectManager() {}
	~ObjectManager() { Reset(); }

	template <typename T>
	T* AddObject(int layer = 0, bool isDisplay = true, bool isActive = true)
	{
		T* object = new T();
		object->Init();

		object->layer = layer;
		object->isDisplay = isDisplay;
		object->isActive = isActive;

		objectList.push_back(object);

		return object;
	}
	
	void Update();
	void Reset();

private:
	void ClearObjectList();
};

#define OBJECT ObjectManager::GetInstance()

#define Instance(T) OBJECT.AddObject<T>()

#define InstanceEx(T) OBJECT.AddObject<T>