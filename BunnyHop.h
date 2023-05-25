#pragma once
#include "Classes.h"
#include "Structs.h"
#include <Windows.h>

bool isPlayerMoving(  )
{
	int playerVel{ (int)( hack.pLocalPlayer->velocity.x + hack.pLocalPlayer->velocity.y + hack.pLocalPlayer->velocity.z) };
	if ( playerVel != 0 )
		return true;
	else
		return false;
}

inline void BunnyHop(  )
{
	if ( isPlayerMoving(  ) )
	{
		if ( GetAsyncKeyState( VK_SPACE ) )
		{
			if ( hack.pLocalPlayer->flag & FLAG.onGround )
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