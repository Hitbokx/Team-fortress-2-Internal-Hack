#pragma once
#include <vector>
#include "structs.h"

#define END_OF_FREE_LIST -1
#define ENTRY_IN_USE -2

void setTeamColour( GlowObjectDefinition_t& glowObject )
{
	glowObject.m_vGlowColor = Vector3( 0.f, 0.f, 2.f );
	glowObject.m_flGlowAlpha = 1.7f;
}

void setEnemyColour( GlowObjectDefinition_t& glowObject )
{
	glowObject.m_vGlowColor = Vector3( 2.f, 0.f, 0.f );
	glowObject.m_flGlowAlpha = 1.7f;
}

void Glow(uintptr_t cModuleBase, EntityList* pEntList, PlayerEnt* pLocalPlayer )
{
	CGlowObjectManager* glowobjectManager{ (CGlowObjectManager*)(cModuleBase + offs.dwGlowObjectManager) };

	char entTeam[24]{};

	/*for ( int i{0}; const auto & ent : pEntList->EntList )
	{
		if ( ent.entPtr )
		{
			ent.entPtr->specGlowEnabled = true;
			ent.entPtr->glowEnabled = true;
			ent.entPtr->boldGlowEnabled = false;

			if ( ent.entPtr->team == pLocalPlayer->team )
				entTeam[i] = 't';

			else
				entTeam[i] = 'e';
		}

		++i;
	}*/

	for ( int index{ 0 }; index < glowobjectManager->m_GlowObjectDefinitions.m_Size; ++index )
	{
		GlowObjectDefinition_t& glowobject = glowobjectManager->m_GlowObjectDefinitions[index];

		if ( glowobject.m_nNextFreeSlot != ENTRY_IN_USE )
			continue;

		//if ( index < sizeof( entTeam ) )
		//{

			if ( (pEntList->EntList[index].entPtr->team) == pLocalPlayer->team )
				setTeamColour( glowobject );

			else
				setEnemyColour( glowobject );

			/*	if ( entTeam[index] == 't' )
					setTeamColour( glowobject );

				else
					setEnemyColour( glowobject );
			*/
		//}
	}
}

void unGlow( EntityList* pEntList, PlayerEnt* pLocalPlayer )
{
	for ( const auto& ent : pEntList->EntList )
	{
		if ( ent.entPtr )
		{
			ent.entPtr->specGlowEnabled = false;
			ent.entPtr->glowEnabled = false;
			ent.entPtr->boldGlowEnabled = false;
		}
	}
}