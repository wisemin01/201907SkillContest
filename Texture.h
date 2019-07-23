#pragma once
#include "BaseResource.h"

class Texture :
	public BaseResource
{
public:
	D3DXIMAGE_INFO info;
	LPDIRECT3DTEXTURE9 texture;
public:
	Texture();
	~Texture();

	virtual void Add(const std::string& path, int count = 0) = 0;
	virtual Texture* Get(int count = -1) = 0;

	virtual unsigned int Size() = 0;

	__declspec(property(get = GetWidth)) unsigned int Width;
	__declspec(property(get = GetHeight)) unsigned int Height;

	unsigned int GetWidth() { return info.Width; }
	unsigned int GetHeight() { return info.Height; }
};
