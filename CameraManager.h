#pragma once
#include "Singleton.h"

class SkyBox;
class CameraManager :
	public Singleton<CameraManager>
{
	friend class RenderManager;
private:
	Matrix matView;
	Matrix matProj;

	SkyBox* skyBox = nullptr;

	Vector3 light = Vector3::Zero;
public:
	CameraManager();
	~CameraManager();

	__declspec(property(get = GetLightPosition, put = SetLightPosition)) Vector3 LightPosition;
		 
	void SetViewMatrix();

	void SetSkyBox(SkyBox* skyBox);

	Matrix GetViewMatrix() { return matView; }
	Matrix GetProjMatrix() { return matProj; }

	Vector3 GetMainCamPosition();
	Vector3 GetLightPosition();

	void SetLightPosition(Vector3 light);

private:
	void DrawSkyBox(bool zbufferMode);
};

#define CAMERA CameraManager::GetInstance()