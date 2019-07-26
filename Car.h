#pragma once
#include "GameObject.h"

class Car :
	public GameObject
{
public:
	void Setting(Mesh* mesh, Vector3 position);

	// GameObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	virtual void OnCollision(Collider* other);
};

