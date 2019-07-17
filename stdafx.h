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

// MANAGER INCLUDE

#include "InputManager.h"
#include "CollisionManager.h"
#include "ObjectManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"

// COMPONENT

#include "Collider2D.h"