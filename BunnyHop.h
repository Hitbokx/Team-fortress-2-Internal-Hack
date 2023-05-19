#pragma once
#include "Classes.h"
#include "Structs.h"
#include <Windows.h>

bool isPlayerMoving( PlayerEnt* pLocalPlayer )
{
	int playerVel{ (int)(pLocalPlayer->velocity.x + pLocalPlayer->velocity.y + pLocalPlayer->velocity.z) };
	if ( playerVel != 0 )
		return true;
	else
		return false;
}

inline void BunnyHop( PlayerEnt* pLocalPlayer )
{
	if ( isPlayerMoving( pLocalPlayer ) )
	{
		if ( GetAsyncKeyState( VK_SPACE ) )
		{
			if ( pLocalPlayer->flag & FLAG.onGround )
			{
				*(uintptr_t*)(modBase.client + offs.fJump) |= force.jump;
			}
			else
			{
				*(uintptr_t*)(modBase.client + offs.fJump) &= ~force.jump;
			}
		}
	}
}