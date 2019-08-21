#pragma once
class SceneManager : public SingleInstance<SceneManager>
{
	map<string, IScene*> Scenes;
	IScene* NextScene = nullptr;
	IScene* NowScene = nullptr;
public:
	SceneManager();
	~SceneManager();

	void CheckChangeScene();
	void ChangeScene(string Name);
	void AddScene(string Name, IScene* Scene);
	IScene* GetNowScene();
	IScene* GetScene(string Name);

	virtual void Update(float DeltaTime);
	virtual void LateUpdate();
	virtual void Render();
};