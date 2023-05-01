#pragma once
#include <vector>
#include "structs.h"

#define END_OF_FREE_LIST -1
#define ENTRY_IN_USE -2

void setTeamColour( GlowObjectDefinition_t& glowObject )
{
	glowObject.m_vGlowColor = Vector3( 0.f, 0.f, 1.f );
	glowObject.m_flGlowAlpha = 1.7f;
}

void setEnemyColour( GlowObjectDefinition_t& glowObject )
{
	glowObject.m_vGlowColor = Vector3( 1.f, 0.f, 0.f );
	glowObject.m_flGlowAlpha = 1.7f;
}

void Glow(uintptr_t cModuleBase, EntityList* pEntList, PlayerEnt* pLocalPlayer )
{
	CGlowObjectManager* glowobjectManager{ (CGlowObjectManager*)(cModuleBase + offs.dwGlowObjectManager) };

	char entity{ 0 };

	for ( const auto& ent : pEntList->EntList )
	{
		
		if ( ent.entPtr )
		{
			ent.entPtr->specGlowEnabled = true;
			ent.entPtr->glowEnabled = true;
			ent.entPtr->boldGlowEnabled = false;

			if ( ent.entPtr->team == pLocalPlayer->team )
			{

			}

			else
			{
				entity = 'e';
			}
		}
	}

	for ( int index = 0; index < glowobjectManager->m_GlowObjectDefinitions.m_Size; index++ )
	{
		GlowObjectDefinition_t& glowobject = glowobjectManager->m_GlowObjectDefinitions[index];

		if ( glowobject.m_nNextFreeSlot != ENTRY_IN_USE )
			continue;

		if ( entity )
		{
			switch ( entity )
			{
				case 0: 
					break;

				case 't':
					setTeamColour( glowobject );
					break;

				case 'e':
					setEnemyColour( glowobject );
					break;

				default:
					std::cout << "Error entity!\n";
					break;
			}

		}
		
	}
	Sleep( 1 );
}