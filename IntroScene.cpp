#include "DXUT.h"
#include "IntroScene.h"

#include "TestObject.h"
#include "SkyBox.h"
#include "TileMap.h"

void IntroScene::Init()
{
	LOAD(Mesh, "Test", "H/H.obj");
	LOAD(Mesh, "SkyBox", "SkyBox_Sphere/Stage.obj");
	LOAD(Shader, "SkyBoxShader", "Shader/SkyBox.fx");

	SkyBox::Create("SkyBox01")
		.SetMesh("SkyBox")
		.SetShader("SkyBoxShader")
		.SetMain();

	Camera::Create("Camera01")
		.SetPosition(Vector3(0, 0, -180))
		.SetLookAt(Vector3::Zero)
		.SetUp(Vector3::Up)
		.SetMain();

	TileMapRenderer r;
	r.LoadFromFile("./Resource/Data/TILEMAP.txt");

	Instance(TestObject);
}

void IntroScene::Update()
{
	OBJECT.Update();
}

void IntroScene::Destroy()
{
	RESOURCE.Reset();
}
