//=============================================================================
//	Fps.h
//=============================================================================
#pragma once
#include <array>

class Fps
{
public:
	Fps(): count( 0 ), time( 0 ), fps( 0.0 ) {}
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
