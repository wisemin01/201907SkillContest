#include "DXUT.h"
#include "Collider.h"

void Collider::Init()
{
}

void Collider::Update()
{
	if (sphereData)
		sphereData->Translation(gameObject->transform->position);

	if (obbData)
		obbData->Translation(gameObject->transform->position, gameObject->transform->MatRotation);
}

void Collider::Destroy()
{
}

void Collider::SetAsSphere(float radius)
{
	if (sphereData)
	{
		SAFE_DELETE(sphereData);
	}

	sphereData = new SphereData();

	sphereData->center = gameObject->transform->position;
	sphereData->length = radius;
}

void Collider::SetAsBox(float x_width, float y_width, float z_width)
{
	SetAsSphere(max(x_width, max(y_width, z_width)));

	if (obbData)
	{
		SAFE_DELETE(obbData);
	}

	obbData = new OBBData();

	obbData->center = gameObject->transform->position;

	obbData->axisDir[0] = Vector3(1.0f, 0.0f, 0.0f);
	obbData->axisDir[1] = Vector3(0.0f, 1.0f, 0.0f);
	obbData->axisDir[2] = Vector3(0.0f, 0.0f, 1.0f);

	obbData->axisLen[0] = x_width;
	obbData->axisLen[1] = y_width;
	obbData->axisLen[2] = z_width;
}

bool Collider::IsCollision(const Collider* col1, const Collider* col2)
{
	if (col1->sphereData != nullptr &&
		col2->sphereData != nullptr)
	{
		// 1차 구 충돌 검사 실시
		if (SphereData::IsCollision(col1->sphereData, col2->sphereData))
		{
			if (col1->obbData != nullptr &&
				col2->obbData != nullptr)
			{
				// 2차 OBB 충돌 검사 실시

				if (OBBData::IsCollision(col1->obbData, col2->obbData))
				{
					// 성공시
					return true;
				}

				return false;
			}
			
			// OBB DATA 가 없을경우
			return true;
		}
		return false;
	}

	// 두 물체의 충돌체가 정확하지 않으면 false 반환
	return false;
}

