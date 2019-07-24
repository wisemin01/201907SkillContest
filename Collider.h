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

	struct OBBData
	{
		Vector3 center;
		Vector3 axisDir[3];
		float axisLen[3];

		static bool IsCollision(const OBBData* a, const OBBData* b);

		void Translation(const Vector3& center, const Matrix& m);
	};

	struct SphereData
	{
		Vector3 center;
		float length;

		static bool IsCollision(const SphereData* a, const SphereData* b);

		void Translation(const Vector3& center);
	};

private:

	OBBData* obbData = nullptr;
	SphereData* sphereData = nullptr;

public:
	// Component을(를) 통해 상속됨
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Destroy() = 0;

	void SetAsSphere(float radius);
	void SetAsBox(float x_width, float y_width, float z_width);

public:
	static bool IsCollision(const Collider* col1, const Collider* col2);
};

