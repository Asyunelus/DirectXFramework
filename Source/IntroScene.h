#pragma once
class IntroScene : public IScene
{
public:
	IntroScene();
	virtual ~IntroScene();

	virtual void Start();
	virtual void Update(float DeltaTime);
	virtual void LateUpdate();
	virtual void Render();
	virtual void End();
};

