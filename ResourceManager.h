#pragma once
#include "Singleton.h"

class ResourceManager
	: public Singleton<ResourceManager>
{
public:
	void RenderBegin();
	void RenderEnd();
	void OnResetDevice();
	void OnLostDevice();
};

#define RESOURCE ResourceManager::GetInstance()