//--------------------------------------------------------------------------------------
// File: MeshLoader.cpp
//
// Wrapper class for ID3DXMesh interface. Handles loading mesh data from an .obj file
// and resource management for material textures.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#include "DXUT.h"
#include "SDKmisc.h"
#pragma warning(disable: 4995)
#include "Mesh.h"
#include <fstream>
using namespace std;
#pragma warning(default: 4995)


// Vertex declaration
D3DVERTEXELEMENT9 VERTEX_DECL[] =
{
	{ 0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_POSITION, 0},
	{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_NORMAL,   0},
	{ 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_TEXCOORD, 0},
	D3DDECL_END()
};


//--------------------------------------------------------------------------------------
Mesh::Mesh()
{
	m_pMesh = NULL;
}


//--------------------------------------------------------------------------------------
Mesh::~Mesh()
{
	Destroy();
}


//--------------------------------------------------------------------------------------
void Mesh::Destroy()
{
	m_Vertices.RemoveAll();
	m_Indices.RemoveAll();
	m_Attributes.RemoveAll();

	SAFE_RELEASE(m_pMesh);
}


//--------------------------------------------------------------------------------------
HRESULT Mesh::Create(const string& strFilename, const string& mtlFileName)
{
	HRESULT hr;
	// Start clean
	Destroy();


	// Load the vertex buffer, index buffer, and subset information from a file. In this case, 
	// an .obj file was chosen for simplicity, but it's meant to illustrate that ID3DXMesh objects
	// can be filled from any mesh file format once the necessary data is extracted from file.
	V_RETURN(LoadGeometryFromOBJ(strFilename, mtlFileName));

	// Create the encapsulated mesh
	ID3DXMesh* pMesh = NULL;
	V_RETURN(D3DXCreateMesh(m_Indices.GetSize() / 3, m_Vertices.GetSize(),
		D3DXMESH_MANAGED | D3DXMESH_32BIT, VERTEX_DECL,
		DXUTGetD3D9Device(), &pMesh));

	// Copy the vertex data
	Vertex* pVertex;
	V_RETURN(pMesh->LockVertexBuffer(0, (void**)& pVertex));
	memcpy(pVertex, m_Vertices.GetData(), m_Vertices.GetSize() * sizeof(Vertex));
	pMesh->UnlockVertexBuffer();
	m_Vertices.RemoveAll();

	// Copy the index data
	DWORD* pIndex;
	V_RETURN(pMesh->LockIndexBuffer(0, (void**)& pIndex));
	memcpy(pIndex, m_Indices.GetData(), m_Indices.GetSize() * sizeof(DWORD));
	pMesh->UnlockIndexBuffer();
	m_Indices.RemoveAll();

	// Copy the attribute data
	DWORD* pSubset;
	V_RETURN(pMesh->LockAttributeBuffer(0, &pSubset));
	memcpy(pSubset, m_Attributes.GetData(), m_Attributes.GetSize() * sizeof(DWORD));
	pMesh->UnlockAttributeBuffer();
	m_Attributes.RemoveAll();

	// Reorder the vertices according to subset and optimize the mesh for this graphics 
	// card's vertex cache. When rendering the mesh's triangle list the vertices will 
	// cache hit more often so it won't have to re-execute the vertex shader.
	DWORD* aAdjacency = new DWORD[pMesh->GetNumFaces() * 3];
	if (aAdjacency == NULL)
		return E_OUTOFMEMORY;

	V(pMesh->GenerateAdjacency(1e-6f, aAdjacency));
	V(pMesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE, aAdjacency, NULL, NULL, NULL));

	SAFE_DELETE_ARRAY(aAdjacency);
	m_pMesh = pMesh;

	return S_OK;
}


