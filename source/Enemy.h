//
//	Enemy.h
//=============================================================================
#pragma once
#include <array>
#include "Define.h"

class Map;
class Graphics;

class Enemy
{
public:
	Enemy();
	~Enemy() {}

	void update( const Timer&, Map& );
	void render( const Graphics& )const;

	void reset();

	Position<float> getPos()const{ return position; }

private:
	static const int SIZE =  12;
	enum Action{ STAND, WALK, JUMP, DEAD }action;

	void animetion( const Timer& );
	float replacement(const float, const int );

	Position<float> position;//敵の座標(中心座標)
	Position<int> draw;//敵の描画座標
	float jump;//敵の落下速度
	int anime;
	bool isGround;//着地フラグ
};
