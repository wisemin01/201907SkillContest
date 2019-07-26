#include "DXUT.h"
#include "InputManager.h"

void InputManager::InputUpdate()
{
	for (int i = 0; i < 256; i++)
	{
		bOldKeyState[i] = bCurKeyState[i];
		bCurKeyState[i] = GetAsyncKeyState(i);
	}

	if (GetKeyDown(VK_LBUTTON))
	{
		OnLeftMouseClick(this, TouchEventArgs(MousePos));
	}

	if (GetKeyDown(VK_RBUTTON))
	{
		OnRightMouseClick(this, TouchEventArgs(MousePos));
	}
}

bool InputManager::GetKeyDown(int key)
{
	return bOldKeyState[key] == false 
		&& bCurKeyState[key] == true;
}

bool InputManager::GetkeyUp(int key)
{
	return bOldKeyState[key] == true
		&& bCurKeyState[key] == false;
}

bool InputManager::GetKeyPress(int key)
{
	return bOldKeyState[key] == true
		&& bCurKeyState[key] == true;
}

void InputManager::MouseScrollEvent(bool flag)
{
	OnMouseWheelScroll(this, flag);
}
