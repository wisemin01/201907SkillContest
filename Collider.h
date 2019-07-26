#pragma once
#include "Component.h"

class Matrix;
class Vector3;


struct SphereData
{
	SphereData() {}
	SphereData(float radius) : length(radius) {}

	Vector3 center;
	float length;

	static bool IsCollision(const SphereData* a, const SphereData* b);

	void Translation(const Vector3& center);
};

struct AABBData
{
	AABBData() {}
	AABBData(float x, float y, float z)
		: localMin(-x / 2.f, -y / 2.f, -z / 2.f), localMax(x / 2.f, y / 2.f, z / 2.f) {}

	Vector3 localMin;
	Vector3 localMax;

	Vector3 center;

	Vector3 GetMin() const { return localMin + center; }
	Vector3 GetMax() const { return localMax + center; }

	static bool IsCollision(const AABBData* a, const AABBData* b);
	static Vector3 Intersect(const AABBData* a, const AABBData* b);

	void Translation(const Vector3& center);
};

struct MixData
{
	static bool IsCollision(const AABBData* a, const SphereData* b);
	static bool IsCollision(const SphereData* a, const AABBData* b);
};


class Collider :
	public Component
{
	enum ColliderType
	{
		None,
		Box,
		Sphere
	};
public:

	SphereData* sphereData = nullptr;
	AABBData* aabbData = nullptr;

	ColliderType type = None;

	__declspec(property(get = GetTag)) string Tag;

	bool isTrigger = false;

public:
	// Component을(를) 통해 상속됨
	virtual void Init();
	virtual void Update();
	virtual void Destroy();

	void SetAsSphere(float radius);
	void SetAsBox(float x, float y, float z);

	string GetTag() { return gameObject->Tag; }

public:
	static bool IsCollision(const Collider* col1, const Collider* col2);
};

