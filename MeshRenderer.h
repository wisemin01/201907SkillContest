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

	void SetMesh(Mesh* mesh);
	void SetShader(Shader* shader);

protected:
	void NormalRender(Matrix mat);
	void ShaderRender(Matrix mat);
};

