//=============================================================================
//	Input.cpp
//=============================================================================
#include "Input.h"
#include "Define.h"

//-----------------------------------------------------------------------------
void Input::update()
{
	previous = current;

	int input = GetJoypadInputState( DX_INPUT_KEY_PAD1 );

	( input & PAD_INPUT_UP ) ? current.up = true : current.up = false;
	( input & PAD_INPUT_DOWN ) ? current.down = true : current.down = false;
	( input & PAD_INPUT_LEFT ) ? current.left = true : current.left = false;
	( input & PAD_INPUT_RIGHT ) ? current.right = true : current.right = false;
	( input & PAD_INPUT_A ) ? current.padA = true : current.padA = false;
	( input & PAD_INPUT_B ) ? current.padB = true : current.padB = false;

	std::array<char,KEY_ALL> tmp;
	GetHitKeyStateAll( tmp.data() );

	for( int i = 0; i < KEY_ALL; ++i )
	{
		( tmp[ i ] != 0 ) ? current.key[ i ] = true : current.key[ i ] = false;
	}
}
//-----------------------------------------------------------------------------
bool Input::isDownedPad( const int code )const
{
	switch( code )
	{
		case PAD_INPUT_DOWN: return current.down;
		case PAD_INPUT_LEFT: return current.left;
		case PAD_INPUT_RIGHT: return current.right;
		case PAD_INPUT_UP: return current.up;
		case PAD_INPUT_A: return current.padA;
		case PAD_INPUT_B: return current.padB;
	}

	return false;
}
//-----------------------------------------------------------------------------
bool Input::isPressedPad( const int code )const
{
	switch( code )
	{
		case PAD_INPUT_DOWN:
			return isPressed( current.down, previous.down );
		case PAD_INPUT_LEFT:
			return isPressed( current.left, previous.left );
		case PAD_INPUT_RIGHT:
			return isPressed( current.right, previous.right );
		case PAD_INPUT_UP:
			return isPressed( current.up, previous.up );
		case PAD_INPUT_A:
			return isPressed( current.padA, previous.padA );
		case PAD_INPUT_B:
			return isPressed( current.padB, previous.padB );
	}

	return false;
}
//-----------------------------------------------------------------------------
bool Input::isReleasedPad( const int code )const
{
	switch( code )
	{
		case PAD_INPUT_DOWN:
			return isReleased( current.down, previous.down );
		case PAD_INPUT_LEFT:
			return isReleased( current.left, previous.left );
		case PAD_INPUT_RIGHT:
			return isReleased( current.right, previous.right );
		case PAD_INPUT_UP:
			return isReleased( current.up, previous.up );
		case PAD_INPUT_A:
			return isReleased( current.padA, previous.padA );
		case PAD_INPUT_B:
			return isReleased( current.padB, previous.padB );
	}

	return false;
}
//-----------------------------------------------------------------------------
bool Input::isDownedKey( const int code )const
{
	return current.key[ code ];
}
//-----------------------------------------------------------------------------
bool Input::isPressedKey( const int code )const
{
	return isPressed( current.key[ code ], previous.key[ code ] );
}
//-----------------------------------------------------------------------------
bool Input::isReleasedKey( const int code )const
{
	return isReleased( current.key[ code ], previous.key[ code ] );
}
