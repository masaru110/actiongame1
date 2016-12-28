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
	position.set( 160.0F, 120.0F ); //プレイヤーの座標を初期化
}
//-----------------------------------------------------------------------------
void Player::update( const Input& input, const Timer& t, 
	Map& map, Inform& inform )
{ 
	const float SPEED = 1.0F;
	const float GRAVITY = 0.2F; 
	const float JUMP_POWER = 5.0F;
	const float MARGIN = 0.5F;

	Position<float> move;//移動量
	action = STAND;

	// 左右の移動	
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

	// 地面に足が着いている場合のみジャンプ
	if ( isGround && ( input.isPressedPad( PAD_INPUT_UP )))
	{
		jump = -JUMP_POWER;
		isGround = false;
		action = JUMP;
	}
	
	jump += GRAVITY;//落下処理	
	move.y = jump;//落下速度を移動量に加える

	//マップとの衝突による位置補正
	collisionWithMap( map, inform, move );

	//地上判定による位置補正
	onGround( map );

	//死亡処理
	if ( position.y > SCREEN_Y + CHIP ){ action = DEAD; }

	//移動制限
	position.x = max( CHIP / 2, position.x );//左端
	position.x = min( map.getWidthF() - CHIP / 2, position.x );//右端

	//描画位置の算出
	if ( position.x < SCREEN_X / 2 )//左端
	{ 
		draw.x = ( int )position.x;
	}
	else if ( position.x > map.getWidthF() - SCREEN_X / 2 )//右端
	{
		draw.x = ( int )position.x - ( map.getWidthF() - SCREEN_X );
	}
	else { draw.x = SCREEN_X / 2; }

	draw.y = ( int )position.y;
    
	//アニメーション
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
	position.set( 160.0F, 120.0F ); //プレイヤーの座標を初期化
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
	//キャラクタの左上、右上、左下、右下部分が当たり判定
	float upper  = position.y - SIZE / 2;
    float bottom = position.y + SIZE / 2;
    float left   = position.x - SIZE / 2;
	float right  = position.x + SIZE / 2;
	Position<float> pos1, pos2;

	//マップに衝突しているか調べ、衝突していたら補正する
	//プレイヤー下部とブロック上辺の衝突判定
	if ( move.y > 0.0F )
	{
		pos1.set( left,  bottom + move.y );//下左点
		pos2.set( right, bottom + move.y );//下右点

		switch ( map.getObjectFromTwoPoints( pos1, pos2 ))
		{
			case 1://通常ブロック
				adjustMovement( move.y, bottom );
				jump = 0.0F;
				break;
			case 2://コイン
				map.setObjectFromTwoPoints( pos1, pos2 );
				inform.addScore( 10 );
				break;
			case 3://クリア
				action = CLEAR;
				break;
		}
	}
	//プレイヤー上部とブロック下辺の衝突判定
	else if ( move.y < 0.0F )
	{
		pos1.set( left,  upper + move.y );//上左点
		pos2.set( right, upper + move.y );//上右点

		switch ( map.getObjectFromTwoPoints( pos1, pos2 ))
		{
			case 1://通常ブロック
				adjustMovement( move.y, upper, 1 );
				jump = 0.0F;
				break;
			case 2://コイン
				map.setObjectFromTwoPoints( pos1, pos2 );
				inform.addScore( 10 );
				break;
			case 3://クリア
				action = CLEAR;
				break;
			//default:
		}
	}

	position.y += move.y;//上下移動成分を加算

	//プレイヤー左側とブロック右側の衝突判定
	if ( move.x < 0.0F )
	{
		pos1.set( left + move.x, upper );//上左点
		pos2.set( left + move.x, bottom );//下左点

		switch ( map.getObjectFromTwoPoints( pos1, pos2 ))
		{
			case 1://通常ブロック
				adjustMovement( move.x, left, 1 );
				break;
			case 2://コイン
				map.setObjectFromTwoPoints( pos1, pos2 );
				inform.addScore( 10 );
				break;
			case 3://クリア
				action = CLEAR;
				break;
			//default:
		}
	}
	//プレイヤー右側とブロック左側の衝突判定
	else if ( move.x > 0.0F )
	{
		pos1.set( right + move.x, upper );//上右点
		pos2.set( right + move.x, bottom );//下右点

		switch ( map.getObjectFromTwoPoints( pos1, pos2 ))
		{
			case 1://通常ブロック
				adjustMovement( move.x, right );
				break;
			case 2://コイン
				map.setObjectFromTwoPoints( pos1, pos2 );
				inform.addScore( 10 );
				break;
			case 3://クリア
				action = CLEAR;
				break;
			//default:
		}
	}

	position.x += move.x;//左右移動成分を加算
}
//-----------------------------------------------------------------------------
void Player::adjustMovement( float& move, const float dir, const int shift )
{
	const float MARGIN = 0.5F;//少数を繰り上げないとうまく動作しない

	//壁の端まで座標をを戻す
	float adjust = (float)((int)( dir + move ) / CHIP + shift ) * CHIP;
	//上下左右で戻す位置が変わる
	if ( shift ){ move = adjust - dir + MARGIN; }
	else{ move = adjust - dir - MARGIN; }	
}
//-----------------------------------------------------------------------------
void Player::onGround( Map& map )
{
	//接地判定
	float bottom = position.y + ( SIZE / 2 )+ 1.0F;
    float left   = position.x - SIZE / 2;
	float right  = position.x + SIZE / 2;
	Position<float> pos1( left, bottom );//下左点
	Position<float> pos2( right, bottom );//下右点

	if ( map.getObjectFromTwoPoints( pos1, pos2 ) == 1 ){ isGround = true; }
	else
	{ 	
		isGround = false; 
		action = JUMP; 
	}
}
