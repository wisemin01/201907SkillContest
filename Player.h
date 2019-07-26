#pragma once
#include "GameObject.h"
class Player :
	public GameObject
{
public:

	float minSpeed = 70;
	float maxSpeed = 180;

	float speed;

public:

	// GameObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	virtual void OnCollision(Collider* other) override;

public:
	void MoveCalculate();
};

