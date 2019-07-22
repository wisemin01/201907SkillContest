#pragma once
#include "Component.h"

class Transform
	: public Component
{
public:
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;

	Matrix GetWorldMatrix();

	__declspec(property(get = GetWorldMatrix)) Matrix World;

	// Component��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Destroy() override;
};

