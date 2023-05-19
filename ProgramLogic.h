#pragma once
#include "Includes.h"
#include "Include.h"

void Run( )
{
	PlayerEnt* pLocalPlayer{ *(PlayerEnt**)(modBase.client + offs.localPlayer) };
	EntityList* pEntList{ *(EntityList**)(modBase.client + offs.entList) };
	int numPlayers{ *(int*)(modBase.engine + offs.numPlayers) };

	while ( !(GetAsyncKeyState( VK_END ) & 1) )
	{
		pLocalPlayer = *(PlayerEnt**)(modBase.client + offs.localPlayer);
		pEntList = *(EntityList**)(modBase.client + offs.entList);
		numPlayers = *(int*)(modBase.engine + offs.numPlayers);

		if ( GetAsyncKeyState( VK_NUMPAD0 ) & 1 )
		{
			if ( !bools.bHop )
			{
				std::cout << "B-Hop Enabled!\n";
				bools.bHop = !bools.bHop;
			}
			else
			{
				std::cout << "B-Hop Disabled!\n";
				bools.bHop = !bools.bHop;
			}
		}

		if ( GetAsyncKeyState( VK_NUMPAD1 ) & 1 )
		{
			if ( !bools.bTriggerBot )
			{
				std::cout << "TriggerBot Enabled!\n";
				bools.bTriggerBot = !bools.bTriggerBot;
			}
			else
			{
				std::cout << "TriggerBot Disabled!\n";
				bools.bTriggerBot = !bools.bTriggerBot;
			}
		}

		if ( GetAsyncKeyState( VK_NUMPAD2 ) & 1 )
		{
			if ( !bools.bGlowHack )
			{
				std::cout << "GlowHack Enabled!\n";
				bools.bGlowHack = !bools.bGlowHack;
			}
			else
			{
				std::cout << "GlowHack Disabled!\n";
				unGlow( pEntList, pLocalPlayer );
				bools.bGlowHack = !bools.bGlowHack;
			}
		}

		if ( GetAsyncKeyState( VK_NUMPAD3 ) & 1 )
		{
			if ( !bools.bAimbot )
			{
				std::cout << "Aimbot Enabled!\n";
				bools.bAimbot = !bools.bAimbot;
			}
			else
			{
				std::cout << "Aimbot Disabled!\n";
				bools.bAimbot = !bools.bAimbot;
			}
		}

		if ( GetAsyncKeyState( VK_NUMPAD4 ) & 1 )
		{
			if ( !bools.bSnapLines )
			{
				std::cout << "Drawing ESP snaplines!\n";
				ESP( );
				bools.bSnapLines = !bools.bSnapLines;
			}
			else
			{
				std::cout << "ESP snaplines won't be Drawn!\n";
				g_hook.unHook<7>( (BYTE*)directx.d3d9Device[42] );
				bools.bSnapLines = !bools.bSnapLines;
			}
		}

		if ( pLocalPlayer )
		{
			if ( bools.bHop )
				BunnyHop( pLocalPlayer );

			if ( bools.bTriggerBot )
				TriggerBot( pLocalPlayer, pEntList, numPlayers );

			if ( bools.bGlowHack )
				Glow( pEntList, pLocalPlayer );

			if ( bools.bAimbot )
				Aimbot( pLocalPlayer, pEntList, numPlayers );
		}

		Sleep( 1 );
	}

	// Extra Check for disabling hook

	if ( bools.bSnapLines )
		g_hook.unHook<7>( (BYTE*)directx.d3d9Device[42] );

	if( bools.bGlowHack )
		unGlow( pEntList, pLocalPlayer );
}