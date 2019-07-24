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

	LOAD(Mesh, "Building1", "building_1/1.obj");
	LOAD(Mesh, "Building2", "building_2/2.obj");
	LOAD(Mesh, "Building3", "building_3/3.obj");
	LOAD(Mesh, "Building4", "building_4/4.obj");
	LOAD(Mesh, "Building5", "building_5/5.obj");

	LOAD(Mesh, "Road1", "road_1/1.obj");
	LOAD(Mesh, "Road2", "road_2/2.obj");
	LOAD(Mesh, "Road3", "road_3/3.obj");
	LOAD(Mesh, "Road4", "road_4/4.obj");
	LOAD(Mesh, "Road5", "road_5/5.obj");

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
