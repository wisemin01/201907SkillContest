#include "DXUT.h"
#include "Collider.h"

void Collider::Init()
{
	gameObject->collider = this;

	COLLISION.Add(this);
}

void Collider::Update()
{
	if (sphereData)
		sphereData->Translation(gameObject->transform->position);

	if (aabbData)
		aabbData->Translation(gameObject->transform->position);
}

void Collider::Destroy()
{
	if (gameObject->collider == this)
		gameObject->collider = nullptr;

	type = None;

	COLLISION.Remove(this);

	SAFE_DELETE(sphereData);
	SAFE_DELETE(aabbData);
}

void Collider::SetAsSphere(float radius)
{
	if (sphereData)
	{
		SAFE_DELETE(sphereData);
	}

	sphereData = new SphereData(radius);

	sphereData->center = gameObject->transform->position;

	type = Sphere;
}

void Collider::SetAsBox(float x, float y, float z)
{
	if (aabbData)
	{
		SAFE_DELETE(aabbData);
	}

	aabbData = new AABBData(x, y, z);

	aabbData->center = gameObject->transform->position;

	type = Box;
}

bool Collider::IsCollision(const Collider* col1, const Collider* col2)
{
	if (col1->type == None)
		return false;

	if (col2->type == None)
		return false;

	if (col1->type == Sphere &&
		col2->type == Sphere)
		return SphereData::IsCollision(col1->sphereData, col2->sphereData);

	if (col1->type == Box &&
		col2->type == Box)
		return AABBData::IsCollision(col1->aabbData, col2->aabbData);

	if (col1->type == Box &&
		col2->type == Sphere)
		return MixData::IsCollision(col1->aabbData, col2->sphereData);

	if (col1->type == Sphere &&
		col2->type == Box)
		return MixData::IsCollision(col1->sphereData, col2->aabbData);

	return false;
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

bool Collider::AABBData::IsCollision(const AABBData* a, const AABBData* b)
{
	Vector3 amax = a->GetMax();
	Vector3 bmax = b->GetMax();

	Vector3 amin = a->GetMin();
	Vector3 bmin = b->GetMin();

	if (amax.x < bmin.x || amin.x > bmax.x) return 0;
	if (amax.y < bmin.y || amin.y > bmax.y) return 0;
	if (amax.z < bmin.z || amin.z > bmax.z) return 0;
	return 1;

	return false;
}

void Collider::AABBData::Translation(const Vector3& center)
{
	this->center = center;
}

bool Collider::MixData::IsCollision(const AABBData* a, const SphereData* b)
{
	Vector3 min = a->GetMin();
	Vector3 max = a->GetMax();

	Vector3 sphereC = b->center;
	float radius = b->length;

	if (max.x < (sphereC.x - radius) || min.x > (sphereC.x + radius)) return false;
	if (max.y < (sphereC.y - radius) || min.y > (sphereC.y + radius)) return false;
	if (max.z < (sphereC.z - radius) || min.z > (sphereC.z + radius)) return false;

	return true;
}

bool Collider::MixData::IsCollision(const SphereData* a, const AABBData* b)
{
	return IsCollision(b, a);
}
