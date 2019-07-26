#pragma once
#include "Component.h"

class Rigidbody :
	public Component
{
	friend class GameObject;
private:

	Vector3 _force = Vector3::Zero;
	Vector3 _velocity = Vector3::Zero;

	float _mass = 1.0f;
	float _drag = 50;

	float _elasticity = 0.1f;

	bool _useGravity = true;

	bool _isKinematic = false;
	bool _isOnGround = false;
	bool _isFreeze = false;
	bool _isFreezeRotation = false;

public:
	__declspec(property(get = GetForce, put = SetForce)) Vector3 Force;
	__declspec(property(get = GetVelocity, put = SetVelocity)) Vector3 Velocity;
	__declspec(property(get = GetMass, put = SetMass)) float Mass;
	__declspec(property(get = GetDrag, put = SetDrag)) float Drag;
	__declspec(property(get = GetElasticity, put = SetElasticity)) float Elasticity;
	__declspec(property(get = GetUseGravity, put = SetUseGravity)) bool UseGravity;
	__declspec(property(get = GetIsKinematic, put = SetIsKinematic)) bool IsKinematic;
	__declspec(property(get = GetIsFreeze, put = SetIsFreeze)) bool IsFreeze;
	__declspec(property(get = GetIsFreezeRotation, put = SetIsFreezeRotation)) bool IsFreezeRotation;

	void SetForce(Vector3 value) { _force = value; }
	void SetVelocity(Vector3 value) { _velocity = value; }
	void SetMass(float value) { _mass = max(0.0f, value); }
	void SetDrag(float value) { _drag = value; }
	void SetElasticity(float value) { _elasticity = min(1.0f, max(0.0f, value)); }
	void SetUseGravity(bool value) { _useGravity = value; }

	void SetIsKinematic(bool value) { _isKinematic = value; }
	void SetIsFreeze(bool value) { _isFreeze = value; }
	void SetIsFreezeRotation(bool value) { _isFreezeRotation = value; }

	Vector3 GetForce() { return _force; }
	Vector3 GetVelocity() { return _velocity; }
	float GetMass() { return _mass; }
	float GetDrag() { return _drag; }
	float GetElasticity() { return _elasticity; }
	bool GetUseGravity() { return _useGravity; }
	bool GetIsKinematic() { return _isKinematic; }
	bool GetIsFreeze() { return _isFreeze; }
	bool GetIsFreezeRotation() { return _isFreezeRotation; }

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