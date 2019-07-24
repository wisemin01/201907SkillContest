#include "DXUT.h"
#include "CameraManager.h"

#include "Camera.h"
#include "SkyBox.h"

CameraManager::CameraManager()
{
	matProj = Matrix::PerspectiveFovLH(D3DXToRadian(45.0f), 16.f / 9.f, 1.f, 5000.f);
	DXUTGetD3D9Device()->SetTransform(D3DTS_PROJECTION, &matProj);
	SetViewMatrix();
}

CameraManager::~CameraManager()
{
	Camera::RemoveAll();
}

void CameraManager::SetViewMatrix()
{
	Camera* main = Camera::mainCamera;

	if (main)
	{
		matView = Matrix::LookAtLH(main->position, main->lookAt, main->up);
		DXUTGetD3D9Device()->SetTransform(D3DTS_VIEW, &matView);
	}
}

void CameraManager::SetSkyBox(SkyBox* skyBox)
{
	this->skyBox = skyBox;
}

Vector3 CameraManager::GetMainCamPosition()
{
	return Camera::mainCamera->position;
}

Vector3 CameraManager::GetLightPosition()
{
	return light;
}

void CameraManager::DrawSkyBox(bool zbufferMode)
{
	if (skyBox == nullptr)
		return;

	skyBox->DrawSkyBox(zbufferMode);
}
