#pragma once

#include "Collision.h"

class GameObject
{
	friend class ObjectManager;
private:
	int layer;

	bool isDisplay;
	bool isActive;
	bool isDie;

private:

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Destroy() = 0;

	virtual void OnCollision(Collision other) { }

	void Kill() { isDie = true; }
	void Kill(GameObject* other) { other->Kill(); }
};

