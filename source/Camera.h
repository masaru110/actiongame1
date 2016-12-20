//=============================================================================
//	Camera.h
//=============================================================================
#pragma once
#include "Define.h"

class Camera
{
 public:
	Camera();
	~Camera();

	Position<float> move( const Position<float>, const int );

	Position<int> getPos()const{ return position; }

 private:
	 Position<int> windowSize;
	 Position<int> position;
};
