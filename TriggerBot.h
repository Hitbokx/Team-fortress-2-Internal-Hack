#pragma once
#include "Classes.h"
#include "Structs.h"
#include "Include.h"

inline void TriggerBot(  )
{
	if ( !bools.bShotNow )
	{
		*(uintptr_t*)(modBase.client + offs.fAttack) &= ~force.attack;

		bools.bShotNow = !bools.bShotNow;
	}

	if ( ( hack.pEntList->EntList[(hack.pLocalPlayer->crossHairId) - 1].m_pEntity->team) == hack.pLocalPlayer->team )
		return;

	if ( ( hack.pEntList->EntList[( hack.pLocalPlayer->crossHairId) - 1].m_pEntity->health) <= 0 )
		return;
	
	if ( hack.pLocalPlayer->crossHairId > hack.numPlayers && hack.pLocalPlayer->crossHairId <= 0 )
		return;


	if ( bools.bShotNow )
	{
		*(uintptr_t*)(modBase.client + offs.fAttack) |= force.attack;
		bools.bShotNow = !bools.bShotNow;
	}
}