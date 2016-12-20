/*
	TestGame ver20161114  by masaru
*/
//=============================================================================
//	main.cpp
//=============================================================================
#define _CRTDBG_MAP_ALLOC

#include <stdlib.h>
#include <crtdbg.h>
#include <array>

#include "Define.h"
#include "Input.h"
#include "Content.h"

//-----------------------------------------------------------------------------
// Fps
//-----------------------------------------------------------------------------
class Fps
{
public:
	Fps(): count( 0 ), time( 0 ), fps( 0.0 ) {}
	~Fps() {}

	void update();
	void render()const;

private:
	static const int FRAME_MAX = 60;

	int count;
	int time;
	double fps;
	std::array<int,FRAME_MAX> frame;
};
//-----------------------------------------------------------------------------
void Fps::update()
{ 
    frame[count] = GetNowCount() - time;
    time = GetNowCount();

    if ( count == 0 )
	{
        int average = 0;
		for ( int i = 0; i < FRAME_MAX; i++ ){ average += frame[ i ]; }
		average /= FRAME_MAX;
		fps = 1000.0 / ( double )average;
    }

	count = ( count + 1 ) % FRAME_MAX;
}
//-----------------------------------------------------------------------------
void Fps::render()const
{
	DrawFormatString( 2, 2, 0xffff00, "FPS %.1f", fps );
}
//-----------------------------------------------------------------------------
//Game
//-----------------------------------------------------------------------------
class Game
{
public:
	Game();
	~Game(){}

	void update();
	void render()const;

	bool isProceed()const{ return proceed; }

private:
	Fps fps;
	Input input;
	Content content;

	bool proceed;
	int screen;
};
//-----------------------------------------------------------------------------
Game::Game(): proceed( true )
{
	screen = MakeGraph( SCREEN_X, SCREEN_Y );
}
//-----------------------------------------------------------------------------
void Game::update()
{
	fps.update();
	input.update();

	content.update( input );

	//ESCキーが押されたら終了
	if ( input.isPressedKey( KEY_INPUT_ESCAPE )){ proceed = false; }
}
//-----------------------------------------------------------------------------
void Game::render()const
{
	content.render();

	GetDrawScreenGraph( 0, 0, SCREEN_X, SCREEN_Y, screen );
	DrawExtendGraph( 0, 0, WINDOW_X, WINDOW_Y, screen, false );

	fps.render();
}
//-----------------------------------------------------------------------------
//WinMain
//-----------------------------------------------------------------------------
int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
	//メモリリーク検出
	#if defined _DEBUG
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	#endif

	//DXライブラリの初期設定
	SetOutApplicationLogValidFlag( false );
	ChangeWindowMode( true );
	SetMainWindowText( WINDOW_TITLE );
	//DXライブラリの初期化と裏画面設定
	if ( DxLib_Init() == -1 ){ return -1; }
	SetDrawScreen( DX_SCREEN_BACK );

	Game* game = new Game();

	//ゲームループ
	while( game->isProceed() &&	
		   ProcessMessage() == 0 )
	{
		ClearDrawScreen();
		game->update();
		game->render();
		ScreenFlip();
	}

	//終了処理
	safeDelete( game );
	DxLib_End();

	return 0;
}
