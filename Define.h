#pragma once

using Vector2 = D3DXVECTOR2;
using Vector3 = D3DXVECTOR3;

using Matrix = D3DXMATRIXA16;
using Quaternion = D3DXQUATERNION;
using object = LPVOID;

using ulong = unsigned long;

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

#define Vector2_Zero Vector2(0.0f, 0.0f)
#define Vector2_One Vector2(1.0f, 1.0f)
#define Vector2_Two Vector2(2.0f, 2.0f)

#define Vector3_Zero Vector3(0.0f, 0.0f, 0.0f)
#define Vector3_One Vector3(1.0f, 1.0f, 1.0f)
#define Vector3_Two Vector3(2.0f, 2.0f, 2.0f)

#define SAFE_EXECUTE(p) if(p != nullptr) p