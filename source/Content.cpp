//=============================================================================
//	Content.cpp
//=============================================================================
#include "Content.h"
#include "Define.h"
#include "Input.h"

//-----------------------------------------------------------------------------
void RedState::update( Content* content )
{
	content;
	color = GetColor( 255, 0, 0 );
}
//-----------------------------------------------------------------------------
void BlueState::update( Content* content )
{
	content;
	color = GetColor( 0, 0, 255 );
}
//-----------------------------------------------------------------------------
void GreenState::update( Content* content )
{
	content;
	color = GetColor( 0, 255, 0 );
}
//-----------------------------------------------------------------------------
void YellowState::update( Content* content )
{
	content;
	color = GetColor( 255, 255, 0 );
}
//-----------------------------------------------------------------------------
Content::Content(): proceed( true ), state( nullptr )
{
	state = &redState;
}
//-----------------------------------------------------------------------------
void Content::update( const Input& input )
{
	if( input.isPressedPad( PAD_INPUT_UP )){ state = &greenState; }
	if( input.isPressedPad( PAD_INPUT_DOWN )){ state = &yellowState; }
	if( input.isPressedPad( PAD_INPUT_LEFT )){ state = &redState; }
	if( input.isPressedPad( PAD_INPUT_RIGHT )){ state = &blueState; }

	state->update( this );
}
//-----------------------------------------------------------------------------
void Content::render()const
{	
	DrawBox( 220, 140, 420, 340, state->getColor(), true );
}
