#pragma once
#include "Include.h"
#include "DirectXStuff.h"
#include "Structs.h"
#include "HookingClass.h"
#include "DrawESP.h"
#include "TraceLine.h"

void APIENTRY HkEndScene( LPDIRECT3DDEVICE9 o_pDevice )
{
	if ( !g_dxStuff.get( )->m_directX.pDevice )
		g_dxStuff.get( )->m_directX.pDevice = o_pDevice;

	g_draw.get( )->DrawText( "1ST COPIED ESP BY HITBOKX!", g_dxStuff.get( )->m_window.windowWidth / 2, g_dxStuff.get( )->m_window.windowHeight - 20, D3DCOLOR_ARGB( 255, 0, 200, 200 ) );

	DrawMenu( );

	for ( const auto& client : hack.pEntList->EntList )
	{
		PlayerEnt* currEnt{ (PlayerEnt*)(client.m_pEntity) };

		if ( !CheckValidEnt( currEnt ) )
			continue;

		if ( !isVisible( currEnt ) )
			continue;

		D3DCOLOR espColour, snapLineColour, velColour, headLineColour;

		if ( currEnt->team == hack.pLocalPlayer->team )
		{
			espColour = Colour::Ally::esp;
			snapLineColour = Colour::Ally::snapline;
			velColour = Colour::Ally::velocity;
			headLineColour = Colour::Ally::headline;
		}
		else
		{
			espColour = Colour::Enemy::esp;
			snapLineColour = Colour::Enemy::snapline;
			velColour = Colour::Enemy::velocity;
			headLineColour = Colour::Enemy::headline;
		}

		if ( !bools.bShowTeamates && (currEnt->team == hack.pLocalPlayer->team) )
			continue;

		Vector3 entHead3D{ ((Player*)currEnt)->GetHeadBone( ) };

		entHead3D.z += 8;
		Vector2 entPos2D{};
		Vector2 entHead2D{};

		if ( WorldToScreen( currEnt->playerCoordinates, entPos2D ) )
		{
			if ( bools.bVelEsp )
			{
				Vector3 velocity3D{ currEnt->playerCoordinates + (currEnt->velocity * 0.25) };
				Vector2 velocity2D{};

				if ( WorldToScreen( velocity3D, velocity2D ) )
				{
					g_draw.get( )->DrawLine( entPos2D, velocity2D, 2, velColour );
					g_draw.get( )->DrawFilledRect( velocity2D.x - 2, velocity2D.y - 2, 4, 4, espColour );
				}
			}

			if ( bools.bSnapLines )
				drawSnapLines( entPos2D, snapLineColour );

			if ( WorldToScreen( entHead3D, entHead2D ) )
			{
				if ( bools.bBox2D )
					DrawESPBox2D( entHead2D, entPos2D, 2, espColour );

				if ( bools.bBox3D )
					DrawESPBox3D( entHead3D, currEnt->playerCoordinates, currEnt->viewAngles.y, 25, 2, espColour );

				if ( bools.bStatus2D )
					DrawStatus( currEnt->health, entHead2D, entPos2D );

				if ( bools.bStatusText )
					DisplayStatus( currEnt->health, entPos2D );

				if ( bools.bHeadlineEsp )
					DrawHeadLine( currEnt, entHead3D, headLineColour );
			}
		}
	}

	if ( bools.bRcsCrosshair )
		DrawCrossHair( );

	g_oEndScene( g_dxStuff.get( )->m_directX.pDevice );
}

void ESP( )
{
	g_dxStuff.get( )->hookEndScene( );
}