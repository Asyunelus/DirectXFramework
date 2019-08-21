#include "stdafx.h"
#include "IScene.h"

IScene::IScene()
{
}

IScene::~IScene()
{
}

void IScene::PStart()
{
	ObjectManager::GetInstance()->Start();
	Start();
}

void IScene::PUpdate(float DeltaTime)
{
	ObjectManager::GetInstance()->Update(DeltaTime);
	Update(DeltaTime);
}

void IScene::PLateUpdate()
{
	ObjectManager::GetInstance()->LateUpdate();
	LateUpdate();
}

void IScene::PRender()
{
	ObjectManager::GetInstance()->Render();
	Render();
}

void IScene::PEnd()
{
	ObjectManager::GetInstance()->End();
	End();
}
