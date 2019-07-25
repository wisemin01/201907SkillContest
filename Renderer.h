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

	virtual void SetShader(Shader* shader) {}
	virtual void SetTexture(Texture* texture) {}
	virtual void SetMesh(Mesh* mesh) {}

	// Component을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Destroy() override;

	virtual void Render() = 0;
};

