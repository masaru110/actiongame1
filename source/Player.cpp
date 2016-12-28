//=============================================================================
//	Player.cpp
//=============================================================================
#include "Player.h"
#include "Input.h"
#include "Map.h"
#include "Graphics.h"
#include "Inform.h"

//-----------------------------------------------------------------------------
Player::Player(): action( STAND ), jump( 0.0F ), anime( 0 ), 
		isTurn( true ), isGround( false )
{
	position.set( 160.0F, 120.0F ); //�v���C���[�̍��W��������
}
//-----------------------------------------------------------------------------
void Player::update( const Input& input, const Timer& t, 
	Map& map, Inform& inform )
{ 
	const float SPEED = 1.0F;
	const float GRAVITY = 0.2F; 
	const float JUMP_POWER = 5.0F;
	const float MARGIN = 0.5F;

	Position<float> move;//�ړ���
	action = STAND;

	// ���E�̈ړ�	
	if ( input.isDownedPad( PAD_INPUT_LEFT ))
	{ 
		move.x -= SPEED;
		isTurn = true; 
		action = WALK;
	}
	if ( input.isDownedPad( PAD_INPUT_RIGHT ))
	{ 
		move.x += SPEED;
		isTurn = false; 
		action = WALK;
	}

	// �n�ʂɑ��������Ă���ꍇ�̂݃W�����v
	if ( isGround && ( input.isPressedPad( PAD_INPUT_UP )))
	{
		jump = -JUMP_POWER;
		isGround = false;
		action = JUMP;
	}
	
	jump += GRAVITY;//��������	
	move.y = jump;//�������x���ړ��ʂɉ�����

	//�}�b�v�Ƃ̏Փ˂ɂ��ʒu�␳
	collisionWithMap( map, inform, move );

	//�n�㔻��ɂ��ʒu�␳
	onGround( map );

	//���S����
	if ( position.y > SCREEN_Y + CHIP ){ action = DEAD; }

	//�ړ�����
	position.x = max( CHIP / 2, position.x );//���[
	position.x = min( map.getWidthF() - CHIP / 2, position.x );//�E�[

	//�`��ʒu�̎Z�o
	if ( position.x < SCREEN_X / 2 )//���[
	{ 
		draw.x = ( int )position.x;
	}
	else if ( position.x > map.getWidthF() - SCREEN_X / 2 )//�E�[
	{
		draw.x = ( int )position.x - ( map.getWidthF() - SCREEN_X );
	}
	else { draw.x = SCREEN_X / 2; }

	draw.y = ( int )position.y;
    
	//�A�j���[�V����
	animetion( t );
}
//-----------------------------------------------------------------------------
void Player::render( const Graphics& g )const
{
	int  herf = SIZE / 2;
	int x = ( int )( position.x - herf );
	int y = ( int )( position.y - herf );
	int w = ( int )( position.x + herf ) + 1;
	int h = ( int )( position.y + herf ) + 1;

	DrawRotaGraph( draw.x, draw.y - 1, 1.0, 0,  
		g.getChip( anime ), true, isTurn );
	//DrawBox( x, y, w, h, GetColor( 255, 0, 0 ), false );
}
//-----------------------------------------------------------------------------
void Player::reset()
{
	action = STAND;
	jump =  0.0F;
	anime = 0; 
	isTurn = true;
	isGround = false;
	position.set( 160.0F, 120.0F ); //�v���C���[�̍��W��������
}
//-----------------------------------------------------------------------------
void Player::animetion( const Timer& t )
{
	static const std::array <int, 4> an = { 1, 0, 2, 0 };
	unsigned int time = t.time % 40;

	switch ( action )
	{
	case STAND:
		anime = 0;
		break;

	case JUMP:
		anime = 3;
		break;

	case WALK:
		anime = an.at( time / 10 );
		break;

	default:
		break;
	}
}
//-----------------------------------------------------------------------------
void Player::collisionWithMap( Map& map, Inform& inform, Position<float>& move )
{
	//�L�����N�^�̍���A�E��A�����A�E�������������蔻��
	float upper  = position.y - SIZE / 2;
    float bottom = position.y + SIZE / 2;
    float left   = position.x - SIZE / 2;
	float right  = position.x + SIZE / 2;
	Position<float> pos1, pos2;

	//�}�b�v�ɏՓ˂��Ă��邩���ׁA�Փ˂��Ă�����␳����
	//�v���C���[�����ƃu���b�N��ӂ̏Փ˔���
	if ( move.y > 0.0F )
	{
		pos1.set( left,  bottom + move.y );//�����_
		pos2.set( right, bottom + move.y );//���E�_

		switch ( map.getObjectFromTwoPoints( pos1, pos2 ))
		{
			case 1://�ʏ�u���b�N
				adjustMovement( move.y, bottom );
				jump = 0.0F;
				break;
			case 2://�R�C��
				map.setObjectFromTwoPoints( pos1, pos2 );
				inform.addScore( 10 );
				break;
			case 3://�N���A
				action = CLEAR;
				break;
		}
	}
	//�v���C���[�㕔�ƃu���b�N���ӂ̏Փ˔���
	else if ( move.y < 0.0F )
	{
		pos1.set( left,  upper + move.y );//�㍶�_
		pos2.set( right, upper + move.y );//��E�_

		switch ( map.getObjectFromTwoPoints( pos1, pos2 ))
		{
			case 1://�ʏ�u���b�N
				adjustMovement( move.y, upper, 1 );
				jump = 0.0F;
				break;
			case 2://�R�C��
				map.setObjectFromTwoPoints( pos1, pos2 );
				inform.addScore( 10 );
				break;
			case 3://�N���A
				action = CLEAR;
				break;
			//default:
		}
	}

	position.y += move.y;//�㉺�ړ����������Z

	//�v���C���[�����ƃu���b�N�E���̏Փ˔���
	if ( move.x < 0.0F )
	{
		pos1.set( left + move.x, upper );//�㍶�_
		pos2.set( left + move.x, bottom );//�����_

		switch ( map.getObjectFromTwoPoints( pos1, pos2 ))
		{
			case 1://�ʏ�u���b�N
				adjustMovement( move.x, left, 1 );
				break;
			case 2://�R�C��
				map.setObjectFromTwoPoints( pos1, pos2 );
				inform.addScore( 10 );
				break;
			case 3://�N���A
				action = CLEAR;
				break;
			//default:
		}
	}
	//�v���C���[�E���ƃu���b�N�����̏Փ˔���
	else if ( move.x > 0.0F )
	{
		pos1.set( right + move.x, upper );//��E�_
		pos2.set( right + move.x, bottom );//���E�_

		switch ( map.getObjectFromTwoPoints( pos1, pos2 ))
		{
			case 1://�ʏ�u���b�N
				adjustMovement( move.x, right );
				break;
			case 2://�R�C��
				map.setObjectFromTwoPoints( pos1, pos2 );
				inform.addScore( 10 );
				break;
			case 3://�N���A
				action = CLEAR;
				break;
			//default:
		}
	}

	position.x += move.x;//���E�ړ����������Z
}
//-----------------------------------------------------------------------------
void Player::adjustMovement( float& move, const float dir, const int shift )
{
	const float MARGIN = 0.5F;//�������J��グ�Ȃ��Ƃ��܂����삵�Ȃ�

	//�ǂ̒[�܂ō��W����߂�
	float adjust = (float)((int)( dir + move ) / CHIP + shift ) * CHIP;
	//�㉺���E�Ŗ߂��ʒu���ς��
	if ( shift ){ move = adjust - dir + MARGIN; }
	else{ move = adjust - dir - MARGIN; }	
}
//-----------------------------------------------------------------------------
void Player::onGround( Map& map )
{
	//�ڒn����
	float bottom = position.y + ( SIZE / 2 )+ 1.0F;
    float left   = position.x - SIZE / 2;
	float right  = position.x + SIZE / 2;
	Position<float> pos1( left, bottom );//�����_
	Position<float> pos2( right, bottom );//���E�_

	if ( map.getObjectFromTwoPoints( pos1, pos2 ) == 1 ){ isGround = true; }
	else
	{ 	
		isGround = false; 
		action = JUMP; 
	}
}
