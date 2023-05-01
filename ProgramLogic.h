#pragma once
#include "Includes.h"

void Run( uintptr_t cModuleBase, uintptr_t eModuleBase )
{
	PlayerEnt* pLocalPlayer{ *(PlayerEnt**)(cModuleBase + offs.localPlayer) };
	EntityList* pEntList{ *(EntityList**)(cModuleBase + offs.entList) };
	int numPlayers{ *(int*)(eModuleBase + offs.numPlayers) };

	while ( !(GetAsyncKeyState( VK_END ) & 1) )
	{
		pLocalPlayer = *(PlayerEnt**)(cModuleBase + offs.localPlayer);
		pEntList = *(EntityList**)(cModuleBase + offs.entList);
		numPlayers = *(int*)(eModuleBase + offs.numPlayers);

		if ( GetAsyncKeyState( VK_NUMPAD1 ) & 1 )
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

		if ( GetAsyncKeyState( VK_NUMPAD2 ) & 1 )
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

		if ( GetAsyncKeyState( VK_NUMPAD3 ) & 1 )
		{
			if ( !bools.bGlowHack )
			{
				std::cout << "GlowHack Enabled!\n";
				bools.bGlowHack = !bools.bGlowHack;
			}
			else
			{
				std::cout << "GlowHack Disabled!\n";
				bools.bGlowHack = !bools.bGlowHack;
			}
		}

		if ( pLocalPlayer )
		{
			if ( bools.bHop )
				BunnyHop( pLocalPlayer, cModuleBase );

			if ( bools.bTriggerBot )
				TriggerBot( pLocalPlayer, cModuleBase, pEntList, numPlayers );

			if ( bools.bGlowHack )
				Glow( cModuleBase, pEntList, pLocalPlayer );
		}
		Sleep( 1 );
	}
}