bool Collider::OBBData::IsCollision(const OBBData* Box1, const OBBData* Box2)
{
	double c[3][3];
	double absC[3][3];
	double d[3];

	double r0, r1, r;
	int i;

	const double cutoff = 0.999999;
	bool existsParallelPair = false;

	Vector3 diff = Box1->center - Box2->center;

	for (i = 0; i < 3; ++i)
	{
		c[0][i] = D3DXVec3Dot(&Box1->axisDir[0], &Box2->axisDir[i]);
		absC[0][i] = abs(c[0][i]);
		if (absC[0][i] > cutoff)
			existsParallelPair = true;
	}

	d[0] = D3DXVec3Dot(&diff, &Box1->axisDir[0]);
	r = abs(d[0]);
	r0 = Box1->axisLen[0];
	r1 = Box2->axisLen[0] * absC[0][0] + Box2->axisLen[1] * absC[0][1] + Box2->axisLen[2] * absC[0][2];

	if (r > r0 + r1)
		return FALSE;

	for (i = 0; i < 3; ++i)
	{
		c[1][i] = D3DXVec3Dot(&Box1->axisDir[1], &Box2->axisDir[i]);
		absC[1][i] = abs(c[1][i]);
		if (absC[1][i] > cutoff)
			existsParallelPair = true;
	}

	d[1] = D3DXVec3Dot(&diff, &Box1->axisDir[1]);
	r = abs(d[1]);
	r0 = Box1->axisLen[1];
	r1 = Box2->axisLen[0] * absC[1][0] + Box2->axisLen[1] * absC[1][1] + Box2->axisLen[2] * absC[1][2];

	if (r > r0 + r1)
		return FALSE;

	for (i = 0; i < 3; ++i)
	{
		c[2][i] = D3DXVec3Dot(&Box1->axisDir[2], &Box2->axisDir[i]);
		absC[2][i] = abs(c[2][i]);
		if (absC[2][i] > cutoff)
			existsParallelPair = true;
	}

	d[2] = D3DXVec3Dot(&diff, &Box1->axisDir[2]);
	r = abs(d[2]);
	r0 = Box1->axisLen[2];
	r1 = Box2->axisLen[0] * absC[2][0] + Box2->axisLen[1] * absC[2][1] + Box2->axisLen[2] * absC[2][2];

	if (r > r0 + r1)
		return FALSE;

	r = abs(D3DXVec3Dot(&diff, &Box2->axisDir[0]));
	r0 = Box1->axisLen[0] * absC[0][0] + Box1->axisLen[1] * absC[1][0] + Box1->axisLen[2] * absC[2][0];
	r1 = Box2->axisLen[0];

	if (r > r0 + r1)
		return FALSE;

	r = abs(D3DXVec3Dot(&diff, &Box2->axisDir[1]));
	r0 = Box1->axisLen[0] * absC[0][1] + Box1->axisLen[1] * absC[1][1] + Box1->axisLen[2] * absC[2][1];
	r1 = Box2->axisLen[1];

	if (r > r0 + r1)
		return FALSE;

	r = abs(D3DXVec3Dot(&diff, &Box2->axisDir[2]));
	r0 = Box1->axisLen[0] * absC[0][2] + Box1->axisLen[1] * absC[1][2] + Box1->axisLen[2] * absC[2][2];
	r1 = Box2->axisLen[2];

	if (r > r0 + r1)
		return FALSE;

	if (existsParallelPair == true)
		return TRUE;

	r = abs(d[2] * c[1][0] - d[1] * c[2][0]);
	r0 = Box1->axisLen[1] * absC[2][0] + Box1->axisLen[2] * absC[1][0];
	r1 = Box2->axisLen[1] * absC[0][2] + Box2->axisLen[2] * absC[0][1];
	if (r > r0 + r1)
		return FALSE;

	r = abs(d[2] * c[1][1] - d[1] * c[2][1]);
	r0 = Box1->axisLen[1] * absC[2][1] + Box1->axisLen[2] * absC[1][1];
	r1 = Box2->axisLen[0] * absC[0][2] + Box2->axisLen[2] * absC[0][0];
	if (r > r0 + r1)
		return FALSE;

	r = abs(d[2] * c[1][2] - d[1] * c[2][2]);
	r0 = Box1->axisLen[1] * absC[2][2] + Box1->axisLen[2] * absC[1][2];
	r1 = Box2->axisLen[0] * absC[0][1] + Box2->axisLen[1] * absC[0][0];
	if (r > r0 + r1)
		return FALSE;

	r = abs(d[0] * c[2][0] - d[2] * c[0][0]);
	r0 = Box1->axisLen[0] * absC[2][0] + Box1->axisLen[2] * absC[0][0];
	r1 = Box2->axisLen[1] * absC[1][2] + Box2->axisLen[2] * absC[1][1];
	if (r > r0 + r1)
		return FALSE;

	r = abs(d[0] * c[2][1] - d[2] * c[0][1]);
	r0 = Box1->axisLen[0] * absC[2][1] + Box1->axisLen[2] * absC[0][1];
	r1 = Box2->axisLen[0] * absC[1][2] + Box2->axisLen[2] * absC[1][0];
	if (r > r0 + r1)
		return FALSE;

	r = abs(d[0] * c[2][2] - d[2] * c[0][2]);
	r0 = Box1->axisLen[0] * absC[2][2] + Box1->axisLen[2] * absC[0][2];
	r1 = Box2->axisLen[0] * absC[1][1] + Box2->axisLen[1] * absC[1][0];
	if (r > r0 + r1)
		return FALSE;

	r = abs(d[1] * c[0][0] - d[0] * c[1][0]);
	r0 = Box1->axisLen[0] * absC[1][0] + Box1->axisLen[1] * absC[0][0];
	r1 = Box2->axisLen[1] * absC[2][2] + Box2->axisLen[2] * absC[2][1];
	if (r > r0 + r1)
		return FALSE;

	r = abs(d[1] * c[0][1] - d[0] * c[1][1]);
	r0 = Box1->axisLen[0] * absC[1][1] + Box1->axisLen[1] * absC[0][1];
	r1 = Box2->axisLen[0] * absC[2][2] + Box2->axisLen[2] * absC[2][0];
	if (r > r0 + r1)
		return FALSE;

	r = abs(d[1] * c[0][2] - d[0] * c[1][2]);
	r0 = Box1->axisLen[0] * absC[1][2] + Box1->axisLen[1] * absC[0][2];
	r1 = Box2->axisLen[0] * absC[2][1] + Box2->axisLen[1] * absC[2][0];
	if (r > r0 + r1)
		return FALSE;

	return TRUE;
}

void Collider::OBBData::Translation(const Vector3& center, const Matrix& m)
{
	axisDir[0] = Vector3::TransformNormal(axisDir[0], m);
	axisDir[1] = Vector3::TransformNormal(axisDir[1], m);
	axisDir[2] = Vector3::TransformNormal(axisDir[2], m);

	this->center = center;
}

bool Collider::SphereData::IsCollision(const SphereData* a, const SphereData* b)
{
	Vector3 diff = b->center - a->center;
	float distance = Vector3::Length(diff);

	if (distance <= (a->length + b->length))
	{
		return true;
	}

	return false;
}

void Collider::SphereData::Translation(const Vector3& center)
{
	this->center = center;
}
