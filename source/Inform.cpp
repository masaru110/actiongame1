//=============================================================================
//	Inform.cpp
//=============================================================================
#include "Inform.h"
#include "define.h"
#include "Graphics.h"

//-----------------------------------------------------------------------------
void Inform::render( const Graphics& g, const int time )const
{
	Position<int> pos( 160, 8 );

	//0の描画(得点のカサまし)
	DrawGraph( pos.x, pos.y, g.getString( 0 ), true );

	drawString( "SCORE", pos.set( 32, 8 ), g );//スコア
	drawNumber( score, pos.set( 152, 8 ), g );//スコア
	drawString( "TIME", pos.set( 248, 8 ), g );//スコア
	drawNumber( time, pos.set( 304, 8 ), g );//タイム

}
//-----------------------------------------------------------------------------
void Inform::drawNumber( int num, const Position<int> pos, const Graphics& g )const
{
	const int WIDTH = 8;	//数字グラフィック横幅

	int w = 0;
	int x = pos.x;

	//scoreが十進数で何桁になるか調査
	for ( int i = 10; num >= i; i*=10 ){ ++w; }

	for ( int i = 0; i <= w; ++i )
	{
		DrawGraph( x, pos.y, g.getString( num % 10 ), true );
		x -= WIDTH;//描画X座標を移動
		num /= 10;//1番下の桁が描画し終わったので一桁下げる
	}
}
//-----------------------------------------------------------------------------
void Inform::drawString( std::string str, const Position<int> pos, 
	const Graphics& g )const
{
	for ( UINT i = 0; i < str.size() ; ++i )
	{	
		if(( str.at( i ) < 65 ) || ( str.at( i ) > 90 )){ continue; }
		DrawGraph( pos.x + ( 8 * i ), pos.y, 
			g.getString( str.at( i ) - 55 ), true );
	}
}
