#pragma once

class Renderer;
class Transform;

class GameObject
{
	friend class ObjectManager;
private:
	int layer;

	bool isDisplay;
	bool isActive;
	bool isDie;

public:
	Renderer* renderer = nullptr;
	Transform* transform = nullptr;

private:

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Destroy() = 0;

	void Kill() { isDie = true; }
	void Kill(GameObject* other) { other->Kill(); }
};

