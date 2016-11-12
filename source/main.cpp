//=============================================================================
/*
	TestGame ver20161112  by masaru
*/
//=============================================================================
//	main.cpp
//=============================================================================
#define _CRTDBG_MAP_ALLOC

#include <stdlib.h>
#include <crtdbg.h>

#include "Define.h"
#include "Game.h"

//-----------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int )
{
	//ƒƒ‚ƒŠƒŠ[ƒNŒŸo
	#if defined _DEBUG
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	#endif

	Game* game = new Game();

	game->execute();

	safeDelete( game );

	return 0;
}
