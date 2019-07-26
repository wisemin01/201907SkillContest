#pragma once
#include "GameObject.h"

class Bullet :
	public GameObject
{
public:
	void Setting(Vector3 direction, float speed);

	// GameObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;
};

