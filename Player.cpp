#include "DXUT.h"
#include "Player.h"

void Player::Init()
{
	AC(Transform);
	AC(Rigidbody);

	ACR(MeshRenderer).SetMesh(FIND(Mesh, "Test"))
		.SetShader(FIND(Shader, "LightShader"));

	transform->position = Vector3(0, 200, 0);
	transform->scale = Vector3::One * 0.05;

	rigidbody->useGravity = false;
	rigidbody->drag = 56;
}

void Player::Update()
{
	float speed = 90;

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

	ERROR_LOG("ASD");
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
