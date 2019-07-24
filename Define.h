#pragma once

using object = LPVOID;

class Texture;

// Vertex format
struct Vertex
{
	Vector3 position;
	Vector3 normal;
	Vector2 texcoord;
};

// Material properties per mesh subset
struct Material
{
	string strName = "";

	Texture* lpDiffuse = nullptr;
	Texture* lpSpecular = nullptr;
};

using MaterialList = std::vector<Material*>;
using Shader = ID3DXEffect;
using DXBuffer = ID3DXBuffer;

// * IF THE OBJECT IS NULL, THE FUNCTION IS NOW EXECUTED.
#define SAFE_EXECUTE(p) if(p != nullptr) p

// * DEBUG LOG
#define DEBUG_LOG(text) cout << text << endl;

// * RETURN POINTER
#define AC(c) AddComponent<c>()
#define GC(c) GetComponent<c>()

// * RETURN REFERENCE
#define ACR(c) (*AddComponent<c>())
#define GCR(c) (*GetComponent<c>())

// * FIND RESOURCE AS RESOURCE MANAGER
#define FIND(_Ty, RsName) RESOURCE.Find<_Ty>(RsName)

// * LOAD RESOURCE AS RESOURCE MANAGER
#define LOAD(_Ty, RsName, RsPath) RESOURCE.Load<_Ty>(RsName, "./Resource/" ## RsPath)


// *  LAMBDA FUNC
#define LAMBDA [&]()