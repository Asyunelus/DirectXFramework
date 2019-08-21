#pragma once
class Camera : public SingleInstance<Camera>
{
	D3DXVECTOR3 EyePt = D3DXVECTOR3(0.0f, 0.0f, -5.0f);
	D3DXVECTOR3 LookatPt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 UpVec = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	float vib = 0.f;
	D3DXVECTOR2 CameraPos;
	D3DXVECTOR2 LastCameraPos;
	D3DXVECTOR2 TargetPosition;

public:
	RECT rc;
	D3DXVECTOR2 Zoom = D3DXVECTOR2(1.0f, 1.0f);
	D3DXVECTOR2 ZoomPivot = D3DXVECTOR2(0.5f, 0.5f);

public:
	Camera();
	virtual ~Camera();

	void SetupMatrices();

	D3DXVECTOR2 GetCameraPosition();
	D3DXVECTOR2 GetCameraScreenPosition();
	D3DXVECTOR2 GetCameraLastPosition();
	D3DXVECTOR2 GetCameraDirection();

	void Reset();

	void MoveCamera(D3DXVECTOR2 Pos);
	void CheckMove();
};

