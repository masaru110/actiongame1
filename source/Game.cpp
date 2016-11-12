//=============================================================================
//	Game.cpp
//=============================================================================
#include "Game.h"
#include "Define.h"

//-----------------------------------------------------------------------------
Game::Game(): isProceed( true )
{
	//DX���C�u�����̏����ݒ�
	SetOutApplicationLogValidFlag( false );
	ChangeWindowMode( true );
	SetMainWindowText( WINDOW_TITLE );

	//DX���C�u�����̏������Ɨ���ʐݒ�
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
	//�Q�[�����[�v
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

	//ESC�L�[�������ꂽ��I��
	if( input.isPressedKey( KEY_INPUT_ESCAPE )){ isProceed = false; }
}
//-----------------------------------------------------------------------------
void Game::render()const
{
	content.render();
	fps.render();
}
