#pragma once
class FPSCounter
{
private:
	unsigned long long Frames = 0;
	double time1 , time2;
	double fpsTime = 0;
	long double fps_;
public:
	FPSCounter();
	void nextFrame();
	long double FPS();
	bool ready() const;
	~FPSCounter() = default;
};

