//=============================================================================
//	Map.h
//=============================================================================
#pragma once
#include "define.h"
#include <array>

enum MapObject
{
	OBJECT_NON,// = 0,
	OBJECT_BLOCK,
	OBJECT_COIN,

};

class Map
{
public:
	Map();
	~Map() {}

	void update( const Position<int> );
	void render()const;
	char getObjectFromTwoPoints( const Position<float>, const Position<float> )const;
	void setObjectFromTwoPoints( const Position<float>, const Position<float> );


	int getWidthF()const{ return WIDTH - 1; };

private:
	static const int  WIDTH = 640;//マップの横幅
	static const int  MAP_WIDTH = WIDTH / CHIP;// マップの横幅
	static const int  MAP_HEIGHT = SCREEN_Y / CHIP;// マップの縦幅

	Position<int> draw;
	char map[MAP_HEIGHT][MAP_WIDTH];
	//std::array<int,FRAME_MAX> frame;
};
