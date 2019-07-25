#include "DXUT.h"
#include "CollisionManager.h"

#include "Collider.h"

void CollisionManager::Add(Collider* col)
{
	colliderContainer.push_back(col);
}

void CollisionManager::Remove(Collider* col)
{
	colliderContainer.remove(col);
}

void CollisionManager::CollisionCheck()
{
	if (colliderContainer.size() < 2)
		return;

	auto end = std::prev(colliderContainer.end(), 1);

	for (auto col1 = colliderContainer.begin(); col1 != end; col1++)
	{
		for (auto col2 = std::next(col1, 1); col2 != colliderContainer.end(); col2++)
		{
			if ((*col1)->gameObject == (*col2)->gameObject)
				continue;

			if (Collider::IsCollision(*col1, *col2))
			{
				(*col1)->gameObject->OnCollisionBase(*col2);
				(*col2)->gameObject->OnCollisionBase(*col1);
			}
		}
	}
}
