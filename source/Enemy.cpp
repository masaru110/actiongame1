//=============================================================================
//	Enemy.cpp
//=============================================================================
#include "Enemy.h"
#include "Map.h"
#include "Graphics.h"

//-----------------------------------------------------------------------------
Enemy::Enemy(): action( STAND ), jump( 0.0F ), anime( 0 ), isGround( false )
{
	position.set( 200.0F, 220.0F ); //座標を設定
}
//-----------------------------------------------------------------------------
void Enemy::update( const Timer& t, Map& map )
{ 
	const float SPEED = 1.0F;
	const float GRAVITY = 0.2F; 
	const float JUMP_POWER = 5.0F;
	const float MARGIN = 0.5F;

	Position<float> move;
	action = STAND;

	move.x -= SPEED; 

	jump += GRAVITY;//落下処理	
	move.y = jump;//落下速度を移動量に加える

	//キャラクタの左上、右上、左下、右下部分が当たり判定のある
	float upper  = position.y - SIZE / 2;
    float bottom = position.y + SIZE / 2;
    float left   = position.x - SIZE / 2;
	float right  = position.x + SIZE / 2;
	//float adjust;

	////マップに衝突しているか調べ、衝突していたら補正する
	////プレイヤー下部とブロック上辺の衝突判定
	//if (( move.y > 0.0F ) && 
	//   ( map.isCollided( left,  bottom + move.y ) ||
	//	 map.isCollided( right, bottom + move.y )))
	//{
	//	if ( map.getObject() == OBJECT_BLOCK )
	//	{
	//		adjust = (float)((int)( bottom + move.y ) / CHIP ) * CHIP;
	//		move.y = adjust - bottom - MARGIN;
	//		jump = 0.0F;
	//	}
	//}

	////プレイヤー上部とブロック下辺の衝突判定
	//else if (( move.y < 0.0F ) &&
	//   ( map.isCollided( left,  upper + move.y ) ||
	//	 map.isCollided( right, upper + move.y )))
	//{
	//	if ( map.getObject() == OBJECT_BLOCK )
	//	{
	//		adjust = (float)((int)( upper + move.y ) / CHIP + 1 ) * CHIP;       
	//		move.y = adjust - upper + MARGIN;
	//		jump = 0.0F;
	//	}
	//}

	//position.y += move.y;//上下移動成分を加算

	//float moveL =  left + move.x;
	//float moveR = right + move.x;

	////プレイヤー左側とブロック右側の衝突判定
	//if (( move.x < 0.0F ) &&
	//   ( map.isCollided( moveL, upper ) ||
	//	 map.isCollided( moveL, bottom )))
	//{
	//	if ( map.getObject() == OBJECT_BLOCK )
	//	{
	//		adjust = (float)((int)( moveL ) / CHIP + 1 ) * CHIP;       
	//		move.x = adjust - left + MARGIN;
	//	}
	//}
	////プレイヤー右側とブロック左側の衝突判定
	//else if (( move.x > 0.0F ) &&
	//   ( map.isCollided( moveR, upper ) ||
	//	 map.isCollided( moveR, bottom )))
	//{
	//	if ( map.getObject() == OBJECT_BLOCK )
	//	{
	//		adjust = (float)((int)( moveR ) / CHIP ) * CHIP;       
	//		move.x = adjust - right - MARGIN;
	//	}
	//}

	//position.x = position.x + move.x;

	////接地判定
	//if ( map.isCollided( left, bottom + 1.0F ) || 
	//	map.isCollided( right, bottom + 1.0F )){ isGround = true; }
	//else{ isGround = false; action = JUMP; }

	//////PositionF m = camera.move( position, map.getWidthF());

	//////死亡
	////if ( position.y > SCREEN_Y + CHIP ){ action = DEAD; }

	draw.x = ( int )position.x;
	draw.y = ( int )position.y;
        
	//animetion( t );
}
//-----------------------------------------------------------------------------
void Enemy::render( const Graphics& g )const
{
	int  herf = SIZE / 2;
	int x = ( int )( position.x - herf );
	int y = ( int )( position.y - herf );
	int w = ( int )( position.x + herf ) + 1;
	int h = ( int )( position.y + herf ) + 1;

	//DrawRotaGraph( draw.x, draw.y-1, 1.0, 0, g.get( anime ), true, true );
	DrawBox( x, y, w, h, GetColor( 0, 0, 255 ), true );
}
//-----------------------------------------------------------------------------
void Enemy::reset()
{
	action = STAND;
	jump =  0.0F;
	anime = 0; 
	isGround = false;
	position.set( 160.0F, 120.0F ); //プレイヤーの座標を初期化
}
//-----------------------------------------------------------------------------
void Enemy::animetion( const Timer& t )
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
