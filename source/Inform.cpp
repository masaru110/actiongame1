//=============================================================================
//	Inform.cpp
//=============================================================================
#include "Inform.h"
#include "define.h"
#include "Graphics.h"

//-----------------------------------------------------------------------------
void Inform::render( const Graphics& g, const int time )const
{
	Position<int> pos( 160, 8 );

	//0�̕`��(���_�̃J�T�܂�)
	DrawGraph( pos.x, pos.y, g.getString( 0 ), true );

	drawString( "SCORE", pos.set( 32, 8 ), g );//�X�R�A
	drawNumber( score, pos.set( 152, 8 ), g );//�X�R�A
	drawString( "TIME", pos.set( 248, 8 ), g );//�X�R�A
	drawNumber( time, pos.set( 304, 8 ), g );//�^�C��

}
//-----------------------------------------------------------------------------
void Inform::drawNumber( int num, const Position<int> pos, const Graphics& g )const
{
	const int WIDTH = 8;	//�����O���t�B�b�N����

	int w = 0;
	int x = pos.x;

	//score���\�i���ŉ����ɂȂ邩����
	for ( int i = 10; num >= i; i*=10 ){ ++w; }

	for ( int i = 0; i <= w; ++i )
	{
		DrawGraph( x, pos.y, g.getString( num % 10 ), true );
		x -= WIDTH;//�`��X���W���ړ�
		num /= 10;//1�ԉ��̌����`�悵�I������̂ňꌅ������
	}
}
//-----------------------------------------------------------------------------
void Inform::drawString( std::string str, const Position<int> pos, 
	const Graphics& g )const
{
	for ( UINT i = 0; i < str.size() ; ++i )
	{	
		if(( str.at( i ) < 65 ) || ( str.at( i ) > 90 )){ continue; }
		DrawGraph( pos.x + ( 8 * i ), pos.y, 
			g.getString( str.at( i ) - 55 ), true );
	}
}
