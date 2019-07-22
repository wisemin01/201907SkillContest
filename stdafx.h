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

#include "Debug.h"
#include "Define.h"
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

// COMPONENT

#include "Transform.h"
#include "Renderer.h"