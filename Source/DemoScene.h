#pragma once
class DemoScene : public IScene
{
public:
	DemoScene();
	~DemoScene();

	virtual void Start();
	virtual void Update(float fDeltaTime);
	virtual void LateUpdate();
	virtual void Render();
	virtual void End();
};

