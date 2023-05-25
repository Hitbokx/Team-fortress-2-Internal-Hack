#pragma once
#include "Classes.h"
#include "Vector.h"
#include "Structs.h"
#include "Include.h"

Player* getClosestEnemy(  )
{
	float closestDistance{ 1000000 };
	int closestDistanceIndex{ -1 };

	for ( int i{ 1 }; i < hack.numPlayers; ++i )
	{
		Player* currPlayer{ (Player*)(hack.pEntList->EntList[i].m_pEntity) };

		if ( (!currPlayer) || (!(*(uintptr_t*)currPlayer)) || ((uintptr_t)currPlayer == (uintptr_t)hack.pLocalPlayer))
			continue;

		if ( currPlayer->bDormant )
			continue;

		if ( currPlayer->health <= 1 || hack.pLocalPlayer->health <= 1 )
			continue;

		if ( currPlayer->team == hack.pLocalPlayer->team )
			continue;

		float currDistance{ ((LocalPlayer*)hack.pLocalPlayer)->getDistance( currPlayer->playerCoordinates ) };

		if ( currDistance < closestDistance )
		{
			closestDistance = currDistance;
			closestDistanceIndex = i;
		}
	}

	if ( closestDistanceIndex == -1 )
		return NULL;
	else
		return (Player*)(hack.pEntList->EntList[closestDistanceIndex].m_pEntity);
}

void Aimbot(  )
{
	Player* closestEnemy{ getClosestEnemy(  ) };

	if ( closestEnemy )
	{
		Vector3 headBonePos{ closestEnemy->GetHeadBone() };

		((LocalPlayer*)hack.pLocalPlayer)->aimAt( headBonePos );
	}
}