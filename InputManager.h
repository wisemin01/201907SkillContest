#pragma once
#include "Singleton.h"
#include "TouchEventArgs.h"

class InputManager : public Singleton<InputManager>
{
private:
	bool bOldKeyState[256];
	bool bCurKeyState[256];

public:
	InputManager()
	{
	}
	virtual ~InputManager()
	{
	}

	__declspec(property(get = GetMousePos)) Vector2 MousePos;

	EventHandler<TouchEventArgs> OnLeftMouseClick;
	EventHandler<TouchEventArgs> OnRightMouseClick;

	Vector2 GetMousePos()
	{
		POINT pt;

		GetCursorPos(&pt);
		ScreenToClient(DXUTGetHWND(), &pt);

		return Vector2((float)pt.x, (float)pt.y);
	}

	void InputUpdate();

	bool GetKeyDown(int key);
	bool GetkeyUp(int key);
	bool GetKeyPress(int key);
};

#define INPUT InputManager::GetInstance()