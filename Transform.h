#pragma once
#include "Component.h"

class Transform
	: public Component
{
public:
	Transform* parents = nullptr;
public:
	Transform() {}
	Transform(GameObject* base) : Component(base) {}

	Vector3 position;
	Vector3 rotation;
	Vector3 scale;

	Matrix GetWorldMatrix();

	__declspec(property(get = GetWorldMatrix)) Matrix World;

	// Component을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Destroy() override;

	void AddChild(Transform* t);
	void RemoveChild(Transform* t);
};

