#pragma once

class Mesh;

class SkyBox
{
private:
	Mesh* mesh = nullptr;
	Shader* shader = nullptr;

public:
	SkyBox();
	virtual ~SkyBox();

	SkyBox& SetMesh(const string& meshKey);
	SkyBox& SetShader(const string& shaderKey);

	void DrawSkyBox(bool zbufferEnable = false);

	void SetMain();

private:
	void ShaderRender();
	void NormalRender();

	// STATIC FIELD
public:

	static SkyBox& Create(const string& key);
	static SkyBox& Find(const string& key);
	static void Remove(const string& key);
	static void RemoveAll();

private:
	static std::map<string, SkyBox*> skyBoxContainer;
};

