#include "stdafx.h"

Camera::Camera()
{
	Reset();
}

Camera::~Camera()
{
}

void Camera::SetupMatrices()
{
	float vibp = 0.f;
	if (vib > 0.f) {
		vibp = sinf(vib * 70.f) * powf(vib, 0.7f) * 16.f;
	}

	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &EyePt, &LookatPt, &UpVec);
	DirectX::GetInstance()->g_pd3dDevice->SetTransform(D3DTS_VIEW, &matView);

	float camX = CameraPos.x;
	float camY = CameraPos.y;

	float screenX = DirectX::GetInstance()->ScreenWidth / Zoom.x;
	float screenY = DirectX::GetInstance()->ScreenHeight / Zoom.y;

	camX += -ZoomPivot.x * screenX;
	camY += -ZoomPivot.y * screenY;

	D3DXMATRIXA16 matProj;
	rc.left = camX;
	rc.right = camX + screenX;
	rc.top = camY;
	rc.bottom = camY + screenY;

	D3DXMatrixOrthoOffCenterLH(&matProj, rc.left + vibp, rc.right + vibp, rc.bottom + vibp, rc.top + vibp, 0.1f, 100.f);

	DirectX::GetInstance()->g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}

D3DXVECTOR2 Camera::GetCameraPosition()
{
	return CameraPos;
}

D3DXVECTOR2 Camera::GetCameraScreenPosition()
{
	D3DXVECTOR2 Screen = D3DXVECTOR2(DirectX::GetInstance()->ScreenWidth, DirectX::GetInstance()->ScreenHeight);
	Screen.x *= -ZoomPivot.x;
	Screen.y *= -ZoomPivot.y;
	return CameraPos + Screen;
}

D3DXVECTOR2 Camera::GetCameraLastPosition()
{
	return LastCameraPos;
}

D3DXVECTOR2 Camera::GetCameraDirection()
{
	return CameraPos - LastCameraPos;
}

void Camera::Reset()
{
	CameraPos = TargetPosition = LastCameraPos = D3DXVECTOR2(0, 0);
}

void Camera::MoveCamera(D3DXVECTOR2 Pos)
{
	TargetPosition = Pos;
}

void Camera::CheckMove()
{
	LastCameraPos = CameraPos;
	CameraPos = TargetPosition;
}
