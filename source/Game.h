//=============================================================================
//	Game.h
//=============================================================================
#pragma once
#include "Fps.h"
#include "Input.h"

class Game
{
public:
	Game();
	~Game();

	int		execute();

private:
	void	initialize();
	void	update();
	void	render()const;
	void	error( const char* );

	Fps		fps;
	Input	input;
	bool	isProceed;
};
