#pragma once
#include "Classes.h"
#include "Structs.h"
#include <Windows.h>

inline void TriggerBot( PlayerEnt* pLocalPlayer, uintptr_t cModuleBase, EntityList* pEntList, int numPlayers )
{
	if ( !bools.bShotNow )
	{
		*(uintptr_t*)(cModuleBase + offs.fAttack) &= ~force.attack;

		bools.bShotNow = !bools.bShotNow;
	}

	if ( (pEntList->EntList[(pLocalPlayer->crossHairId) - 1].entPtr->team) == pLocalPlayer->team )
		return;

	if ( (pEntList->EntList[(pLocalPlayer->crossHairId) - 1].entPtr->health) <= 0 )
		return;
	
	if ( pLocalPlayer->crossHairId > numPlayers && pLocalPlayer->crossHairId <= 0 )
		return;


	if ( bools.bShotNow )
	{
		*(uintptr_t*)(cModuleBase + offs.fAttack) |= force.attack;
		bools.bShotNow = !bools.bShotNow;
	}
}