#pragma once
#include <vector>
#include "structs.h"

#define END_OF_FREE_LIST -1
#define ENTRY_IN_USE -2

void setTeamColour( GlowObjectDefinition_t& glowObject )
{
	glowObject.m_vGlowColor = Vector3( 2.f, 0.f, 0.f );
	glowObject.m_flGlowAlpha = 1.7f;
}

void setEnemyColour( GlowObjectDefinition_t& glowObject )
{
	glowObject.m_vGlowColor = Vector3( 0.f, 0.f, 2.f );
	glowObject.m_flGlowAlpha = 1.7f;
}

void resetColour( GlowObjectDefinition_t& glowObject )
{
	glowObject.m_vGlowColor = Vector3{ 0.f,0.f,0.f };
	glowObject.m_flGlowAlpha = 0.f;
}

void Glow(uintptr_t cModuleBase, EntityList* pEntList, PlayerEnt* pLocalPlayer )
{
	CGlowObjectManager* glowobjectManager{ (CGlowObjectManager*)(cModuleBase + offs.dwGlowObjectManager) };

	for ( const auto & ent : pEntList->EntList )
	{
		if ( !ent.m_pEntity || ent.m_pEntity == pLocalPlayer || ent.m_pEntity->bDormant )
			continue;

		if ( ent.m_pEntity )
		{
			ent.m_pEntity->specGlowEnabled = true;
			ent.m_pEntity->glowEnabled = true;
			ent.m_pEntity->boldGlowEnabled = false;
		}
	}

	for ( int index = 0; index < glowobjectManager->m_GlowObjectDefinitions.m_Size; ++index ) {
		GlowObjectDefinition_t& glowobject = glowobjectManager->m_GlowObjectDefinitions[index];

		if ( glowobject.m_nNextFreeSlot != ENTRY_IN_USE )
			continue;

		PlayerEnt* entity{};

		auto Index{ glowobject.m_hEntity.GetEntryIndex() };

		CEntInfo* pInfo{ &pEntList->EntList[Index] };

		int serialNum{ glowobject.m_hEntity.GetSerialNumber( ) };

		entity = (PlayerEnt*)pInfo->m_pEntity;

		if ( entity )
		{
			if ( entity->team == pLocalPlayer->team )
				setTeamColour( glowobject );
			else
				setEnemyColour( glowobject );
		}
	}
}

void unGlow( uintptr_t cModuleBase, EntityList* pEntList, PlayerEnt* pLocalPlayer )
{
	CGlowObjectManager* glowobjectManager{ (CGlowObjectManager*)(cModuleBase + offs.dwGlowObjectManager) };

	for ( const auto& ent : pEntList->EntList )
	{
		if ( ent.m_pEntity )
		{
			ent.m_pEntity->specGlowEnabled = false;
			ent.m_pEntity->glowEnabled = false;
			ent.m_pEntity->boldGlowEnabled = false;
		}
	}

	for ( int index = 0; index < glowobjectManager->m_GlowObjectDefinitions.m_Size; ++index ) {
		GlowObjectDefinition_t& glowobject = glowobjectManager->m_GlowObjectDefinitions[index];

		if ( glowobject.m_nNextFreeSlot != ENTRY_IN_USE )
			continue;

		resetColour( glowobject );
	}
}