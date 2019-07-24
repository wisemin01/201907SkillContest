#include "DXUT.h"
#include "IntroScene.h"

#include "PlayerCamera.h"
#include "SkyBox.h"
#include "TileMap.h"
#include "Player.h"

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
		.SetPosition(Vector3(0, 0, -200))
		.SetLookAt(Vector3::Zero)
		.SetUp(Vector3::Up)
		.SetMain();

	auto player = Instance(Player);
	Instance(PlayerCamera)->SetTarget(player->transform);
	Instance(TileMap)->Load("./Resource/Data/TILEMAP.txt");
}

void IntroScene::Update()
{
	OBJECT.Update();
}

void IntroScene::Destroy()
{
	OBJECT.Reset();
}
