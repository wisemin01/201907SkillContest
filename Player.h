#pragma once
#include "GameObject.h"
class Player :
	public GameObject
{
public:

	// GameObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	virtual void OnCollision(Collider* other) override;
};

