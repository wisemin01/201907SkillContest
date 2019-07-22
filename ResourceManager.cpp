#include "DXUT.h"
#include "ResourceManager.h"
#include <fstream>

#include "MeshLoader.h"
#include "SingleTexture.h"
#include "MultiTexture.h"

ResourceManager::ResourceManager()
{
	D3DXCreateSprite(DXUTGetD3D9Device(), &d3dxSprite);
	CreateBilBoardMesh();
}

ResourceManager::~ResourceManager()
{
	SAFE_RELEASE(d3dxSprite);
	SAFE_RELEASE(billBoardMesh);

	Reset();
}

void ResourceManager::RenderBegin()
{
	SAFE_EXECUTE(d3dxSprite)->Begin(D3DXSPRITE_ALPHABLEND);
}

void ResourceManager::RenderEnd()
{
	SAFE_EXECUTE(d3dxSprite)->End();
}

void ResourceManager::OnResetDevice()
{
	SAFE_EXECUTE(d3dxSprite)->OnResetDevice();
}

void ResourceManager::OnLostDevice()
{
	SAFE_EXECUTE(d3dxSprite)->OnLostDevice();
}

void ResourceManager::Reset()
{
	for each (auto iter in textureContainer)
	{
		SAFE_DELETE(iter.second);
	}

	for each (auto iter in materialContainer)
	{
		for each (auto material in (*iter.second))
		{
			SAFE_DELETE(material);
		}

		SAFE_DELETE(iter.second);
	}

	for each (auto iter in meshContainer)
	{
		SAFE_DELETE(iter.second);
	}

	for each (auto iter in shaderContainer)
	{
		SAFE_DELETE(iter.second);
	}

	textureContainer.clear();
	materialContainer.clear();
	meshContainer.clear();
	shaderContainer.clear();
}

Texture* ResourceManager::LoadTexture(const string& key, const string& path, int count)
{
	if (auto find = textureContainer.find(key); find != textureContainer.end())
		return find->second;

	Texture* tex = nullptr;

	if (count == 0)
		tex = new SingleTexture();
	else
		tex = new MultiTexture();

	tex->Add(path, count);

	textureContainer.insert(make_pair(key, tex));

	return tex;
}

Mesh* ResourceManager::LoadMesh(const string& key, const string& path, const string& mtlPath)
{
	if (auto find = meshContainer.find(key); find != meshContainer.end())
		return find->second;

	Mesh* loader = new Mesh();
	loader->Create(path, mtlPath);

	meshContainer.insert(make_pair(key, loader));

	return loader;
}

MaterialList* ResourceManager::LoadMaterial(const string& key, const string& path)
{
	if (auto find = materialContainer.find(key); find != materialContainer.end())
		return find->second;

	MaterialList* list = new MaterialList;

	char strCommand[256] = { 0 };
	ifstream InFile(path);

	if (!InFile)
	{
		return nullptr;
	}

	Material* material = nullptr;
	bool bFound = false;

	while(true)
	{
		InFile >> strCommand;
		if (!InFile)
			break;

		if (0 == strcmp(strCommand, "newmtl"))
		{
			material = new Material;
			list->push_back(material);

			InFile >> strCommand;
			material->strName = strCommand;
		}
		else if (0 == strcmp(strCommand, "map_Kd"))
		{
			InFile >> strCommand;

			int index = path.rfind("/");

			string imagePath = path.substr(0, index + 1) + strCommand;

			index = imagePath.rfind(".");
			imagePath = imagePath.substr(0, index + 1) + "png";

			material->lpDiffuse = LoadTexture(imagePath, imagePath);
		}
		else if (0 == strcmp(strCommand, "map_Ks"))
		{
			InFile >> strCommand;

			int index = path.rfind("/");

			string imagePath = path.substr(0, index + 1) + strCommand;

			index = imagePath.rfind(".");
			imagePath = imagePath.substr(0, index + 1) + "png";

			material->lpSpecular = LoadTexture(imagePath, imagePath);
		}

		InFile.ignore(1000, '\n');
	}

	InFile.close();

	materialContainer.insert(make_pair(key, list));

	return list;
}

Shader* ResourceManager::LoadShader(const string& key, const string& path)
{
	if (auto find = shaderContainer.find(key); find != shaderContainer.end())
		return find->second;

	Shader* shader = nullptr;
	DXBuffer* buffer = nullptr;
	ulong flag = 0;

#if DEBUG
	flag = D3DXSHADER_DEBUG;
#endif

	D3DXCreateEffectFromFileExA(DXUTGetD3D9Device(), path.c_str(), nullptr,
		nullptr, nullptr, flag, nullptr, &shader, &buffer);

	if (shader == nullptr && buffer != nullptr)
	{
		int size = buffer->GetBufferSize();
		object bufferPointer = buffer->GetBufferPointer();

		if (bufferPointer)
		{
			char* ch = new char[size];
			sprintf(ch, (char*)bufferPointer);

			OutputDebugStringA(ch);
			SAFE_DELETE_ARRAY(ch);
			return nullptr;
		}
	}

	shaderContainer.insert(make_pair(key, shader));

	return shader;
}

void ResourceManager::CreateBilBoardMesh()
{
	D3DXCreateMeshFVF(2, 4, D3DXMESH_32BIT | D3DXMESH_MANAGED,
		D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1, DXUTGetD3D9Device(), &billBoardMesh);

	object vp = nullptr;
	billBoardMesh->LockVertexBuffer(0, &vp);

	Vertex* v = (Vertex*)vp;

	v[0] = { Vector3(-1, 1, 0), Vector3_Zero, Vector2_Zero };
	v[0] = { Vector3(1, 1, 0), Vector3_Zero, Vector2(1, 0) };
	v[0] = { Vector3(1, -1, 0), Vector3_Zero, Vector2_One };
	v[0] = { Vector3(-1, -1, 0), Vector3_Zero, Vector2(0, 1) };

	billBoardMesh->UnlockVertexBuffer();

	object ip = nullptr;
	billBoardMesh->LockIndexBuffer(0, &ip);

	ulong* i = (ulong*)ip;

	i[0] = 0;
	i[1] = 1;
	i[2] = 3;
	i[3] = 3;
	i[4] = 1;
	i[5] = 2;

	billBoardMesh->UnlockIndexBuffer();
}
