#include "DXUT.h"
#include "Player.h"

void Player::Init()
{
	AC(Transform);
	AC(Rigidbody);

	ACR(MeshRenderer).SetMesh(FIND(Mesh, "Test"));

	transform->position = Vector3(0, 100, 0);
	transform->scale = Vector3::One * 0.1;

	rigidbody->useGravity = false;

	SetRenderBegin(LAMBDA{ DXUTGetD3D9Device()->SetRenderState(D3DRS_LIGHTING, false); });
	SetRenderEnd(LAMBDA{ DXUTGetD3D9Device()->SetRenderState(D3DRS_LIGHTING, true); });
}

void Player::Update()
{
	float speed = 30;

	if (INPUT.GetKeyPress('W'))
		transform->position += Vector3(0, 0, speed * Time::DeltaTime());

	if (INPUT.GetKeyPress('S'))
		transform->position += Vector3(0, 0, -speed * Time::DeltaTime());

	if (INPUT.GetKeyPress('A'))
		transform->position += Vector3(-speed * Time::DeltaTime(), 0, 0);

	if (INPUT.GetKeyPress('D'))
		transform->position += Vector3(speed * Time::DeltaTime(), 0, 0);

	cout << transform->position << endl;
}

void Player::Render()
{

}

void Player::Destroy()
{

}
