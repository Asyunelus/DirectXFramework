#pragma once
class GameScene : public IScene
{
public:
	GameScene();
	virtual ~GameScene();

	virtual void Start();
	virtual void Update(float DeltaTime);
	virtual void LateUpdate();
	virtual void Render();
	virtual void End();
};