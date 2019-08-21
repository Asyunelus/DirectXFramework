#include "stdafx.h"

DirectX::DirectX()
{
}

DirectX::~DirectX()
{
}

HRESULT DirectX::InitD3D(HWND hWnd, HINSTANCE hInst, float ScreenWidth, float ScreenHeight)
{
	this->hWnd = hWnd;
	this->hInst = hInst;
	this->ScreenWidth = ScreenWidth;
	this->ScreenHeight = ScreenHeight;

	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
#ifdef _DEBUG
	d3dpp.Windowed = TRUE;
#else
	d3dpp.Windowed = FALSE;
#endif
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	if (!d3dpp.Windowed) {
		d3dpp.BackBufferCount = 2;
		d3dpp.BackBufferWidth = ScreenWidth;
		d3dpp.BackBufferHeight = ScreenHeight;
		d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	} else {
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	}

	// Create the D3DDevice
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &g_pd3dDevice)))
	{
		return E_FAIL;
	}

	if (FAILED(D3DXCreateLine(g_pd3dDevice, &g_pLine))) {
		return E_FAIL;
	}

	// Turn off culling
	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// Turn off D3D lighting
	g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// Turn on the zbuffer
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_ALPHAREF, (unsigned int)0x00000001);
	g_pd3dDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);

	g_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	g_pd3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_BORDER);
	g_pd3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_BORDER);

	return S_OK;
}

void DirectX::OnTick()
{
	float DeltaTime = Time::GetInstance()->Update();
	SceneManager::GetInstance()->CheckChangeScene();
	KeyManager::GetInstance()->Update();
	Update(DeltaTime);
	LateUpdate();
	Camera::GetInstance()->CheckMove();
	Render();
}

void DirectX::Update(float DeltaTime)
{
	SceneManager::GetInstance()->Update(DeltaTime);
}

void DirectX::LateUpdate()
{
	SceneManager::GetInstance()->LateUpdate();
}

void DirectX::Render()
{
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		Camera::GetInstance()->SetupMatrices();

		SceneManager::GetInstance()->Render();

		g_pd3dDevice->EndScene();
	}

	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

void DirectX::End()
{
	if (g_pd3dDevice != NULL)
		g_pd3dDevice->Release();

	if (g_pD3D != NULL)
		g_pD3D->Release();
}

void DirectX::DrawLine(float x1, float y1, float x2, float y2, D3DCOLOR color)
{
	RECT rc = Camera::GetInstance()->rc;
	D3DXVECTOR2 zoom = Camera::GetInstance()->Zoom;
	D3DXVECTOR2 vec[2];
	vec[0] = D3DXVECTOR2((x1 - rc.left) * zoom.x, (y1 - rc.top) * zoom.y);
	vec[1] = D3DXVECTOR2((x2 - rc.left) * zoom.x, (y2 - rc.top) * zoom.y);
	g_pLine->Draw(vec, 2, color);
}