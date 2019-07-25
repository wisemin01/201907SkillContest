#pragma once
#include "Component.h"

class Rigidbody :
	public Component
{
	friend class GameObject;
public:

	Vector3 force = Vector3::Zero;
	Vector3 velocity = Vector3::Zero;

	float mass = 0.0f;
	float drag = 50;

	bool useGravity = true;

	bool isKinematic = false;

public:
	// Component을(를) 통해 상속됨

	virtual void Init() override;
	virtual void Update() override;
	virtual void Destroy() override;

	void AddForce(Vector3 force);
	void AddForce(float x, float y, float z);

private:
	void OnCollision(Transform* otherTransform, Rigidbody* otherRigidbody);

public:

	static Vector3 Gravity;
};

