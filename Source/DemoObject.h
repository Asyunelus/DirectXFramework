#pragma once
class DemoObject : public GameObject
{
public:
	DemoObject();
	~DemoObject();

	virtual void Start();
	virtual void Update(float DeltaTime);
	virtual void LateUpdate();
	virtual void Render();
	virtual void End();
};

