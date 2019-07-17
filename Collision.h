#pragma once


struct Collision
{
	Collision(RECT overlap, GameObject* other)
		: overlapRect(overlap), gameObject(other) {	}

	RECT overlapRect;
	GameObject* gameObject;
};

