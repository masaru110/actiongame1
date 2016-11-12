//=============================================================================
//	Fps.cpp
//=============================================================================
#include "Fps.h"
#include "Define.h"

//-----------------------------------------------------------------------------
void Fps::update()
{ 
    frame[count] = GetNowCount() - time;
    time = GetNowCount();

    if( count == 0 )
	{
        int average = 0;
		for( int i = 0; i < FRAME_MAX; i++ ){ average += frame[ i ]; }
		average /= FRAME_MAX;
		fps = 1000.0 / ( double )average;
    }

	count = ( count + 1 ) % FRAME_MAX;
}
//-----------------------------------------------------------------------------
void Fps::render()const
{
	DrawFormatString( 2, 2, 0xffff00, "FPS %.1f", fps );
}