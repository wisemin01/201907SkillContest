#include "DXUT.h"
#include "Player.h"

void Player::Init()
{
	AC(Transform);
	AC(Rigidbody);
	AC(Collider);
	AC(MeshRenderer);

	renderer->SetMesh(FIND(Mesh, "Car3"));
	renderer->SetShader(FIND(Shader, "LightShader"));

	transform->position		= Vector3(0, 100, 0);
	transform->scale		= Vector3::One;
	transform->SetRotationDegree(Vector3(0, 90, 0));

	rigidbody->UseGravity	= true;
	rigidbody->Drag			= 56;
	rigidbody->Elasticity	= 0.5f;
	rigidbody->Mass			= 1.0f;

	collider->SetAsBox(300, 300, 300);
}

void Player::Update()
{
	MoveCalculate();
}

void Player::Render()
{

}

void Player::Destroy()
{

}

void Player::OnCollision(Collider* other)
{
}

void Player::MoveCalculate()
{
	Vector3 goVec = Vector3::Zero;

	if (INPUT.GetKeyPress('W'))
		goVec += Vector3(0, 0, 1);

	if (INPUT.GetKeyPress('A'))
		goVec += Vector3(-1, 0, 0);

	if (INPUT.GetKeyPress('S'))
		goVec += Vector3(0, 0, -1);

	if (INPUT.GetKeyPress('D'))
		goVec += Vector3(1, 0, 0);

	goVec.Normalize();
	float r = D3DXToDegree(atan2f(-goVec.z, goVec.x));

	if (goVec.Length() != 0) {
		Quaternion q = Quaternion::Rotation(Vector3(0, r, 0).ToRadian());
		transform->rotation = Quaternion::SLerp(transform->rotation, q, 0.1f);

		speed = Lerp(speed, maxSpeed, 0.1f);
	}
	else
	{
		speed = Lerp(speed, minSpeed, 0.1f);
	}

	goVec = goVec * speed * Time::DeltaTime();
	rigidbody->AddForce(goVec);
}
