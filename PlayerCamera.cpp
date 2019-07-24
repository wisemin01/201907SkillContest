#include "DXUT.h"

#include "PlayerCamera.h"

void PlayerCamera::Init()
{
	AC(Transform);

	transform->position = Vector3(0, 0, 0);
	camOffset = Vector3(0, 30, -100);
	Camera::GetMainCamera()->up = Vector3::Up;
}

void PlayerCamera::Update()
{
	Camera::GetMainCamera()->lookAt = playerTransform->position;
	Camera::GetMainCamera()->position = Vector3::Lerp(Camera::GetMainCamera()->position, playerTransform->position + camOffset, 0.2f);
}

void PlayerCamera::Render()
{

}

void PlayerCamera::Destroy()
{
}

void PlayerCamera::SetTarget(Transform* target)
{
	playerTransform = target;
}
