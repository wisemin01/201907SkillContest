#include "DXUT.h"

#include "PlayerCamera.h"

void PlayerCamera::Init()
{
	TouchEvent = CreateEvent(TouchEventArgs, OnMouseClick);
	INPUT.OnLeftMouseClick += TouchEvent;

	AC(Transform);

	transform->position = Vector3(0, 0, 0);
	camOffset = Vector3(0, 30, -1);
}

void PlayerCamera::Update()
{
	Camera::GetMainCamera()->lookAt = playerTransform->position;
	Camera::GetMainCamera()->position = playerTransform->position + camOffset;
}

void PlayerCamera::Render()
{

}

void PlayerCamera::Destroy()
{
	INPUT.OnLeftMouseClick.SafeRemove(TouchEvent);
}

void PlayerCamera::OnMouseClick(object sender, TouchEventArgs args)
{
	cout << args.MousePosition << endl;
}

void PlayerCamera::SetTarget(Transform* target)
{
	playerTransform = target;
}
