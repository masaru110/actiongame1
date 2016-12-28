//=============================================================================
//	Content.h
//=============================================================================
#pragma once
#include "Graphics.h"
#include "Map.h"
#include "Camera.h"
#include "Inform.h"
#include "Player.h"
#include "Enemy.h"

class Input;
struct Sequence;

//-----------------------------------------------------------------------------
class Content
{
public:
	Content();
	~Content(){}

	void update( const Input& );
	void render()const;

	bool isCounter( const unsigned int );

	bool isProceed(){ return proceed; }
	void changeSequence( Sequence* const seq ){ sequence = seq; }

	Timer timer;
	Timer count;
	Graphics graphics;
	Map map;
	Camera camera;
	Inform inform;
	Player player;
	Enemy enemy;

private:
	static const int MAX_TIME = 255;
	Sequence* sequence;
	bool proceed;
};
