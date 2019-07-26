#pragma once
#include "Component.h"

class Transform
	: public Component
{
public:
	Transform* parents = nullptr;
public:
	Transform() {}
	Transform(GameObject* base) : Component(base) {}

	Vector3 _position;
	Quaternion _rotation;
	Vector3 _scale;

	__declspec(property(get = GetPosition, put = SetPosition)) Vector3 position;
	__declspec(property(get = GetRotation, put = SetRotation)) Quaternion rotation;
	__declspec(property(get = GetScale, put = SetScale)) Vector3 scale;

	Vector3 GetPosition() { return _position; }
	void SetPosition(Vector3 v) { _position = v; }
	Quaternion GetRotation() { return _rotation; }
	void SetRotation(Quaternion q) { _rotation = q; }
	Vector3 GetScale() { return _scale; }
	void SetScale(Vector3 v) { _scale = v; }

	void Rotate(Vector3 degree);

	void SetRotationDegree(Vector3 r) { _rotation = Quaternion::Rotation(r.ToRadian()); }

	Matrix GetWorldMatrix();

	Matrix GetRotationMatrix();

	__declspec(property(get = GetWorldMatrix)) Matrix World;
	__declspec(property(get = GetRotationMatrix)) Matrix MatRotation;

	// Component을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Destroy() override;

	void AddChild(Transform* t);
	void RemoveChild(Transform* t);
};

