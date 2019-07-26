#include "DXUT.h"
#include "Rigidbody.h"

Vector3 Rigidbody::Gravity = Vector3(0.0f, -9.8f * 10, 0.0f);

void Rigidbody::Init()
{
	gameObject->rigidbody = this;
}

void Rigidbody::Update()
{
	if (_useGravity == true && _isOnGround == false)
	 	_force += Gravity * Time::DeltaTime() * Mass;

	_velocity += _force;
	_force = Vector3::Zero;

	if (gameObject->transform)
		gameObject->transform->position += _velocity;

	float real_drag = _drag * Time::DeltaTime();

	if (real_drag >= 1.0f) real_drag = 0.99f;
	
	_velocity *= real_drag;

	_isOnGround = false;
}

void Rigidbody::Destroy()
{
	if (gameObject->rigidbody == this)
		gameObject->rigidbody = nullptr;
}

void Rigidbody::AddForce(Vector3 force)
{
	this->_force += force;
}

void Rigidbody::AddForce(float x, float y, float z)
{
	this->_force += Vector3(x, y, z);
}

void Rigidbody::OnCollision(Transform* otherTransform, Rigidbody* otherRigidbody)
{
	if (_isKinematic)
		return;

	if (_isFreeze)
		return;

	if (otherTransform->gameObject->collider->isTrigger
		|| gameObject->collider->isTrigger)
	{
		return;
	}

	if (otherRigidbody && otherRigidbody->_isKinematic) {
		_isOnGround = true;
	
		if (gameObject->rigidbody->_velocity.y < 0)
			gameObject->rigidbody->_velocity.y = 0;

		gameObject->rigidbody->AddForce(Vector3::Up * 50.0f * Time::DeltaTime() * Mass);
		return;
	}

	if (_isFreezeRotation == false)
	{
		if (otherTransform->position.x > gameObject->transform->position.x) 
		{
			if (otherTransform->position.y > gameObject->transform->position.y)
				gameObject->transform->Rotate(Vector3(0, -5, 0)); // 1사분면
			else
				gameObject->transform->Rotate(Vector3(0, 5, 0)); // 4사분면
		}
		else
		{
			if (otherTransform->position.y > gameObject->transform->position.y)
				gameObject->transform->Rotate(Vector3(0, 5, 0)); // 2
			else
				gameObject->transform->Rotate(Vector3(0, -5, 0)); // 3
		}
	}

	constexpr float reflectCoefficient = 300.0f;
	constexpr float velocityDragCoefficient = 0.7f;
	
	Vector3 otherVelocity = otherRigidbody ? otherRigidbody->_velocity : Vector3::Zero;
	float otherMass = otherRigidbody ? otherRigidbody->_mass : 1.0f;
	
	Vector3 pushDirection = Vector3::Normalize(gameObject->transform->position - otherTransform->position);
	Vector3 pushPower = pushDirection * reflectCoefficient;
	
	pushPower += gameObject->rigidbody->_velocity * _elasticity;
	pushPower -= gameObject->rigidbody->_velocity * (1.0f - _elasticity);
	
	if (_isOnGround == true)
		pushPower = Vector3::Up;
	
	pushPower += otherVelocity * velocityDragCoefficient;
	
	AddForce(pushPower * otherMass * Time::DeltaTime());
}
