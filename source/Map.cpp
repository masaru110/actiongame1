//=============================================================================
//	Map.cpp
//=============================================================================
#include "Map.h"
#include "Define.h"

//-----------------------------------------------------------------------------
Map::Map()
{
	// マップデータ
	char data[MAP_HEIGHT][MAP_WIDTH] =
	{
		0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
		0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
		0,0,0,1,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1, 1,0,0,1,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
		0,0,0,1,0, 0,0,2,0,2, 0,0,0,0,0, 0,0,1,0,1, 1,0,0,1,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,1,0,0,
		0,0,0,1,1, 1,1,0,0,0, 0,0,0,0,0, 0,0,1,0,1, 1,0,0,1,1, 1,1,0,0,0, 0,0,0,0,0, 0,0,1,0,0,

		0,0,0,0,0, 0,0,0,1,1, 0,0,0,0,0, 0,0,1,0,1, 1,0,0,0,0, 0,0,0,1,1, 0,0,0,0,0, 0,0,0,0,0,
		0,0,0,0,0, 0,0,0,0,0, 0,0,1,1,0, 0,0,1,0,1, 1,0,0,0,0, 0,0,0,0,0, 0,0,1,1,0, 0,0,0,0,0,
		0,0,0,0,2, 2,2,2,0,0, 0,0,0,0,0, 0,0,1,0,1, 1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
		1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1, 1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
		1,0,0,0,0, 0,0,1,1,0, 0,0,0,0,0, 1,0,1,0,0, 0,0,0,0,0, 0,0,1,1,0, 0,0,0,0,0, 1,0,0,0,0,

		0,0,0,0,0, 1,1,1,1,1, 0,0,0,0,1, 1,0,1,0,1, 0,0,0,0,0, 1,1,1,1,1, 0,0,0,0,1, 1,0,0,3,1,
		0,0,0,0,0, 1,1,1,1,1, 0,0,0,1,1, 1,0,1,0,0, 0,0,0,0,0, 1,1,1,1,1, 0,0,0,1,1, 1,0,0,3,0,
		0,0,0,0,0, 0,0,0,0,0, 0,0,0,1,1, 1,1,1,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,1,1, 1,1,0,3,0,
		0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,3,1,
		1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,0,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,
	};

	for ( int i = 0; i < MAP_HEIGHT; ++i )
	{
		for ( int j = 0; j < MAP_WIDTH; ++j )
		{
			map[ i ][ j ] = data[ i ][ j ];
		}
	}
}
//-----------------------------------------------------------------------------
void Map::update( Position<int> pos )
{
	draw.x = pos.x;
}
//-----------------------------------------------------------------------------
void Map::render()const
{
	int width = draw.x / CHIP;
	int drawpoint = width;
	int margin = ( draw.x % CHIP );

	int x,y;

	for ( int i = 0; i < MAP_HEIGHT; ++i )
	{
		for ( int j = 0; j < 21; ++j )
		{
			//範囲外は描画しない
			if (( j + drawpoint < 0 )||( j + drawpoint >= MAP_WIDTH )){ continue; }
			if ( map[ i  ][ j + drawpoint ] == 1 )
			{
				x = (( j - width + drawpoint ) * CHIP ) - margin;
				y = i * CHIP;
				DrawBox( x, y, x + CHIP, y + CHIP, 
					GetColor( 255, 255, 255 ), true );
			}
			else if ( map[ i  ][ j + drawpoint ] == 2 )
			{
				x = (( j - width + drawpoint ) * CHIP ) - margin + CHIP / 2;
				y = i * CHIP + CHIP / 2;
				DrawCircle( x, y, 7, GetColor( 255, 255, 0 ), true );
			}
			else if ( map[ i  ][ j + drawpoint ] == 3 )
			{
				x = (( j - width + drawpoint ) * CHIP ) - margin;
				y = i * CHIP;
				DrawBox( x, y, x + CHIP, y + CHIP, 
					GetColor( 255, 0, 0 ), true );
			}
		}
	}
}
//-----------------------------------------------------------------------------
char Map::getObjectFromTwoPoints( const Position<float> pos1,
	const Position<float> pos2 )const
{
	std::array<int,2>  x;
	std::array<int,2>  y;

    //整数値へ変換
    x.at( 0 ) = (int)pos1.x / CHIP;
	y.at( 0 ) = (int)pos1.y / CHIP;
    x.at( 1 ) = (int)pos2.x / CHIP;
    y.at( 1 ) = (int)pos2.y / CHIP;

	for (int i = 0; i < 2; ++i )
	{
		//マップ範囲外
		if ( x.at( i ) >= MAP_WIDTH || y.at( i ) >= MAP_HEIGHT || 
			x.at( i ) < 0 || y.at( i ) < 0 )
		{ continue; }
		//０以外なら指定の座標に該当するマップの情報を返す
		if ( map[ y.at( i ) ][ x.at( i ) ] != 0  )
		{ 
			return map[ y.at( i ) ][ x.at( i ) ]; 
		}
	}

	return 0;//何もないなら０
}
//-----------------------------------------------------------------------------
void Map::setObjectFromTwoPoints( const Position<float> pos1,
	const Position<float> pos2 )
{
	std::array<int,2>  x;
	std::array<int,2>  y;

    //整数値へ変換
    x.at( 0 ) = (int)pos1.x / CHIP;
	y.at( 0 ) = (int)pos1.y / CHIP;
    x.at( 1 ) = (int)pos2.x / CHIP;
    y.at( 1 ) = (int)pos2.y / CHIP;

	for (int i = 0; i < 2; ++i )
	{
		//マップ範囲外
		if ( x.at( i ) >= MAP_WIDTH || y.at( i ) >= MAP_HEIGHT || 
			x.at( i ) < 0 || y.at( i ) < 0 )
		{ continue; }
		//０以外なら指定の座標を０に
		if ( map[ y.at( i ) ][ x.at( i ) ] != 0  )
		{ 
			map[ y.at( i ) ][ x.at( i ) ] = 0; 
			break;
		}
	}
}