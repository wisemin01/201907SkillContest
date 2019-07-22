#include "DXUT.h"
#include "Transform.h"

Matrix Transform::GetWorldMatrix()
{
	Matrix world;

	Matrix S, R, T;

	Quaternion qRot;
	D3DXQuaternionRotationYawPitchRoll(&qRot, rotation.y, rotation.x, rotation.z);

	D3DXMatrixScaling(&S, scale.x, scale.y, scale.z);
	D3DXMatrixRotationQuaternion(&R, &qRot);
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);

	world = S * R * T;

	return world;
}

void Transform::Init()
{
	gameObject->transform = this;
}

void Transform::Update()
{
}

void Transform::Destroy()
{
	if (gameObject->transform == this)
		gameObject->transform = nullptr;
}
