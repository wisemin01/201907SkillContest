#include "DXUT.h"
#include "Tile.h"

void Tile::Init()
{
	AC(Transform);
	AC(MeshRenderer);
	AC(Collider);

	AC(Rigidbody);

	rigidbody->UseGravity = false;
	rigidbody->IsFreeze = true;
	rigidbody->Mass = 3.0f;
}

void Tile::Update()
{
}

void Tile::Render()
{
}

void Tile::Destroy()
{
}

Tile& Tile::SetMesh(Mesh* mesh)
{
	renderer->SetMesh(mesh);
	return *this;
}

Tile& Tile::SetShader(Shader* shader)
{
	renderer->SetShader(shader);
	return *this;
}

Tile& Tile::SetPosition(const Vector3& pos)
{
	transform->position = pos;
	return *this;
}

Tile& Tile::SetRotation(const Vector3& rot)
{
	transform->SetRotationDegree(rot);
	return *this;
}

Tile& Tile::SetCollider(float x, float y, float z)
{
	collider->SetAsBox(x, y, z);
	return *this;
}
