//=============================================================================
//	Game.h
//=============================================================================
#pragma once
#include "Fps.h"
#include "Input.h"
#include "Content.h"

class Game
{
public:
	Game();
	~Game();

	int execute();

private:
	void update();
	void render()const;

	Fps fps;
	Input input;
	Content content;
	bool isProceed;
};
