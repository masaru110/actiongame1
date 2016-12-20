//=============================================================================
//	Inform.h
//=============================================================================
#pragma once

class Graphics;

class Inform
{
 public:
	 Inform(): score( 0 ){}
	~Inform(){}

	void render( const Graphics& )const;
	void add( int add ){ score += add; };

 private:
	void drawScore( const Graphics& )const;

	int score;
};
