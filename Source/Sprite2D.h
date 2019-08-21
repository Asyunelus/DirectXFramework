#pragma once
class Sprite2D : public Component
{
public:
	D3DXVECTOR2 ScalePivot;
	D3DXVECTOR2 RotatePivot;

	D3DXMATRIX matWorld;
	CUSTOMVERTEX Vertex[4];

	bool Loop = true;
	bool IsEnd = false;
	float AniTime = 0.2f;
	float CurAniTime = 0.0f;
	
	vector<shared_ptr<Texture>> Textures;

	int SzScene = 0;
	int CurScene = 0;

public:
	Sprite2D(GameObject* object);
	Sprite2D(GameObject* object, string fileWithPathFormat, int szScene);
	Sprite2D(GameObject* object, string FilePath);
	Sprite2D(GameObject* object, string fileWithPathFormat, int startSzScene, int szScene);
	virtual ~Sprite2D();

	virtual void Start();
	virtual void Update(float deltaTime);
	virtual void LateUpdate();
	virtual void Render();
	virtual void End();

	void UpdateTransform();
	void UpdateVertex();
	void SetUV(float x, float y, float width, float height);
	void SetUVByPixel(float xp, float yp, float widthp, float heightp);
	void SetImageSize(float width, float height);
	void SetARGB(int a, int r, int g, int b);

	float GetTextureWidth();
	float GetTextureHeight();
	float GetRealWidth();
	float GetRealHeight();
};

