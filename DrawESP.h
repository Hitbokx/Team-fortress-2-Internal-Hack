#pragma once
#include "Include.h"
#include "dxStuff.h"
#include "Structs.h"
#include "Classes.h"
#include "Draw.h"

bool CheckValidEnt( PlayerEnt* ent, PlayerEnt* pLocalPlayer )
{
	if ( ent == nullptr )
		return false;

	if ( ent == pLocalPlayer )
		return false;

	if ( ent->health <= 1 )
		return false;

	if ( ent->bDormant )
		return false;

	return true;
}

bool  WorldToScreen( Vector3 pos, Vector2& screen, float viewMatrix[16] )
{
	Vector4 clipCoords;
	clipCoords.x = pos.x * viewMatrix[0] + pos.y * viewMatrix[1] + pos.z * viewMatrix[2] + viewMatrix[3];
	clipCoords.y = pos.x * viewMatrix[4] + pos.y * viewMatrix[5] + pos.z * viewMatrix[6] + viewMatrix[7];
	clipCoords.z = pos.x * viewMatrix[8] + pos.y * viewMatrix[9] + pos.z * viewMatrix[10] + viewMatrix[11];
	clipCoords.w = pos.x * viewMatrix[12] + pos.y * viewMatrix[13] + pos.z * viewMatrix[14] + viewMatrix[15];

	if ( clipCoords.w < 0.1f )
		return false;

	Vector3 NDC;
	NDC.x = clipCoords.x / clipCoords.w;
	NDC.y = clipCoords.y / clipCoords.w;
	NDC.z = clipCoords.z / clipCoords.w;

	screen.x = (directx.window.windowWidth / 2 * NDC.x) + (NDC.x + directx.window.windowWidth / 2);
	screen.y = -(directx.window.windowHeight / 2 * NDC.y) + (NDC.y + directx.window.windowHeight / 2);
	return true;
}

void drawSnapLines( )
{
	EntityList* pEntList = *(EntityList**)(modBase.client + offs.entList);
	PlayerEnt* pLocalPlayer{ *(PlayerEnt**)(modBase.client + offs.localPlayer) };

	for( const auto& client : pEntList->EntList )
	{
		PlayerEnt* currEnt{ (PlayerEnt*)(client.m_pEntity) };

		if ( !CheckValidEnt( currEnt, pLocalPlayer ) )
			continue;

		D3DCOLOR colour{};

		if ( currEnt->team == pLocalPlayer->team )
			colour = D3DCOLOR_ARGB( 255, 0, 255, 0 );
		else
			colour = D3DCOLOR_ARGB( 255, 255, 0, 0 );

		float viewMatrix[16]{};

		memcpy( &viewMatrix, (PBYTE*)(modBase.engine + offs.dwViewMatrix), sizeof( viewMatrix ) );

		Vector2 entPos2D{};

		if ( WorldToScreen( currEnt->playerCoordinates, entPos2D, viewMatrix ) )
			DrawLine( entPos2D.x, entPos2D.y, directx.window.windowWidth / 2, directx.window.windowHeight, 2, colour );
	}
}