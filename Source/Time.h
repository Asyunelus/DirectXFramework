#pragma once
class Time : public SingleInstance<Time>
{
public:
	float DeltaTime = 0.0f;
	int FPS = 0;
	DWORD nowTime = 0;
protected:
	DWORD lastTime = 0;
	DWORD fpsTime = 0;
	int TempFPS = 0;

public:
	Time();
	virtual ~Time();

	float Update();
};

