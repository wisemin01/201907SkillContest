#include "DXUT.h"
#include "Transform.h"

Matrix Transform::GetWorldMatrix()
{
	Matrix world;

	Quaternion qRot = Quaternion::Rotation(rotation);

	world = Matrix::Scaling(scale)
		* Matrix::RotationQuaternion(qRot)
		* Matrix::Translation(position);

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
