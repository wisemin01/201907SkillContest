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
}

void Collider::Destroy()
{
	if (gameObject->collider == this)
		gameObject->collider = nullptr;

	COLLISION.Remove(this);

	SAFE_DELETE(sphereData);
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

	D3DXCreateSphere(DXUTGetD3D9Device(), radius, 20, 20, &debugMesh, nullptr);

	gameObject->SetRenderBegin(LAMBDA{
		auto device = DXUTGetD3D9Device();

		device->SetTransform(D3DTS_WORLD, &gameObject->transform->World);

		device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

		if (debugMesh)
			debugMesh->DrawSubset(0);

		device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		});
}

bool Collider::IsCollision(const Collider* col1, const Collider* col2)
{
	if (col1->sphereData != nullptr &&
		col2->sphereData != nullptr)
	{
		if (SphereData::IsCollision(col1->sphereData, col2->sphereData))
		{
			return true;
		}
		return false;
	}

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
