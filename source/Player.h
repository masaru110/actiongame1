//
//	Player.h
//=============================================================================
#pragma once
#include <array>
#include "Define.h"

class Input;
class Map;
//class Camera;
class Graphics;
class Inform;

class Player
{
public:
	Player();
	~Player() {}

	enum Action{ STAND, WALK, JUMP, DEAD, CLEAR };

	void update( const Input&, const Timer&, Map&, Inform& );
	void render( const Graphics& )const;

	void reset();

	Position<float> getPos()const{ return position; }
	bool isAction( Action act )const{ return ( action == act ); }

private:
	static const int SIZE =  12;

	void animetion( const Timer& );
	float replacement(const float, const int );
	void collisionWithMap( Map&, Inform&, Position<float>& );
	void adjustMovement( float&, const float, const int shift = 0 );
	void onGround( Map& );

	Position<float> position;//�v���C���[�̍��W(���S���W)
	Position<int> draw;//�v���C���[�̕`����W
	float jump;//�v���C���[�̗������x
	int anime;
	bool isTurn;//����
	bool isGround;//���n�t���O
	Action action;
};
