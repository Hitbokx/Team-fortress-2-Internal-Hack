#pragma once
#include "Includes.h"
#include "Include.h"

void checkButtons( )
{
	if ( GetAsyncKeyState( Buttons::bHop ) & 1 )
		bools.bHop = !bools.bHop;

	if ( GetAsyncKeyState( Buttons::triggerBotBtn ) & 1 )
		bools.bTriggerBot = !bools.bTriggerBot;

	if ( GetAsyncKeyState( Buttons::glowBtn ) & 1 )
		bools.bGlowHack = !bools.bGlowHack;

	if ( GetAsyncKeyState( Buttons::aimBotBtn ) & 1 )
		bools.bAimbot = !bools.bAimbot;

	if ( GetAsyncKeyState( Buttons::snapLinesBtn ) & 1 )
		bools.bSnapLines = !bools.bSnapLines;

	if ( GetAsyncKeyState( Buttons::showTeamatesBtn ) & 1 )
		bools.bShowTeamates = !bools.bShowTeamates;

	if ( GetAsyncKeyState( Buttons::status2DBtn ) & 1 )
		bools.bStatus2D = !bools.bStatus2D;

	if ( GetAsyncKeyState( Buttons::statusTextBtn ) & 1 )
		bools.bStatusText = !bools.bStatusText;

	if ( GetAsyncKeyState( Buttons::box2DBtn ) & 1 )
		bools.bBox2D = !bools.bBox2D;

	if ( GetAsyncKeyState( Buttons::box3DBtn ) & 1 )
		bools.bBox3D = !bools.bBox3D;

	if ( GetAsyncKeyState( Buttons::headlineEspBtn ) & 1 )
		bools.bHeadlineEsp = !bools.bHeadlineEsp;

	if ( GetAsyncKeyState( Buttons::velEspBtn ) & 1 )
		bools.bVelEsp = !bools.bVelEsp;

	if ( GetAsyncKeyState( Buttons::rcsCrosshairBtn ) & 1 )
		bools.bRcsCrosshair = !bools.bRcsCrosshair;

	if ( GetAsyncKeyState( Buttons::showMenuBtn ) & 1 )
		bools.bShowMenu = !bools.bShowMenu;
}

void CleanUp( )
{
	if ( bools.bGlowHack )
		unGlow( );

	bools.bHop = false;
	bools.bTriggerBot = false;
	bools.bShotNow = false;
	bools.bGlowHack = false;
	bools.bAimbot = false;

	bools.bShowMenu = false;
	bools.bShowTeamates = false;
	bools.bSnapLines = false;
	bools.bBox2D = false;
	bools.bStatus2D = false;
	bools.bStatusText = false;
	bools.bBox3D = false;
	bools.bVelEsp = false;
	bools.bHeadlineEsp = false;
	bools.bRcsCrosshair = false;
}

void Run( )
{
	hack.Init( );
	ESP( );

	while ( !(GetAsyncKeyState( VK_END ) & 1) )
	{
		hack.Update( );

		checkButtons( );

		if ( hack.pLocalPlayer )
		{
			if ( bools.bHop )
				BunnyHop(  );

			if ( bools.bTriggerBot )
				TriggerBot(  );

			if ( bools.bGlowHack )
				Glow(  );
		}

		if ( !bools.bGlowHack )
			unGlow( );

		Sleep( 1 );
	}

	// Extra Check for disabling hook

	CleanUp( );

	Sleep( 1000 );
}