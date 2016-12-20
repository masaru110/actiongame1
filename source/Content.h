//=============================================================================
//	Content.h
//=============================================================================
#pragma once
#include "Graphics.h"
#include "Map.h"
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
	Inform inform;
	Player player;
	Enemy enemy;

private:
	Sequence* sequence;
	bool proceed;
};
