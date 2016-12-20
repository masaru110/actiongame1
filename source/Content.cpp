//=============================================================================
//	Content.cpp
//=============================================================================
#include "Content.h"
#include "Define.h"
#include "Input.h"

//-----------------------------------------------------------------------------
struct Sequence
{
	Sequence(){}
	virtual ~Sequence(){}
	virtual void update( const Input&, Content* ) = 0;
	virtual void render()const = 0;
};
//-----------------------------------------------------------------------------
struct Start :public Sequence
{
	void update( const Input&, Content* );
	void render()const;
}start;
//-----------------------------------------------------------------------------
struct MainSequence :public Sequence
{
	void update( const Input&, Content* );
	void render()const;
}mainSequence;
//-----------------------------------------------------------------------------
struct Dead :public Sequence
{
	void update( const Input&, Content* );
	void render()const;
}dead;
//-----------------------------------------------------------------------------
struct Clear :public Sequence
{
	void update( const Input&, Content* );
	void render()const{}
}clear;
//-----------------------------------------------------------------------------
void Start::update( const Input& input, Content* content )
{
	content->player.update( input, content->timer, content->map, content->inform );
	if ( content->player.isDied() ){ content->changeSequence( &dead ); }

	if ( content->isCounter( 60 ))
	{ 
		content->changeSequence( &mainSequence );
	}
}
//-----------------------------------------------------------------------------
void Start::render()const
{
	DrawFormatString( 100, 100, 0xff0000, "START!!" );
}
//-----------------------------------------------------------------------------
void MainSequence::update( const Input& input, Content* content )
{
	content->player.update( input, content->timer, content->map, content->inform );
	if ( content->player.isDied() ){ content->changeSequence( &dead ); }

	//content->enemy.update( content->timer, content->map );
}
//-----------------------------------------------------------------------------
void MainSequence::render()const
{
}
//-----------------------------------------------------------------------------
void Dead::update( const Input& input, Content* content )
{
	if ( content->isCounter( 120 ))
	{
		content->player.reset();
		content->changeSequence( &start );
	}
}
//-----------------------------------------------------------------------------
void Dead::render()const
{
	DrawFormatString( 100, 100, 0xff0000, "DEAD!!" );
}
//-----------------------------------------------------------------------------
void Clear::update( const Input& input, Content* content )
{
}
//-----------------------------------------------------------------------------
Content::Content(): sequence( nullptr ), proceed( true )
{
	sequence = &start;
	graphics.isCreatedChips( "resorce/chip01.png" );
	graphics.isCreatedStrings( "resorce/atari_font.png" );
}
//-----------------------------------------------------------------------------
void Content::update( const Input& input )
{
	sequence->update( input, this );
	timer.update();
}
//-----------------------------------------------------------------------------
void Content::render()const
{	
	//”wŒiF
	DrawBox( 0, 0, SCREEN_X, SCREEN_Y, GetColor( 51, 187, 255 ), true );
	map.render();
	//enemy.render( graphics );

	//DrawFormatString( 100, 5, 0xffffff, "SCORE %d", score );
	DrawFormatString( 240, 5, 0xffffff, "TIME %d", 255 - timer.time / 60 );
	inform.render( graphics );

	player.render( graphics );
	sequence->render();
}
//-----------------------------------------------------------------------------
bool Content::isCounter( const unsigned int max )
{
	if ( count.time > max )
	{ 
		count.clear(); 
		return true; 
	}

	count.update();
	return false;
}