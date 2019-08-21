#include "stdafx.h"
#include "DemoScene.h"
#include "DemoObject.h"
#include "MouseDragObject.h"

DemoScene::DemoScene()
{
}


DemoScene::~DemoScene()
{
}

void DemoScene::Start()
{
	DemoObject* object = Instantiate<DemoObject*>(new DemoObject);
	MouseDragObject* mouseDrag = Instantiate<MouseDragObject*>(new MouseDragObject);
}

void DemoScene::Update(float fDeltaTime)
{
	
}

void DemoScene::LateUpdate()
{
}

void DemoScene::Render()
{
}

void DemoScene::End()
{
}