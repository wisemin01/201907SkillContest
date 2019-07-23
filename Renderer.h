#pragma once
#include "Component.h"


class Renderer abstract
	: public Component 
{
public:
	std::function<void()> renderBegin;
	std::function<void()> renderEnd;
public:
	Renderer() {}
	Renderer(GameObject* base) : Component(base) {}

	// Component��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Destroy() override;

	virtual void Render() = 0;
};

