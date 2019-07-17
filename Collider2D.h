#pragma once
#include "Component.h"

class Collider2D :
	public Component
{
private:
	RECT localRange;
public:
	__declspec(property(get = GetRange)) RECT Range;
	__declspec(property(get = GetLocalRange)) RECT LocalRange;

	RECT GetRange()
	{
		
	}

	RECT GetLocalRange()
	{
		return localRange;
	}

public:
	static bool IsCollision(Collider2D* o1, Collider2D* o2, RECT& out_collisionRect)
	{
		if (IntersectRect(&o1->Range, &o2->Range, &out_collisionRect))
		{
			return true;
		}

		return false;
	}
};