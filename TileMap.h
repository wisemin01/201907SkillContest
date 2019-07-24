#pragma once
#include "GameObject.h"

class TileMap
	: public GameObject
{
public:
	// GameObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	void Load(const string& tileMapData);
};