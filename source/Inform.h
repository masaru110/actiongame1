//=============================================================================
//	Inform.h
//=============================================================================
#pragma once
#include "Define.h"
#include <string>

class Graphics;

class Inform
{
 public:
	 Inform(): score( 0 ){}
	~Inform(){}

	void render( const Graphics&, const int )const;
	void addScore( int add ){ score += add; };

 private:
	void drawNumber( int, const Position<int>, const Graphics& )const;
	void drawString( std::string, const Position<int>, const Graphics& )const;

	int score;
};
