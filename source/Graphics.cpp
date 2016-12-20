//==============================================================================
//	Graphics.cpp
//==============================================================================
#include "Graphics.h"
#include "Define.h"

//------------------------------------------------------------------------------
bool Graphics::isCreatedChips( const char* path )
{
	//âÊëúÉfÅ[É^ÇÃìoò^
	if ( LoadDivGraph( path, CHIPSET_ALL, CHIP_WIDTH, CHIP_HEIGTH, CHIP, CHIP,
		chipset.data() ) == -1 )
	{	
		return false;//ì«Ç›çûÇ›é∏îs
	}
	
	return true;
}
//------------------------------------------------------------------------------
bool Graphics::isCreatedStrings( const char* path )
{
	//âÊëúÉfÅ[É^ÇÃìoò^
	if ( LoadDivGraph( path, STRINGS_ALL, STR_WIDTH, STR_HEIGTH, 8, 8,
		strings.data() ) == -1 )
	{	
		return false;//ì«Ç›çûÇ›é∏îs
	}
	
	return true;
}
//------------------------------------------------------------------------------
void Graphics::destroy()
{
	for ( int i = 0; i < CHIPSET_ALL; ++i )
	{
		DeleteGraph( chipset.at( i ) );
	}
	for ( int i = 0; i < STRINGS_ALL; ++i )
	{
		DeleteGraph( strings.at( i ) );
	}

}
