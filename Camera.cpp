#include "DXUT.h"
#include "Camera.h"

Camera* Camera::mainCamera = nullptr;
std::map<string, Camera*> Camera::cameraContainer;


void Camera::Update()
{
}


Camera& Camera::SetPosition(Vector3 position)
{
	this->position = position;

	return *this;
}

Camera& Camera::SetLookAt(Vector3 lookAt)
{
	this->lookAt = lookAt;

	return *this;
}

Camera& Camera::SetUp(Vector3 up)
{
	this->up = up;

	return *this;
}

Vector3 Camera::GetForward()
{
	return Vector3::Normalize(lookAt - position);
}

Vector3 Camera::GetBack()
{
	return Vector3::Normalize(position - lookAt);
}

Vector3 Camera::GetRight()
{
	return Vector3::Cross(this->up, Vector3::Normalize(lookAt - position));
}

Vector3 Camera::GetLeft()
{
	return Vector3::Cross(Vector3::Normalize(lookAt - position), this->up);
}

Vector3 Camera::GetUp()
{
	return up;
}

Vector3 Camera::GetDown()
{
	return -up;
}

Camera& Camera::Create(const string& key)
{
	Camera* cam = new Camera();

	cameraContainer.insert(make_pair(key, cam));

	return *cam;
}

Camera& Camera::Find(const string& key)
{
	if (auto find = cameraContainer.find(key); find != cameraContainer.end())
		return *find->second;

	throw exception("Find Failed");
}

void Camera::Remove(const string& key)
{
	auto find = cameraContainer.find(key);

	if (find != cameraContainer.end())
	{
		cameraContainer.erase(find);
	}
}

void Camera::RemoveAll()
{
	for each (auto iter in cameraContainer)
	{
		SAFE_DELETE(iter.second);
	}

	cameraContainer.clear();
}
