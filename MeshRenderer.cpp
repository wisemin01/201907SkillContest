#include "DXUT.h"
#include "MeshRenderer.h"

#include "MeshLoader.h"
#include "Texture.h"

void MeshRenderer::Init()
{
	gameObject->renderer = this;

	RENDER.Add(this);
}

void MeshRenderer::Update()
{

}

void MeshRenderer::Render()
{
	if (mesh == nullptr)
		return;

	auto device = DXUTGetD3D9Device();
	auto transform = gameObject->transform;

	device->SetTransform(D3DTS_WORLD, &transform->World);

	if (renderBegin) renderBegin();

	device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	for (int i = 0; i < mesh->GetNumMaterials(); ++i)
	{
		if (mesh->GetMaterial(i)->lpDiffuse)
		{
			device->SetTexture(0, mesh->GetMaterial(i)->lpDiffuse->texture);
		}

		mesh->GetMesh()->DrawSubset(i);

		device->SetTexture(0, nullptr);
	}

	if (renderEnd)
		renderEnd();
}

void MeshRenderer::Destroy()
{
	if (gameObject->renderer == this)
		gameObject->renderer = nullptr;

	RENDER.Remove(this);
}
