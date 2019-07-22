#pragma once
#include "Singleton.h"

class Texture;
class Material;
class Mesh;

class ResourceManager
	: public Singleton<ResourceManager>
{
private:
	std::map<string, Texture*>		textureContainer;
	std::map<string, Mesh*>			meshContainer;
	std::map<string, MaterialList*> materialContainer;
	std::map<string, Shader*>		shaderContainer;

	LPD3DXSPRITE d3dxSprite;
	LPD3DXMESH   billBoardMesh;
public:
	ResourceManager();
	~ResourceManager();

	void RenderBegin();
	void RenderEnd();
	void OnResetDevice();
	void OnLostDevice();

	void Reset();

public:
	Texture*		LoadTexture	(const string& key, const string& path, int count = 0);
	Mesh*			LoadMesh	(const string& key, const string& path, const string& mtlPath = "");
	MaterialList*	LoadMaterial(const string& key, const string& path);
	Shader*			LoadShader	(const string& key, const string& path);

private:
	void CreateBilBoardMesh();
};

#define RESOURCE ResourceManager::GetInstance()