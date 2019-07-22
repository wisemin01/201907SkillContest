#pragma once
#include "Component.h"


class Renderer abstract
	: public Component 
{
public:
	// Component을(를) 통해 상속됨
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Destroy() = 0;

	virtual void Render() = 0;
};

