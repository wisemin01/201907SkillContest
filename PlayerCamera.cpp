#include "DXUT.h"

#include "PlayerCamera.h"

void PlayerCamera::Init()
{
	AC(Transform);

	Camera::Create("PlayerCamera")
		.SetPosition(Vector3(0, 0, -200))
		.SetLookAt(Vector3::Zero)
		.SetUp(Vector3::Up)
		.SetMain();

	transform->position = Vector3(0, 0, 0);
	camOffset = Vector3(0, 1800, -360);
	Camera::GetMainCamera()->up = Vector3::Up;

	MouseWheelEvent = CreateEvent(bool, OnMouseWheelScroll);
	INPUT.OnMouseWheelScroll += MouseWheelEvent;
}

void PlayerCamera::Update()
{
	Camera::GetMainCamera()->lookAt = playerTransform->position;
	Camera::GetMainCamera()->position = Vector3::Lerp(Camera::GetMainCamera()->position, playerTransform->position + camOffset, 0.5f);
}

void PlayerCamera::Render()
{

}

void PlayerCamera::Destroy()
{
	INPUT.OnMouseWheelScroll -= MouseWheelEvent;
}

void PlayerCamera::SetTarget(Transform* target)
{
	playerTransform = target;
}

void PlayerCamera::OnMouseWheelScroll(object sender, bool flag)
{
	camOffset += flag ? Vector3(0, -100, 50) : Vector3(0, 100, -50);
}
