#pragma once
#include "EventArgs.h"

class TouchEventArgs : EventArgs
{
public:
	Vector2 MousePosition = Vector2_Zero;
	bool isEndProcess = false;

	TouchEventArgs(Vector2 pos)
		: MousePosition(pos)
	{
		
	}
};

