#pragma once
#include "structs.h"

#define END_OF_FREE_LIST -1
#define ENTRY_IN_USE -2

void setTeamColour( GlowObjectDefinition_t& glowObject, int health )
{
	glowObject.m_vGlowColor = Vector3( (health * 0.01), (health * -0.01 + 1), 0.f );
	glowObject.m_flGlowAlpha = 1.7f;
}

void setEnemyColour( GlowObjectDefinition_t& glowObject, int health)
{
	glowObject.m_vGlowColor = Vector3( 0.f, 0.f, 2.f );
	glowObject.m_flGlowAlpha = 1.7f;
}

void resetColour( GlowObjectDefinition_t& glowObject )
{
	glowObject.m_vGlowColor = Vector3{ 0.f,0.f,0.f };
	glowObject.m_flGlowAlpha = 0.f;
}

void Glow(  )
{
	CGlowObjectManager* glowobjectManager{ (CGlowObjectManager*)(modBase.client + offs.dwGlowObjectManager) };

	for ( const auto & ent : hack.pEntList->EntList )
	{
		if ( !ent.m_pEntity || ent.m_pEntity == hack.pLocalPlayer || ent.m_pEntity->bDormant )
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

		CEntInfo* pInfo{ &hack.pEntList->EntList[Index] };

		int serialNum{ glowobject.m_hEntity.GetSerialNumber( ) };

		entity = (PlayerEnt*)pInfo->m_pEntity;

		if ( entity )
		{
			if ( entity->team == hack.pLocalPlayer->team )
				setTeamColour( glowobject, entity->health );

			else
				setEnemyColour( glowobject, entity->health );
		}
	}
}

void unGlow(  )
{
	CGlowObjectManager* glowobjectManager{ (CGlowObjectManager*)(modBase.client + offs.dwGlowObjectManager) };

	for ( const auto& ent : hack.pEntList->EntList )
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