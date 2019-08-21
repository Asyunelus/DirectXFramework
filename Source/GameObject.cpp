#include "stdafx.h"

void GameObject::Start()
{
}

void GameObject::Update(float DeltaTime)
{
}

void GameObject::LateUpdate()
{
}

void GameObject::Render()
{
}

void GameObject::End()
{
	for (auto iter : Components)
		iter.reset();

	Components.clear();
}

shared_ptr<Component> GameObject::AddComponent(shared_ptr<Component> component)
{
	Components.push_back(component);
	return Components.back();
}

bool GameObject::HasComponents()
{
	return Components.size() > 0;
}

void GameObject::UpdateComponents(float DeltaTime)
{
	for (auto iter : Components)
		if (iter)
			if (iter->Enable)
				iter->Update(DeltaTime);
}

void GameObject::LateUpdateComponents()
{
	for (auto iter : Components)
		if (iter)
			if (iter->Enable)
				iter->LateUpdate();
}

void GameObject::RenderComponents()
{
	for (auto iter : Components)
		if (iter)
			if (iter->Enable)
				iter->Render();
}

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}
