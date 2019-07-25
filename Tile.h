#pragma once
#include "GameObject.h"

class Tile :
	public GameObject
{
private:

public:
	// GameObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;
	
	Tile& SetMesh(Mesh* mesh);
	Tile& SetShader(Shader* shader);
	Tile& SetPosition(const Vector3& pos);
	Tile& SetRotation(const Vector3& rot);
	Tile& SetCollider(float x, float y, float z);
};

