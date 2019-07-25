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

	transform->position = Vector3(0, 200, 0);
	transform->rotation = Vector3(0, 90, 0);
	transform->scale = Vector3::One;

	rigidbody->useGravity = true;
	rigidbody->drag = 56;

	collider->SetAsBox(100, 100, 100);
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
