#include "DXUT.h"
#include "Car.h"

void Car::Setting(Mesh* mesh, Vector3 position)
{
	renderer->SetMesh(mesh);
	transform->position = position;
}

void Car::Init()
{
	AC(Transform);
	AC(Rigidbody);
	AC(Collider);
	AC(MeshRenderer);

	renderer->SetShader(FIND(Shader, "LightShader"));

	transform->SetRotationDegree(Vector3(0, 90, 0));
	transform->scale = Vector3::One;

	rigidbody->UseGravity = true;
	rigidbody->Drag = 56;
	rigidbody->Elasticity = 0.5f;

	collider->isTrigger = false;

	collider->SetAsBox(200, 200, 200);
}

void Car::Update()
{
}

void Car::Render()
{
}

void Car::Destroy()
{
}

void Car::OnCollision(Collider* other)
{
	
}
