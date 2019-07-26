#include "DXUT.h"
#include "Transform.h"

void Transform::Rotate(Vector3 degree)
{
	_rotation *= Quaternion::Rotation(degree.ToRadian());
}

Matrix Transform::GetWorldMatrix()
{
	Matrix world;

	world = Matrix::Scaling(_scale)
		* Matrix::RotationQuaternion(_rotation)
		* Matrix::Translation(_position);
	
	if (parents)
		world *= parents->World;

	return world;
}

Matrix Transform::GetRotationMatrix()
{
	return Matrix::RotationQuaternion(rotation);
}

void Transform::Init()
{
	gameObject->transform = this;

	position = Vector3::Zero;
	scale = Vector3::One;
	rotation = Quaternion::Identity;
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