//--------------------------------------------------------------------------------------
HRESULT Mesh::LoadGeometryFromOBJ(const string& strFileName, const string& mtlFileName)
{
	string strMaterialFilename;
	string strObjFileName = strFileName;

	// Create temporary storage for the input data. Once the data has been loaded into
	// a reasonable format we can create a D3DXMesh object and load it with the mesh data.
	CGrowableArray <D3DXVECTOR3> Positions;
	CGrowableArray <D3DXVECTOR2> TexCoords;
	CGrowableArray <D3DXVECTOR3> Normals;

	DWORD dwCurSubset = 0;

	// File input
	char strCommand[256] = { 0 };
	ifstream InFile(strObjFileName);

	if (!InFile)
		return DXTRACE_ERR(L"wifstream::open", E_FAIL);

	while(true)
	{
		InFile >> strCommand;

		if (!InFile)
			break;

		if (0 == strcmp(strCommand, "#"))
		{
			// Comment
		}
		else if (0 == strcmp(strCommand, "v"))
		{
			// Vertex Position
			float x, y, z;
			InFile >> x >> y >> z;
			Positions.Add(D3DXVECTOR3(x, y, z));
		}
		else if (0 == strcmp(strCommand, "vt"))
		{
			// Vertex TexCoord
			float u, v;
			InFile >> u >> v;
			TexCoords.Add(D3DXVECTOR2(u, 1.f - v));
		}
		else if (0 == strcmp(strCommand, "vn"))
		{
			// Vertex Normal
			float x, y, z;
			InFile >> x >> y >> z;
			Normals.Add(D3DXVECTOR3(x, y, z));
		}
		else if (0 == strcmp(strCommand, "f"))
		{
			// Face
			UINT iPosition, iTexCoord, iNormal;
			Vertex vertex;

			for (UINT iFace = 0; iFace < 3; iFace++)
			{
				ZeroMemory(&vertex, sizeof(Vertex));

				// OBJ format uses 1-based arrays
				InFile >> iPosition;
				vertex.position = Positions[iPosition - 1];

				if ('/' == InFile.peek())
				{
					InFile.ignore();

					if ('/' != InFile.peek())
					{
						// Optional texture coordinate
						InFile >> iTexCoord;
						vertex.texcoord = TexCoords[iTexCoord - 1];
					}

					if ('/' == InFile.peek())
					{
						InFile.ignore();

						// Optional vertex normal
						InFile >> iNormal;
						vertex.normal = Normals[iNormal - 1];
					}
				}

				// If a duplicate vertex doesn't exist, add this vertex to the Vertices
				// list. Store the index in the Indices array. The Vertices and Indices
				// lists will eventually become the Vertex Buffer and Index Buffer for
				// the mesh.
				DWORD index = AddVertex(iPosition, &vertex);
				if (index == (DWORD)-1)
					return E_OUTOFMEMORY;

				m_Indices.Add(index);
			}
			m_Attributes.Add(dwCurSubset);
		}
		else if (0 == strcmp(strCommand, "mtllib"))
		{
			// Material library
			InFile >> strMaterialFilename;

			int index = strObjFileName.rfind("/");
			strMaterialFilename = strObjFileName.substr(0, index + 1) + strMaterialFilename;

			if (mtlFileName == "")
				m_Materials = RESOURCE.LoadMaterial(strMaterialFilename, strMaterialFilename);
			else
				m_Materials = RESOURCE.LoadMaterial(mtlFileName, strMaterialFilename);
		}

		else if (0 == strcmp(strCommand, "usemtl"))
		{
			// Material
			char strName[MAX_PATH] = { 0 };
			InFile >> strName;

			for (int iMaterial = 0; iMaterial < m_Materials->size(); iMaterial++)
			{
				Material* pCurMaterial = (*m_Materials)[iMaterial];
				if (0 == strcmp(pCurMaterial->strName.c_str(), strName))
				{
					dwCurSubset = iMaterial;
					break;
				}
			}
		}
		InFile.ignore(1000, '\n');
	}

	// Cleanup
	InFile.close();
	DeleteCache();
	return S_OK;
}


//--------------------------------------------------------------------------------------
DWORD Mesh::AddVertex(UINT hash, Vertex* pVertex)
{
	// If this vertex doesn't already exist in the Vertices list, create a new entry.
	// Add the index of the vertex to the Indices list.
	bool bFoundInList = false;
	DWORD index = 0;

	// Since it's very slow to check every element in the vertex list, a hashtable stores
	// vertex indices according to the vertex position's index as reported by the OBJ file
	if ((UINT)m_VertexCache.GetSize() > hash)
	{
		CacheEntry* pEntry = m_VertexCache.GetAt(hash);
		while (pEntry != NULL)
		{
			Vertex* pCacheVertex = m_Vertices.GetData() + pEntry->index;

			// If this vertex is identical to the vertex already in the list, simply
			// point the index buffer to the existing vertex
			if (0 == memcmp(pVertex, pCacheVertex, sizeof(Vertex)))
			{
				bFoundInList = true;
				index = pEntry->index;
				break;
			}

			pEntry = pEntry->pNext;
		}
	}

	// Vertex was not found in the list. Create a new entry, both within the Vertices list
	// and also within the hashtable cache
	if (!bFoundInList)
	{
		// Add to the Vertices list
		index = m_Vertices.GetSize();
		m_Vertices.Add(*pVertex);

		// Add this to the hashtable
		CacheEntry* pNewEntry = new CacheEntry;
		if (pNewEntry == NULL)
			return (DWORD)-1;

		pNewEntry->index = index;
		pNewEntry->pNext = NULL;

		// Grow the cache if needed
		while ((UINT)m_VertexCache.GetSize() <= hash)
		{
			m_VertexCache.Add(NULL);
		}

		// Add to the end of the linked list
		CacheEntry* pCurEntry = m_VertexCache.GetAt(hash);
		if (pCurEntry == NULL)
		{
			// This is the head element
			m_VertexCache.SetAt(hash, pNewEntry);
		}
		else
		{
			// Find the tail
			while (pCurEntry->pNext != NULL)
			{
				pCurEntry = pCurEntry->pNext;
			}

			pCurEntry->pNext = pNewEntry;
		}
	}

	return index;
}


//--------------------------------------------------------------------------------------
void Mesh::DeleteCache()
{
	// Iterate through all the elements in the cache and subsequent linked lists
	for (int i = 0; i < m_VertexCache.GetSize(); i++)
	{
		CacheEntry* pEntry = m_VertexCache.GetAt(i);
		while (pEntry != NULL)
		{
			CacheEntry* pNext = pEntry->pNext;
			SAFE_DELETE(pEntry);
			pEntry = pNext;
		}
	}

	m_VertexCache.RemoveAll();
}
