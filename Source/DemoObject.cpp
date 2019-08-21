#include "stdafx.h"
#include "DemoObject.h"


DemoObject::DemoObject()
{
	Layer = 10;
	shared_ptr<Sprite2D> sprite = shared_ptr<Sprite2D>(new Sprite2D(this, "./Asset/test/"));
	sprite->RotatePivot = { sprite->GetRealWidth() / 2.f, sprite->GetRealHeight() / 2.f };
	sprite->ScalePivot = sprite->RotatePivot;
	AddComponent(sprite);
}


DemoObject::~DemoObject()
{
}

void DemoObject::Start()
{
	GameObject::Start();
}

void DemoObject::Update(float DeltaTime)
{
	GameObject::Update(DeltaTime);
}

void DemoObject::LateUpdate()
{
	GameObject::LateUpdate();
}

void DemoObject::Render()
{
	GameObject::Render();
}

void DemoObject::End()
{
	GameObject::End();
}
