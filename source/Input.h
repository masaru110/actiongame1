//=============================================================================
//	Input.h
//=============================================================================
#pragma once
#include <array>

class Input
{
public:

	Input(): previous(), current() {}
	~Input() {}

	void update();
	bool isDownedPad( int )const;
	bool isPressedPad( int )const;
	bool isReleasedPad( int )const;
	bool isDownedKey( int )const;
	bool isPressedKey( int )const;
	bool isReleasedKey( int )const;

private:
	static const int KEY_ALL = 256;

	bool isPressed( bool crnt, bool prev )const { return ( crnt && !prev ); }
	bool isReleased( bool crnt, bool prev )const { return ( !crnt && prev ); }

	struct StKey
	{
		std::array<bool,KEY_ALL> key;//�L�[�̓��͏�Ԋi�[�p�ϐ�
		bool up;//�L�[&�p�b�h���p
		bool down;
		bool left;
		bool right;
		bool padA;
		bool padB;
	};

	StKey previous;
	StKey current;
};
