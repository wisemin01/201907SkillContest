#pragma once
#include "Singleton.h"

class Scene;
class SceneManager
	: public Singleton<SceneManager>
{
private:
	map<std::string, Scene*> sceneMap;

	Scene* nowScene = nullptr;
	Scene* nextScene = nullptr;

public:
	SceneManager() {} 
	~SceneManager() { Reset(); }

	void AddScene(const string& key, Scene* scene);
	void ChangeScene(const string& key);

	void Update();

	void Reset();
};

#define SCENE SceneManager::GetInstance()