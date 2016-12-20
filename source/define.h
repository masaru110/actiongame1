//=============================================================================
//	define.h
//=============================================================================
#pragma once
#include <DxLib.h>

//-----------------------------------------------------------------------------
//const
//-----------------------------------------------------------------------------
const char WINDOW_TITLE[]( "demo" );//タイトルバーに表示されるタイトル

const int WINDOW_X( 640 );//ウインドウサイズ
const int WINDOW_Y( 480 );

const int SCREEN_X( 320 );	//ゲーム画面サイズ
const int SCREEN_Y( 240 );

const int CHIP( 16 );// 一つのチップのサイズ
//-----------------------------------------------------------------------------
//structure
//-----------------------------------------------------------------------------
template <typename Type>
struct Position
{
	Position(): x(), y(){}
	Position( Type dx, Type dy ){ x = dx, y = dy; }
	~Position(){}

	void set( Type dx, Type dy ){ x = dx, y = dy; }
	Type x;
	Type y;
};

struct Timer
{
	Timer():time( 0 ){}
	~Timer(){}
	void update(){ ++time; }
	void clear(){ time = 0; }
	unsigned int time;
};
//-----------------------------------------------------------------------------
//inline
//-----------------------------------------------------------------------------
template <class T>
inline void safeDelete( T*& p )
{
	delete p;
	p = nullptr;
}
