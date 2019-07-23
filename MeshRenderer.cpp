#include "DXUT.h"
#include "MeshRenderer.h"

#include "Mesh.h"
#include "Texture.h"

void MeshRenderer::Init()
{
	__super::Init();
}

void MeshRenderer::Render()
{
	if (mesh == nullptr)
		return;

	if (shader == nullptr)
	{
		NormalRender();
	}
	else
	{
		ShaderRender();
	}
}

void MeshRenderer::Destroy()
{
	__super::Destroy();
}

MeshRenderer& MeshRenderer::SetMesh(Mesh* mesh)
{
	this->mesh = mesh;
	return *this;
}

MeshRenderer& MeshRenderer::SetShader(Shader* shader)
{
	this->shader = shader;
	return *this;
}

void MeshRenderer::NormalRender()
{
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

	if (renderEnd) renderEnd();
}

void MeshRenderer::ShaderRender()
{
	auto device = DXUTGetD3D9Device();
	auto transform = gameObject->transform;

	Matrix world = transform->World;
	Matrix view = CAMERA.GetViewMatrix();
	Matrix proj = CAMERA.GetProjMatrix();

	device->SetTransform(D3DTS_WORLD, &world);

	device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	if (renderBegin) renderBegin();

	shader->SetMatrix(D3DXHANDLE("gWorldMatrix"), &world);
	shader->SetMatrix(D3DXHANDLE("gViewMatrix"), &view);
	shader->SetMatrix(D3DXHANDLE("gProjMatrix"), &proj);
	
	shader->SetVector(D3DXHANDLE("gCameraPos"), &Vector4(CAMERA.GetMainCamPosition(), 1.0f));
	shader->SetVector(D3DXHANDLE("gLightPos"), &Vector4(CAMERA.GetLightPosition(), 1.f));
	shader->SetVector(D3DXHANDLE("gAmbent"), &Vector4(0.5f, 0.5f, 0.5f, 1.f));

	UINT pass = 0;
	shader->Begin(&pass, 0);

	for (int j = 0; j < pass; ++j)
	{
		shader->BeginPass(j);
		for (int i = 0; i < mesh->GetNumMaterials(); ++i)
		{
			if (mesh->GetMaterial(i)->lpDiffuse)
				shader->SetTexture(D3DXHANDLE("gDiffuseMap"), mesh->GetMaterial(i)->lpDiffuse->texture);
			if (mesh->GetMaterial(i)->lpSpecular)
				shader->SetTexture(D3DXHANDLE("gSpecualrMap"), mesh->GetMaterial(i)->lpSpecular->texture);
			else
			{
				if (mesh->GetMaterial(i)->lpDiffuse)
					shader->SetTexture(D3DXHANDLE("gDiffuseMap"), mesh->GetMaterial(i)->lpDiffuse->texture);
			}

			shader->CommitChanges();

			mesh->GetMesh()->DrawSubset(i);

			device->SetTexture(0, nullptr);
		}
		shader->EndPass();
	}

	shader->End();

	if (renderEnd) renderEnd();
}

void MeshRenderer::CustomRender(Mesh* mesh, Shader* shader, Matrix world)
{
	if (renderBegin) renderBegin();

	auto device = DXUTGetD3D9Device();

	if (shader == nullptr)
	{
		device->SetTransform(D3DTS_WORLD, &world);

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

		if (renderEnd) renderEnd();
	}
	else
	{
		Matrix view = CAMERA.GetViewMatrix();
		Matrix proj = CAMERA.GetProjMatrix();

		device->SetTransform(D3DTS_WORLD, &world);

		device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

		if (renderBegin) renderBegin();

		shader->SetMatrix(D3DXHANDLE("gWorldMatrix"), &world);
		shader->SetMatrix(D3DXHANDLE("gViewMatrix"), &view);
		shader->SetMatrix(D3DXHANDLE("gProjMatrix"), &proj);

		shader->SetVector(D3DXHANDLE("gCameraPos"), &Vector4(CAMERA.GetMainCamPosition(), 1.0f));
		shader->SetVector(D3DXHANDLE("gLightPos"), &Vector4(CAMERA.GetLightPosition(), 1.f));
		shader->SetVector(D3DXHANDLE("gAmbent"), &Vector4(0.5f, 0.5f, 0.5f, 1.f));

		UINT pass = 0;
		shader->Begin(&pass, 0);

		for (int j = 0; j < pass; ++j)
		{
			shader->BeginPass(j);
			for (int i = 0; i < mesh->GetNumMaterials(); ++i)
			{
				if (mesh->GetMaterial(i)->lpDiffuse)
					shader->SetTexture(D3DXHANDLE("gDiffuseMap"), mesh->GetMaterial(i)->lpDiffuse->texture);
				if (mesh->GetMaterial(i)->lpSpecular)
					shader->SetTexture(D3DXHANDLE("gSpecualrMap"), mesh->GetMaterial(i)->lpSpecular->texture);
				else
				{
					if (mesh->GetMaterial(i)->lpDiffuse)
						shader->SetTexture(D3DXHANDLE("gDiffuseMap"), mesh->GetMaterial(i)->lpDiffuse->texture);
				}

				shader->CommitChanges();

				mesh->GetMesh()->DrawSubset(i);

				device->SetTexture(0, nullptr);
			}
			shader->EndPass();
		}

		shader->End();
	}

	if (renderEnd) renderEnd();
}
