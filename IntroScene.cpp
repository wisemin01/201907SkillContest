#include "DXUT.h"
#include "IntroScene.h"

#include "TestObject.h"

void IntroScene::Init()
{
	Instance(TestObject);
}

void IntroScene::Update()
{
	OBJECT.Update();
}

void IntroScene::Destroy()
{

}
