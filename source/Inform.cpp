//=============================================================================
//	Inform.cpp
//=============================================================================
#include "Inform.h"
#include "define.h"
#include "Graphics.h"

//-----------------------------------------------------------------------------
void Inform::render( const Graphics& g )const
{
	drawScore( g );
}
//-----------------------------------------------------------------------------
void Inform::drawScore( const Graphics& g )const
{
	const int WIDTH = 8;	//�����O���t�B�b�N����
	const int POS_X = 160;	//�`��ʒuX
	const int POS_Y = 8;	//�`��ʒuY

	int sc = score;
	int w = 0;
	int x = POS_X - WIDTH;

	DrawGraph( POS_X, POS_Y, g.getString( 0 ), true );//0�̕`��(���_�̃J�T�܂�)

	//score���\�i���ŉ����ɂȂ邩����
	for ( int i = 10; score >= i; i*=10 ){ ++w; }

	for ( int i = 0;i <= w; ++i )
	{
		DrawGraph( x, POS_Y, g.getString( sc % 10 ), true );
		x -= WIDTH;//�`��X���W���ړ�
		sc /= 10;//1�ԉ��̌����`�悵�I������̂ňꌅ������
	}
}
