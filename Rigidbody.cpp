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
	 	force += Gravity * Time::DeltaTime();

	velocity += force;
	force = Vector3::Zero;

	if (gameObject->transform)
		gameObject->transform->position += velocity;

	float real_drag = drag * Time::DeltaTime();

	if (real_drag >= 1.0f) real_drag = 0.99f;
	
	velocity *= real_drag;
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

void Rigidbody::OnCollision(Transform* otherTransform, Rigidbody* otherRigidbody)
{
	if (isKinematic)
		return;

	constexpr float reflectCoefficient = 10000.0f;
	constexpr float velocityDragCoefficient = 0.7f;

	/*
	gameObject->rigidbody->velocity = Vector3::Zero;

	Vector3 otherVelocity = otherRigidbody ? otherRigidbody->velocity : Vector3::Zero;
	float otherMass = otherRigidbody ? otherRigidbody->mass : 0.0f;

	Vector3 pushDirection = Vector3::Normalize(gameObject->transform->position - otherTransform->position) * reflectCoefficient;
	pushDirection += otherVelocity * velocityDragCoefficient;

	AddForce(pushDirection * otherMass * Time::DeltaTime());

	DEBUG_LOG(pushDirection);
	*/

	float length = gameObject->rigidbody->velocity.Length();

	Vector3 pushDirection = Vector3::Normalize(gameObject->transform->position - otherTransform->position);

	Vector3 data = AABBData::Intersect(gameObject->collider->aabbData, otherTransform->gameObject->collider->aabbData);
	
	float interX = data.x;
	float interY = data.y;
	float interZ = data.z;

	if (interX > interY && interX > interZ)
	{
		// X 기준 충돌
	}
	else if(interY > interX && interY > interZ)
	{
		// Y
	}
	else
	{
		// Z
	}

	pushDirection *= length;

	AddForce(pushDirection);
}
