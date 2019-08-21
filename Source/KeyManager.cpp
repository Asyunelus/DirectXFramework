#include "stdafx.h"

KeyManager::KeyManager()
{
	for (int i = 0; i < 256; i++) {
		KeyState[i] = EKEY::None;
		LastKey[i] = false;
	}
}

KeyManager::~KeyManager()
{
}

void KeyManager::Update()
{
	for (int i = 0; i < 256; i++) {
		bool nKey = GetAsyncKeyState(i) & 0x8000;
		bool lKey = LastKey[i];

		if (nKey && lKey) KeyState[i] = EKEY::Down;
		if (not nKey && lKey) KeyState[i] = EKEY::Up;
		if (nKey && not lKey) KeyState[i] = EKEY::Press;
		if (not nKey && not lKey) KeyState[i] = EKEY::None;

		LastKey[i] = nKey;
	}

	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(DirectX::GetInstance()->hWnd, &pt);
	MousePos = D3DXVECTOR2(pt.x, pt.y) + Camera::GetInstance()->GetCameraScreenPosition();
}

int KeyManager::GetKeyState(int keyCode)
{
	return KeyState[keyCode];
}

D3DXVECTOR2 KeyManager::GetMousePosition()
{
	return MousePos;
}
