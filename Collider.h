#pragma once
#include "Component.h"

class Matrix;
class Vector3;

class Collider :
	public Component
{
	enum ColliderType
	{
		None,
		Box,
		Sphere
	};

	struct SphereData
	{
		Vector3 center;
		float length;

		static bool IsCollision(const SphereData* a, const SphereData* b);

		void Translation(const Vector3& center);
	};

private:

	LPD3DXMESH debugMesh = nullptr;

	SphereData* sphereData = nullptr;

public:
	// Component을(를) 통해 상속됨
	virtual void Init();
	virtual void Update();
	virtual void Destroy();

	void SetAsSphere(float radius);

public:
	static bool IsCollision(const Collider* col1, const Collider* col2);
};

