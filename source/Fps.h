//=============================================================================
//	Fps.h
//=============================================================================
#pragma once
#include <array>

class Fps
{
public:
	Fps();
	~Fps() {}

	void update();
	void render()const;

private:
	static const int FRAME_MAX = 60;

	int count;
	int time;
	double fps;
	std::array<int,FRAME_MAX> frame;
};
