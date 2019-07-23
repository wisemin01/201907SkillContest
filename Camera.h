#pragma once

class Camera
{
	friend class CameraManager;
	friend class SkyBox;
public:
	Camera() {}
	Camera(Vector3 pos, Vector3 look = Vector3(0.f, 0.f, 0.f), Vector3 up = Vector3(0.f, 1.f, 0.f))
		: position(pos), lookAt(look), up(up) {}

	Vector3 position	= Vector3::Zero;
	Vector3 lookAt		= Vector3::Zero;
	Vector3 up			= Vector3::Zero;

	Camera& SetMain() { Camera::mainCamera = this; return *this; }

	virtual void Update();

	Camera& SetPosition(Vector3 position);
	Camera& SetLookAt(Vector3 lookAt);
	Camera& SetUp(Vector3 up);

private:

	static Camera* mainCamera;

	// STATIC FIELD
public:

	static Camera& Create(const string& key);
	static Camera& Find(const string& key);
	static void Remove(const string& key);
	static void RemoveAll();

private:
	static std::map<string, Camera*> cameraContainer;
};