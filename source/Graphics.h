//==============================================================================
//	Graphics.h
//==============================================================================
#pragma once
#include <array>

class Graphics
{
public:
	Graphics(){}
	~Graphics(){}

	bool isCreatedChips( const char* );
	bool isCreatedStrings( const char* );
	void destroy();
		 
	int getChip( int num )const{ return chipset.at( num ); }
	int getString( int num )const{ return strings.at( num ); }

private:
	static const int CHIP_WIDTH = 4;
	static const int CHIP_HEIGTH = 3;
	static const int CHIPSET_ALL = CHIP_WIDTH * CHIP_HEIGTH;

	static const int STR_WIDTH = 8;
	static const int STR_HEIGTH = 5;
	static const int STRINGS_ALL = 36;

	std::array<int, CHIPSET_ALL> chipset;
	std::array<int, STRINGS_ALL> strings;
};
