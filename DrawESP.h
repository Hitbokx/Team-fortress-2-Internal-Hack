#pragma once
#include "Include.h"
#include "dxStuff.h"
#include "Structs.h"
#include "Classes.h"
#include "Draw.h"

void drawSnapLines( )
{
	DrawFilledRect( directx.window.windowWidth / 2 - 2, directx.window.windowHeight / 2 - 2, 4, 4, D3DCOLOR_ARGB( 255, 255, 255, 255 ) );
}