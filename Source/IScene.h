#pragma once

class IScene {
public:
	IScene();
	virtual ~IScene();

	virtual void PStart();
	virtual void PUpdate(float DeltaTime);
	virtual void PLateUpdate();
	virtual void PRender();
	virtual void PEnd();

	virtual void Start() = 0;
	virtual void Update(float DeltaTime) = 0;
	virtual void LateUpdate() = 0;
	virtual void Render() = 0;
	virtual void End() = 0;
};