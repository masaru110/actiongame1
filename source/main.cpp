//=============================================================================
/*
	TestGame ver20160914  by peo
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
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	//ƒƒ‚ƒŠƒŠ[ƒNŒŸo
	#if defined _DEBUG
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	#endif

	Game* game = new Game();
	game->execute();
	delete game;
	game = nullptr;

	return 0;
}
