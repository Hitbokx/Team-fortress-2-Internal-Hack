#pragma once
#include "Classes.h"
#include "Structs.h"
#include <Windows.h>

inline void BunnyHop( PlayerEnt* pLocalPlayer, uintptr_t cModuleBase )
{
	if ( GetAsyncKeyState( VK_SPACE ) )
	{
		if ( pLocalPlayer->flag & FLAG.onGround )
		{
			*(uintptr_t*)(cModuleBase + offs.fJump) |= force.jump;
		}
		else
		{
			*(uintptr_t*)(cModuleBase + offs.fJump) &= ~force.jump;
		}
	}
}