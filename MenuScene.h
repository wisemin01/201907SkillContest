#pragma once
#include "Scene.h"
class MenuScene :
	public Scene
{
	// Scene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Destroy() override;
};

