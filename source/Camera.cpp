//=============================================================================
//	Camera.cpp
//=============================================================================
#include "Camera.h"

//-----------------------------------------------------------------------------
Camera::Camera()
{
	windowSize.set( SCREEN_X, SCREEN_Y );
}
//-----------------------------------------------------------------------------
Camera::~Camera(){}
//-----------------------------------------------------------------------------
Position<float> Camera::move( const Position<float> pos, const int max )
{
	Position<float> mov;

	mov.x = ( float )windowSize.x / 2;
	position.x = ( int )pos.x - windowSize.x / 2;

	if ( position.x < 0 )
	{ 
		position.x = 0; 
		mov.x = pos.x;

	}
	if ( position.x > max - windowSize.x )
	{ 
		position.x = max - windowSize.x;
		mov.x = pos.x - ( max - windowSize.x );
	}

	return mov;
}
