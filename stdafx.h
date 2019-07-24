#pragma once

enum Window
{
	Width = 1280,
	Height = 720,
	Mode = true
};

#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <set>
#include <functional>
#include <string>

using namespace std;

#include "Math.h"
#include "Define.h"
#include "Debug.h"
#include "EventHandler.h"
#include "Time.h"
#include "Timer.h"

#include "GameObject.h"

ostream& operator<<(ostream& os, Vector2 _Val);
ostream& operator<<(ostream& os, Vector3 _Val);

// MANAGER INCLUDE

#include "InputManager.h"
#include "CollisionManager.h"
#include "ObjectManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "RenderManager.h"
#include "CameraManager.h"

// COMPONENT

#include "Transform.h"
#include "Renderer.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "Rigidbody.h"