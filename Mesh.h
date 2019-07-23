//--------------------------------------------------------------------------------------
// File: MeshLoader.h
//
// Wrapper class for ID3DXMesh interface. Handles loading mesh data from an .obj file
// and resource management for material textures.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#ifndef _MESHLOADER_H_
#define _MESHLOADER_H_

#pragma once
#include "BaseResource.h"

// Used for a hashtable vertex cache when creating the mesh from a .obj file
struct CacheEntry
{
	UINT index;
	CacheEntry* pNext;
};


class Mesh : BaseResource
{
public:
	Mesh();
	~Mesh();

	HRESULT Create(const string& strFilename, const string& mtlFileName = "");
	void    Destroy();

	UINT    GetNumMaterials() const
	{
		return (*m_Materials).size();
	}
	Material* GetMaterial(UINT iMaterial)
	{
		return (*m_Materials)[iMaterial];
	}

	ID3DXMesh* GetMesh()
	{
		return m_pMesh;
	}

public:

	HRESULT LoadGeometryFromOBJ(const string& strFilename, const string& mtlFileName);
	// HRESULT LoadMaterialsFromMTL(wstring  strFileName, wstring strMaterialName, Material * pMaterial);

	DWORD   AddVertex(UINT hash, Vertex* pVertex);
	void    DeleteCache();

	ID3DXMesh* m_pMesh;         // Encapsulated D3DX Mesh

	CGrowableArray <CacheEntry*> m_VertexCache;   // Hashtable cache for locating duplicate vertices
	CGrowableArray <Vertex> m_Vertices;      // Filled and copied to the vertex buffer
	CGrowableArray <DWORD> m_Indices;       // Filled and copied to the index buffer
	CGrowableArray <DWORD> m_Attributes;    // Filled and copied to the attribute buffer
	vector <Material*>* m_Materials = nullptr;     // Holds material properties per subset
};

#endif // _MESHLOADER_H_

