#pragma once
#include "GameObject.h"

class PlayerCamera :
	public GameObject
{
private:
	Transform* playerTransform = nullptr;

	Vector3 camOffset = Vector3::Zero;

	Event<bool>* MouseWheelEvent;
public:

	// GameObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	void SetTarget(Transform* target);

	void OnMouseWheelScroll(object sender, bool flag);
};

