#pragma once
class ShopScene : public IScene
{
public:
	ShopScene();
	virtual ~ShopScene();

	virtual void Start();
	virtual void Update(float DeltaTime);
	virtual void LateUpdate();
	virtual void Render();
	virtual void End();
};