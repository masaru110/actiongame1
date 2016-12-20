//=============================================================================
//	Inform.cpp
//=============================================================================
#include "Inform.h"
#include "define.h"
#include "Graphics.h"

//-----------------------------------------------------------------------------
void Inform::render( const Graphics& g )const
{
	drawScore( g );
}
//-----------------------------------------------------------------------------
void Inform::drawScore( const Graphics& g )const
{
	const int WIDTH = 8;	//数字グラフィック横幅
	const int POS_X = 160;	//描画位置X
	const int POS_Y = 8;	//描画位置Y

	int sc = score;
	int w = 0;
	int x = POS_X - WIDTH;

	DrawGraph( POS_X, POS_Y, g.getString( 0 ), true );//0の描画(得点のカサまし)

	//scoreが十進数で何桁になるか調査
	for ( int i = 10; score >= i; i*=10 ){ ++w; }

	for ( int i = 0;i <= w; ++i )
	{
		DrawGraph( x, POS_Y, g.getString( sc % 10 ), true );
		x -= WIDTH;//描画X座標を移動
		sc /= 10;//1番下の桁が描画し終わったので一桁下げる
	}
}
