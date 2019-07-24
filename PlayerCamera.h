#pragma once
#include "GameObject.h"

class PlayerCamera :
	public GameObject
{
private:
	Event<TouchEventArgs> *TouchEvent;

	Transform* playerTransform = nullptr;

	Vector3 camOffset;
public:

	// GameObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	void OnMouseClick(object sender, TouchEventArgs args);

	void SetTarget(Transform* target);
};

