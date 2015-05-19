#include "FPSCounter.h"
#include <Windows.h>
namespace SpEx{
	FPSCounter::FPSCounter()
		: time(GetTickCount64() / 1000.0)
	{
	}

	void FPSCounter::nextFrame(){
		auto tmp = GetTickCount64() / 1000.0;
		double dt = tmp - time;
		time = tmp;
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
};
