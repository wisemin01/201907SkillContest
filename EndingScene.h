#pragma once
#include "Scene.h"
class EndingScene :
	public Scene
{
	// Scene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;
};

