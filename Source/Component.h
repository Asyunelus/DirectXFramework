#pragma once

class GameObject;

class Component
{
public:
	bool Enable = true;
	GameObject* gameObject;
public:
	Component(GameObject* parent);
	virtual ~Component();

	virtual void Start() = 0;
	virtual void Update(float DeltaTime) = 0;
	virtual void LateUpdate() = 0;
	virtual void Render() = 0;
	virtual void End() = 0;
};

