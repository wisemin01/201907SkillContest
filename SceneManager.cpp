#include "DXUT.h"
#include "SceneManager.h"

#include "Scene.h"

void SceneManager::AddScene(const string& key, Scene* scene)
{
	auto find = sceneMap.find(key);

	if (find == sceneMap.end())
	{
		sceneMap.insert(make_pair(key, scene));
	}
}

void SceneManager::ChangeScene(const string& key)
{
	auto find = sceneMap.find(key);

	if (find != sceneMap.end())
	{
		nextScene = find->second;
	}
}

void SceneManager::Update()
{
	if (nextScene != nullptr)
	{
		if (nowScene != nullptr)
		{
			nowScene->Destroy();
		}

		nowScene = nextScene;

		nextScene = nullptr;
		nowScene->Init();
	}

	if (nowScene != nullptr)
	{
		nowScene->Update();
	}
}

void SceneManager::Render()
{
	if (nowScene != nullptr)
	{
		nowScene->Render();
	}
}

void SceneManager::Reset()
{
	if (nowScene != nullptr)
	{
		nowScene->Destroy();
	}

	for each (auto iter in sceneMap)
	{
		SAFE_DELETE(iter.second);
	}

	sceneMap.clear();
}
