#include "stdafx.h"

Time::Time()
{
	lastTime = nowTime = fpsTime = timeGetTime();
}

Time::~Time()
{
}

float Time::Update()
{
	nowTime = timeGetTime();

	DeltaTime = (float)(nowTime - lastTime) / 1000.0f;

	TempFPS++;
	if (fpsTime + 1000 <= nowTime) {
		fpsTime = nowTime;
		FPS = TempFPS;
		TempFPS = 0;
	}

	lastTime = nowTime;

	return DeltaTime;
}
