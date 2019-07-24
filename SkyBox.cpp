#include "DXUT.h"
#include "SkyBox.h"

#include "Mesh.h"
#include "Texture.h"

std::map<string, SkyBox*> SkyBox::skyBoxContainer;


SkyBox::SkyBox()
{
}

SkyBox::~SkyBox()
{
}

SkyBox& SkyBox::SetMesh(const string& meshKey)
{
	mesh = FIND(Mesh, meshKey);
	return *this;
}

SkyBox& SkyBox::SetShader(const string& shaderKey)
{
	shader = FIND(Shader, shaderKey);
	return *this;
}

void SkyBox::DrawSkyBox(bool zbufferEnable)
{
	if (Camera::mainCamera == nullptr)
		return;

	auto device = DXUTGetD3D9Device();

	if (zbufferEnable == true)
	{
		device->SetRenderState(D3DRENDERSTATETYPE::D3DRS_ZENABLE, false);
	}

	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// RENDERING

	if (shader == nullptr)
		NormalRender();
	else
		ShaderRender();

	if (zbufferEnable == true)
	{
		device->SetRenderState(D3DRENDERSTATETYPE::D3DRS_ZENABLE, true);
	}

	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void SkyBox::SetMain()
{
	CAMERA.SetSkyBox(this);
}

void SkyBox::ShaderRender()
{
	auto device = DXUTGetD3D9Device();

	Matrix view = CAMERA.GetViewMatrix();
	Matrix proj = CAMERA.GetProjMatrix();
	Matrix world = Matrix::Translation(Camera::mainCamera->position);

	device->SetTransform(D3DTS_WORLD, &world);

	device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	shader->SetMatrix(D3DXHANDLE("gWorldMatrix"), &world);
	shader->SetMatrix(D3DXHANDLE("gViewMatrix"), &view);
	shader->SetMatrix(D3DXHANDLE("gProjMatrix"), &proj);

	UINT pass = 0;
	shader->Begin(&pass, 0);

	for (int j = 0; j < pass; ++j)
	{
		shader->BeginPass(j);
		for (int i = 0; i < mesh->GetNumMaterials(); ++i)
		{
			if (mesh->GetMaterial(i)->lpDiffuse)
				shader->SetTexture(D3DXHANDLE("gDiffuseMap"), mesh->GetMaterial(i)->lpDiffuse->texture);

			shader->CommitChanges();

			mesh->GetMesh()->DrawSubset(i);

			device->SetTexture(0, nullptr);
		}
		shader->EndPass();
	}

	shader->End();
}

void SkyBox::NormalRender()
{
	auto device = DXUTGetD3D9Device();

	device->SetTransform(D3DTS_WORLD, &Matrix::Translation(Camera::mainCamera->position));

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
}

SkyBox& SkyBox::Create(const string& key)
{
	SkyBox* skyBox = new SkyBox();

	skyBoxContainer.insert(make_pair(key, skyBox));

	return *skyBox;
}

SkyBox& SkyBox::Find(const string& key)
{
	if (auto find = skyBoxContainer.find(key); find != skyBoxContainer.end())
		return *find->second;

	throw exception("Find Failed");
}

void SkyBox::Remove(const string& key)
{
	auto find = skyBoxContainer.find(key);

	if (find != skyBoxContainer.end())
	{
		skyBoxContainer.erase(find);
	}
}

void SkyBox::RemoveAll()
{
	for each (auto iter in skyBoxContainer)
	{
		SAFE_DELETE(iter.second);
	}

	skyBoxContainer.clear();
}
