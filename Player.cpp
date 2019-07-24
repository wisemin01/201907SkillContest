#include "DXUT.h"
#include "Player.h"

void Player::Init()
{
	AC(Transform);
	AC(Rigidbody);

	ACR(MeshRenderer).SetMesh(FIND(Mesh, "Building"))
		//.SetShader(FIND(Shader, "LightShader"))
		;

	transform->position = Vector3(0, 50, 0);
	transform->scale = Vector3::One * 0.01;

	rigidbody->useGravity = false;
	rigidbody->drag = 56;

	AC(Collider)->SetAsSphere(50);
}

void Player::Update()
{
	float speed = 30;

	if (INPUT.GetKeyPress('W'))
		rigidbody->AddForce(Vector3(0, 0, speed * Time::DeltaTime()));

	if (INPUT.GetKeyPress('A'))
		rigidbody->AddForce(Vector3(-speed * Time::DeltaTime(), 0, 0));

	if (INPUT.GetKeyPress('S'))
		rigidbody->AddForce(Vector3(0, 0, -speed * Time::DeltaTime()));

	if (INPUT.GetKeyPress('D'))
		rigidbody->AddForce(Vector3(speed * Time::DeltaTime(), 0, 0));

	if (INPUT.GetKeyPress(VK_SPACE))
		rigidbody->AddForce(Vector3(0, speed * Time::DeltaTime(), 0));

	if (INPUT.GetKeyPress(VK_LSHIFT))
		rigidbody->AddForce(Vector3(0, -speed * Time::DeltaTime(), 0));


	CAMERA.LightPosition = transform->position;
}

void Player::Render()
{

}

void Player::Destroy()
{

}

void Player::OnCollision(Collider* other)
{
	DEBUG_LOG("Ãæµ¹!" << Time::Now());
}
