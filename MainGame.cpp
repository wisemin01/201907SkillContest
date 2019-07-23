#include "DXUT.h"
#include "MainGame.h"

#include "IntroScene.h"
#include "MenuScene.h"
#include "Stage1Scene.h"
#include "EndingScene.h"

void MainGame::Init()
{
	SCENE.AddScene("INTRO", new IntroScene());
	SCENE.AddScene("MENU", new MenuScene());
	SCENE.AddScene("STAGE1", new Stage1Scene());
	SCENE.AddScene("ENDING", new EndingScene());

	SCENE.ChangeScene("INTRO");
}

void MainGame::Update()
{
	INPUT.InputUpdate();
	SCENE.Update();
}

void MainGame::Render()
{
	RENDER.Render();
}

void MainGame::Destroy()
{
	SceneManager::Destroy();
	ObjectManager::Destroy();
	CollisionManager::Destroy();
	RenderManager::Destroy();
	ResourceManager::Destroy();
	InputManager::Destroy();
	CameraManager::Destroy();
}

void MainGame::OnReset()
{
	RESOURCE.OnResetDevice();
}

void MainGame::OnLost()
{
	RESOURCE.OnLostDevice();
}
