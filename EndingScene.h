#pragma once
#include "Scene.h"


class EndingScene :
	public Scene
{
	// Scene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Destroy() override;
};

