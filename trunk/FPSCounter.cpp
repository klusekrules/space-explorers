#include "FPSCounter.h"
#include <Windows.h>

FPSCounter::FPSCounter()
: time1(GetTickCount64() / 1000)
{
}

void FPSCounter::nextFrame(){
	time2 = GetTickCount64() / 1000;
	double dt = time2 - time1;
	time1 = time2;
	++Frames;
	fpsTime += dt;	
}

long double FPSCounter::FPS(){
	if (fpsTime >= 1.0)
	{
		fps_ = Frames / fpsTime;
		fpsTime = 0;
		Frames = 0;
	}
	return fps_;
}

bool FPSCounter::ready() const{
	return fpsTime >= 1.0;
}

