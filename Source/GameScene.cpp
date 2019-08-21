#include "stdafx.h"
#include "GameScene.h"
#include "MouseDragObject.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Start()
{
	MouseDragObject* mouseDrag = Instantiate<MouseDragObject*>(new MouseDragObject);
}

void GameScene::Update(float DeltaTime)
{
}

void GameScene::LateUpdate()
{
}

void GameScene::Render()
{
}

void GameScene::End()
{
}
