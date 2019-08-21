#pragma once
class DirectX : public SingleInstance<DirectX>
{
public:
	HWND					hWnd = NULL;
	HINSTANCE				hInst = NULL;
	float ScreenWidth = 0, ScreenHeight = 0;
	LPDIRECT3D9             g_pD3D = NULL;
	LPDIRECT3DDEVICE9       g_pd3dDevice = NULL;
	LPD3DXLINE				g_pLine = NULL;
public:
	DirectX();
	virtual ~DirectX();

	HRESULT InitD3D(HWND hWnd, HINSTANCE hInst, float ScreenWidth, float ScreenHeight);
	void OnTick();
	void Update(float DeltaTime);
	void LateUpdate();
	void Render();
	void End();
	void DrawLine(float x1, float y1, float x2, float y2, D3DCOLOR color);
};

