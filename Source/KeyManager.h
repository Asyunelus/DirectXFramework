#pragma once

enum EKEY {
	Press,
	Down,
	Up,
	None
};

class KeyManager : public SingleInstance<KeyManager>
{
	int KeyState[256];
	bool LastKey[256];
	
	D3DXVECTOR2 MousePos;
public:
	KeyManager();
	virtual ~KeyManager();

	void Update();

	int GetKeyState(int keyCode);
	D3DXVECTOR2 GetMousePosition();
};

