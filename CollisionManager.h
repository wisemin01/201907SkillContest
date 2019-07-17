#pragma once
#include "Singleton.h"

class CollisionManager : public Singleton<CollisionManager>
{

};

#define COLLISION CollisionManager::GetInstance()