#pragma once
#include "Singleton.h"

class BaseResource;
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
	Texture* LoadTexture(const string& key, const string& path, int count = 0);
	Mesh* LoadMesh(const string& key, const string& path, const string& mtlPath = "");
	MaterialList* LoadMaterial(const string& key, const string& path);
	Shader* LoadShader(const string& key, const string& path);

	Texture* FindTexture(const string& key);
	Mesh* FindMesh(const string& key);
	MaterialList* FindMaterial(const string& key);
	Shader* FindShader(const string& key);

	template <typename _Ty>
	_Ty* Load(const string& key, const string& path, int count = 0)
	{
		throw exception("RESOURCE LOAD FAILED");
	}

	template <>
	Texture* Load<Texture>(const string& key, const string& path, int count)
	{
		return LoadTexture(key, path, count);
	}

	template <>
	Mesh* Load<Mesh>(const string& key, const string& path, int count)
	{
		return LoadMesh(key, path);
	}

	template <>
	MaterialList* Load<MaterialList>(const string& key, const string& path, int count)
	{
		return LoadMaterial(key, path);
	}

	template <>
	Shader* Load<Shader>(const string& key, const string& path, int count)
	{
		return LoadShader(key, path);
	}

	template <typename _Ty>
	_Ty* Find(const string& key)
	{
		throw exception("RESOURCE LOAD FAILED");
	}

	template <>
	Texture* Find<Texture>(const string& key)
	{
		return FindTexture(key);
	}

	template <>
	Mesh* Find<Mesh>(const string& key)
	{
		return FindMesh(key);
	}

	template <>
	MaterialList* Find<MaterialList>(const string& key)
	{
		return FindMaterial(key);
	}

	template <>
	Shader* Find<Shader>(const string& key)
	{
		return FindShader(key);
	}

private:
	void CreateBilBoardMesh();
};

#define RESOURCE ResourceManager::GetInstance()