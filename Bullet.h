#pragma once
#include "GameObject.h"

class Bullet :
	public GameObject
{
public:
	void Setting(Vector3 direction, float speed);

	// GameObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;
};

