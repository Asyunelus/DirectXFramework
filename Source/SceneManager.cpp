#include "stdafx.h"

SceneManager::SceneManager()
{
	NextScene = nullptr;
	NowScene = nullptr;
}


SceneManager::~SceneManager()
{
}

void SceneManager::CheckChangeScene()
{
	if (NextScene) {
		if (NowScene) NowScene->PEnd();
		ObjectManager::GetInstance()->ClearAll();
		NowScene = NextScene;
		NowScene->PStart();
		NextScene = nullptr;
	}
}

void SceneManager::ChangeScene(string Name)
{
	if (Scenes.find(Name) != Scenes.end()) {
		NextScene = Scenes[Name];
	}
}

void SceneManager::AddScene(string Name, IScene* Scene)
{
	Scenes.insert(pair<string, IScene*>(Name, Scene));
}

IScene* SceneManager::GetNowScene()
{
	return NowScene;
}

IScene* SceneManager::GetScene(string Name)
{
	return Scenes[Name];
}

void SceneManager::Update(float DeltaTime)
{
	if (NowScene)
		NowScene->PUpdate(DeltaTime);
}

void SceneManager::LateUpdate()
{
	if (NowScene)
		NowScene->PLateUpdate();
}

void SceneManager::Render()
{
	if (NowScene)
		NowScene->PRender();
}