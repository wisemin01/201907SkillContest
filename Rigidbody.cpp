#include "DXUT.h"
#include "Rigidbody.h"

Vector3 Rigidbody::Gravity = Vector3(0.0f, -9.8f, 0.0f);

void Rigidbody::Init()
{
	gameObject->rigidbody = this;
}

void Rigidbody::Update()
{
	if (useGravity)
		force -= Gravity;

	velocity += force;

	if (gameObject->transform)
		gameObject->transform->position += velocity;

	velocity *= drag * Time::DeltaTime();
}

void Rigidbody::Destroy()
{
	if (gameObject->rigidbody == this)
		gameObject->rigidbody = nullptr;
}

void Rigidbody::AddForce(Vector3 force)
{
	this->force += force;
}

void Rigidbody::AddForce(float x, float y, float z)
{
	this->force += Vector3(x, y, z);
}
