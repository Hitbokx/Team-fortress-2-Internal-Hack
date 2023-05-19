#pragma once
#include "Classes.h"
#include "Structs.h"
#include "Include.h"

inline void TriggerBot( PlayerEnt* pLocalPlayer, EntityList* pEntList, int numPlayers )
{
	if ( !bools.bShotNow )
	{
		*(uintptr_t*)(modBase.client + offs.fAttack) &= ~force.attack;

		bools.bShotNow = !bools.bShotNow;
	}

	if ( (pEntList->EntList[(pLocalPlayer->crossHairId) - 1].m_pEntity->team) == pLocalPlayer->team )
		return;

	if ( (pEntList->EntList[(pLocalPlayer->crossHairId) - 1].m_pEntity->health) <= 0 )
		return;
	
	if ( pLocalPlayer->crossHairId > numPlayers && pLocalPlayer->crossHairId <= 0 )
		return;


	if ( bools.bShotNow )
	{
		*(uintptr_t*)(modBase.client + offs.fAttack) |= force.attack;
		bools.bShotNow = !bools.bShotNow;
	}
}