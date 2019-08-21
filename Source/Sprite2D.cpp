#include "stdafx.h"

Sprite2D::Sprite2D(GameObject * object) : Component(object)
{
	ScalePivot = D3DXVECTOR2(0.5f, 0.5f);
	RotatePivot = D3DXVECTOR2(0.5f, 0.5f);
	IsEnd = false;
}

Sprite2D::Sprite2D(GameObject * object, string fileWithPathFormat, int szScene) : Sprite2D(object)
{
	SzScene = szScene;
	Textures.resize(szScene);
	for (int i = 0; i < szScene; ++i)
	{
		char buffer[MAX_PATH];
		sprintf_s(buffer, fileWithPathFormat.c_str(), i);
		Textures[i] = TextureManager::GetInstance()->QueryTexture(buffer);
	}
	UpdateVertex();
}

Sprite2D::Sprite2D(GameObject* object, string FilePath) : Sprite2D(object)
{
	SzScene = distance(directory_iterator(FilePath), directory_iterator{});
	Textures.resize(SzScene);
	for (int i = 0; i < SzScene; ++i) {
		static string chFormat = "%s/%04d.png";
		char buffer[MAX_PATH];
		sprintf_s(buffer, chFormat.c_str(), FilePath.c_str(), i);
		Textures[i] = TextureManager::GetInstance()->QueryTexture(buffer);
	}
	if (SzScene > 0) UpdateVertex();
}

Sprite2D::Sprite2D(GameObject * object, string fileWithPathFormat, int startSzScene, int szScene) : Sprite2D(object)
{
	SzScene = szScene;
	Textures.resize(szScene);
	for (int i = startSzScene; i < szScene + startSzScene; ++i)
	{
		char buffer[MAX_PATH];
		sprintf_s(buffer, fileWithPathFormat.c_str(), i);
		Textures[i - startSzScene] = TextureManager::GetInstance()->QueryTexture(buffer);
	}
	if (szScene > 0) UpdateVertex();
}

Sprite2D::~Sprite2D()
{
	for (auto iter : Textures) {
		iter.reset();
	}
}

void Sprite2D::Start()
{
}

void Sprite2D::Update(float deltaTime)
{
	if (IsEnd) return;
	if (deltaTime > 1.0f) return;

	CurAniTime += deltaTime;

	if (CurAniTime > AniTime)
	{
		if (CurScene == SzScene - 1 && not Loop) {
			IsEnd = true;
			return;
		}
		CurAniTime -= AniTime;
		if (++CurScene >= SzScene)
		{
			CurScene = 0;
		}
	}
}

void Sprite2D::LateUpdate()
{
}

void Sprite2D::Render()
{
	UpdateTransform();

	DirectX::GetInstance()->g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);
	DirectX::GetInstance()->g_pd3dDevice->SetTexture(0, Textures[CurScene]->pTexture);
	DirectX::GetInstance()->g_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
	DirectX::GetInstance()->g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2,
		(void*)Vertex, sizeof(CUSTOMVERTEX));
}

void Sprite2D::End()
{
	for (auto Texture : Textures) {
		Texture.reset();
	}
}

void Sprite2D::UpdateTransform()
{
	D3DXMATRIX matPos, matTrans;


	D3DXVECTOR2 szSize = { GetTextureWidth(), GetTextureHeight() };


	//스프라이트의 위치
	D3DXMatrixTranslation(&matPos, gameObject->transform.Position.x, gameObject->transform.Position.y, 0.0f);
	//스프라이트의 중점으로 인한 이동
	D3DXMatrixTranslation(&matTrans, szSize.x * -gameObject->transform.Anchor.x, szSize.y * -gameObject->transform.Anchor.y, 0.0f);

	D3DXMatrixIdentity(&matWorld);

	D3DXVECTOR2 FixScalePivot = { ScalePivot.x * szSize.x, ScalePivot.y * szSize.y };
	D3DXVECTOR2 FixRotatePivot = { RotatePivot.x * szSize.x, RotatePivot.y * szSize.y };

	//Scale값, Rotate와 Scale의 기준점, 기울임 적용
	D3DXMatrixTransformation2D(&matWorld, &FixScalePivot, 0.f, &gameObject->transform.Scale, &FixRotatePivot, D3DXToRadian(gameObject->transform.RotateAngle), NULL);

	//행렬끼리 곱셈
	matWorld = matWorld * matTrans * matPos;
}

void Sprite2D::UpdateVertex()
{
	SetImageSize(GetRealWidth(), GetRealHeight());
	SetUV(0.f, 0.f, 1.f, 1.f);
	SetARGB(255, 255, 255, 255);
}

void Sprite2D::SetUV(float x, float y, float width, float height)
{
	Vertex[0].SetUV(x, y);
	Vertex[1].SetUV(x, y + height);
	Vertex[2].SetUV(x + width, y);
	Vertex[3].SetUV(x + width, y + height);
}

void Sprite2D::SetUVByPixel(float xp, float yp, float widthp, float heightp)
{
	SetUV(xp / GetRealWidth(), yp / GetRealHeight(), widthp / GetRealWidth(), heightp / GetRealHeight());
}

void Sprite2D::SetImageSize(float width, float height)
{
	Vertex[0].SetVtx(0.f, 0.f, 0.f);
	Vertex[1].SetVtx(0.f, height, 0.f);
	Vertex[2].SetVtx(width, 0.f, 0.f);
	Vertex[3].SetVtx(width, height, 0.f);
}

void Sprite2D::SetARGB(int a, int r, int g, int b)
{
	D3DCOLOR color = D3DCOLOR_ARGB(a, r, g, b);
	for (int i = 0; i < 4; i++)
		Vertex[i].color = color;
}

float Sprite2D::GetTextureWidth()
{
	return GetRealWidth() * gameObject->transform.Scale.x;
}

float Sprite2D::GetTextureHeight()
{
	return GetRealHeight() * gameObject->transform.Scale.y;
}

float Sprite2D::GetRealWidth()
{
	return Textures[CurScene]->Info.Width;
}

float Sprite2D::GetRealHeight()
{
	return Textures[CurScene]->Info.Height;
}