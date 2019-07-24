#include "DXUT.h"
#include "IntroScene.h"

#include "PlayerCamera.h"
#include "SkyBox.h"
#include "TileMap.h"
#include "Player.h"

void IntroScene::Init()
{
	LOAD(Mesh, "SkyBox", "SkyBox_Sphere/Stage.obj");
	LOAD(Mesh, "Player", "Meteor/Meteor.obj");
	LOAD(Mesh, "Test", "road_5/e.obj");

	LOAD(Shader, "SkyBoxShader", "Shader/SkyBox.fx");
	LOAD(Shader, "LightShader", "Shader/Lighting.fx");

	CAMERA.LightPosition = Vector3(0, 10000, 0);

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
	COLLISION.CollisionCheck();
}

void IntroScene::Destroy()
{
	OBJECT.Reset();
}
