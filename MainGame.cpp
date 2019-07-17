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
	RESOURCE.RenderBegin();

	SCENE.Render();

	RESOURCE.RenderEnd();
}

void MainGame::Destroy()
{
}

void MainGame::OnReset()
{
	RESOURCE.OnResetDevice();
}

void MainGame::OnLost()
{
	RESOURCE.OnLostDevice();
}
