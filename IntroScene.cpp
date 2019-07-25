#include "DXUT.h"
#include "IntroScene.h"

#include "PlayerCamera.h"
#include "SkyBox.h"
#include "TileMap.h"
#include "Player.h"

void IntroScene::Init()
{
	LOAD(Mesh, "SkyBox", "SkyBox_Sphere/Stage.obj");

	LOAD(Mesh, "Car1", "car_1/01.obj");
	LOAD(Mesh, "Car2", "car_2/02.obj");
	LOAD(Mesh, "Car3", "car_3/03.obj");
	LOAD(Mesh, "Car4", "car_4/04.obj");
	LOAD(Mesh, "Car5", "car_5/05.obj");
	LOAD(Mesh, "Car6", "car_6/06.obj");
	LOAD(Mesh, "Car7", "car_7/07.obj");
	LOAD(Mesh, "Car8", "car_8/08.obj");
	LOAD(Mesh, "Car9", "car_9/09.obj");
	LOAD(Mesh, "Car10", "car_10/10.obj");
	LOAD(Mesh, "Car11", "car_11/11.obj");
	LOAD(Mesh, "Car12", "car_12/12.obj");

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
