#pragma once
#include "Singleton.h"

class Collider;
class CollisionManager : public Singleton<CollisionManager>
{
private:
	std::list<Collider*> colliderContainer;
public:

	void Add(Collider* col);
	void Remove(Collider* col);

	void CollisionCheck();
};

#define COLLISION CollisionManager::GetInstance()