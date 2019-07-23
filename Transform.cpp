#include "DXUT.h"
#include "Transform.h"

Matrix Transform::GetWorldMatrix()
{
	Matrix world;

	Quaternion qRot = Quaternion::Rotation(rotation);

	world = Matrix::Scaling(scale)
		* Matrix::RotationQuaternion(qRot)
		* Matrix::Translation(position);
	
	if (parents)
		world *= parents->World;

	return world;
}

void Transform::Init()
{
	gameObject->transform = this;

	position = Vector3::Zero;
	scale = Vector3::One;
	rotation = Vector3::Zero;
}

void Transform::Update()
{
}

void Transform::Destroy()
{
	if (gameObject->transform == this)
		gameObject->transform = nullptr;
}

void Transform::AddChild(Transform* t)
{
	t->parents = this;
}

void Transform::RemoveChild(Transform* t)
{
	if (t->parents == this)
		t->parents = nullptr;
}
