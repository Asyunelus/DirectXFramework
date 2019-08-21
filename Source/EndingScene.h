#pragma once
class EndingScene : public IScene
{
public:
	EndingScene();
	virtual ~EndingScene();

	virtual void Start();
	virtual void Update(float DeltaTime);
	virtual void LateUpdate();
	virtual void Render();
	virtual void End();
};