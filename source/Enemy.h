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

	Position<float> position;//�G�̍��W(���S���W)
	Position<int> draw;//�G�̕`����W
	float jump;//�G�̗������x
	int anime;
	bool isGround;//���n�t���O
};
