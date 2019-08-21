#pragma once
class MainScene : public IScene
{
public:
	MainScene();
	virtual ~MainScene();

	virtual void Start();
	virtual void Update(float DeltaTime);
	virtual void LateUpdate();
	virtual void Render();
	virtual void End();
};

