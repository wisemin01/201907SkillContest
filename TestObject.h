#pragma once
#include "GameObject.h"

class TestObject :
	public GameObject
{
private:
	Event<TouchEventArgs> *TouchEvent;
public:

	// GameObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	void OnMouseClick(object sender, TouchEventArgs args);
};

