#pragma once
#include "Renderer.h"

class Mesh;

class MeshRenderer :
	public Renderer
{
protected:
	Mesh* mesh = nullptr;
	Shader* shader = nullptr;

public:
	MeshRenderer() {}

	virtual void Init();
	virtual void Render();
	virtual void Destroy();

	MeshRenderer& SetMesh(Mesh* mesh);
	MeshRenderer& SetShader(Shader* shader);

private:
	void NormalRender();
	void ShaderRender();

protected:
	void CustomRender(Mesh* mesh, Shader* shader, Matrix world);
};

