#pragma once
#include "Include.h"
#include "dxStuff.h"
#include "Structs.h"
#include "HookingClass.h"
#include "DrawESP.h"

tEndScene oEndScene{ nullptr };

void APIENTRY hkEndScene( LPDIRECT3DDEVICE9 o_pDevice )
{
	if ( !directx.pDevice )
		directx.pDevice = o_pDevice;

	if ( bools.bSnapLines )
		drawSnapLines( );

	oEndScene( directx.pDevice );
}

void ESP( )
{
	if ( GetD3D9Device( directx.d3d9Device, sizeof( directx.d3d9Device ) ) )
	{
		oEndScene = (tEndScene)g_hook.TrampHook32<7>( (BYTE*)directx.d3d9Device[42], (BYTE*)hkEndScene );
	}
}