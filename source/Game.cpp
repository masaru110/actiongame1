//=============================================================================
//	Game.cpp
//=============================================================================
#include "Game.h"
#include "Define.h"

//-----------------------------------------------------------------------------
Game::Game(): isProceed( true )
{
	//DXライブラリの初期設定
	SetOutApplicationLogValidFlag( false );
	ChangeWindowMode( true );
	SetMainWindowText( WINDOW_TITLE );

	//DXライブラリの初期化と裏画面設定
	if( DxLib_Init() != -1 )
	{
		SetDrawScreen( DX_SCREEN_BACK );
	}
	else{ isProceed = false; }
}
//-----------------------------------------------------------------------------
Game::~Game()
{
	DxLib_End();
}
//-----------------------------------------------------------------------------
int Game::execute()
{
	//ゲームループ
	while( isProceed &&	ProcessMessage() == 0 )
	{
		ClearDrawScreen();
		update();
		render();
		ScreenFlip();
	}

	return 0;
}
//-----------------------------------------------------------------------------
void Game::update()
{
	fps.update();
	input.update();

	content.update( input );

	//ESCキーが押されたら終了
	if( input.isPressedKey( KEY_INPUT_ESCAPE )){ isProceed = false; }
}
//-----------------------------------------------------------------------------
void Game::render()const
{
	content.render();
	fps.render();
}
