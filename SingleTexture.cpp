#include "DXUT.h"
#include "SingleTexture.h"

void SingleTexture::Add(const std::string& path, int count)
{
	D3DXGetImageInfoFromFileA(path.c_str(), &info);
	D3DXCreateTextureFromFileExA(DXUTGetD3D9Device(), path.c_str(), info.Width, info.Height, info.MipLevels,
		0, info.Format, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, &info, 0,
		&texture);
}

Texture* SingleTexture::Get(int count)
{
	return this;
}

unsigned int SingleTexture::Size()
{
	return 1;
}
