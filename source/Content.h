//=============================================================================
//	Content.h
//=============================================================================
#pragma once

class Input;
class Content;

//-----------------------------------------------------------------------------
class State
{
public:
	State():color( 0 ){}
	virtual ~State(){}

	virtual void update( Content* ) = 0;

	int getColor()const{ return color; }

protected:
	int color;
};
//-----------------------------------------------------------------------------
class RedState :public State
{
public:
	void update( Content* );
};
//-----------------------------------------------------------------------------
class BlueState :public State
{
public:
	void update( Content* );
};
//-----------------------------------------------------------------------------
class GreenState :public State
{
public:
	void update( Content* );
};
//-----------------------------------------------------------------------------
class YellowState :public State
{
public:
	void update( Content* );
};
//-----------------------------------------------------------------------------
class Content
{
public:
	Content();
	~Content(){}

	void update( const Input& );
	void render()const;

	bool isProceed(){ return proceed; }

private:
	State* state;
	RedState redState;
	BlueState blueState;
	GreenState greenState;
	YellowState yellowState;

	bool proceed;
};
