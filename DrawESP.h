#pragma once
#include "Include.h"
#include "DirectXStuff.h"
#include "Structs.h"
#include "Classes.h"
#include "Draw.h"

inline bool CheckValidEnt( PlayerEnt* ent )
{
	if ( ent == nullptr )
		return false;

	if ( ent == hack.pLocalPlayer )
		return false;

	if ( ent->health <= 1 )
		return false;

	if ( ent->bDormant )
		return false;

	return true;
}

inline bool WorldToScreen( Vector3 pos, Vector2& screen )
{
	Vector4 clipCoords{};

	clipCoords.x = pos.x * hack.viewMatrix[0] + pos.y * hack.viewMatrix[1] + pos.z * hack.viewMatrix[2] + hack.viewMatrix[3];
	clipCoords.y = pos.x * hack.viewMatrix[4] + pos.y * hack.viewMatrix[5] + pos.z * hack.viewMatrix[6] + hack.viewMatrix[7];
	clipCoords.z = pos.x * hack.viewMatrix[8] + pos.y * hack.viewMatrix[9] + pos.z * hack.viewMatrix[10] + hack.viewMatrix[11];
	clipCoords.w = pos.x * hack.viewMatrix[12] + pos.y * hack.viewMatrix[13] + pos.z * hack.viewMatrix[14] + hack.viewMatrix[15];

	if ( clipCoords.w < 0.1f )
		return false;

	Vector3 NDC;
	NDC.x = clipCoords.x / clipCoords.w;
	NDC.y = clipCoords.y / clipCoords.w;
	NDC.z = clipCoords.z / clipCoords.w;

	screen.x = (g_dxStuff.get( )->m_window.windowWidth / 2 * NDC.x) + (NDC.x + g_dxStuff.get( )->m_window.windowWidth / 2);
	screen.y = -(g_dxStuff.get( )->m_window.windowHeight / 2 * NDC.y) + (NDC.y + g_dxStuff.get( )->m_window.windowHeight / 2);
	return true;
}

inline Vector3 TransformVector( Vector3 src, Vector3 ang, float distance )
{
	Vector3 newPos{};
	newPos.x = src.x + (cosf( TORAD( ang.y ) ) * distance);
	newPos.y = src.y + (sinf( TORAD( ang.y ) ) * distance);
	newPos.z = src.z + (tanf( TORAD( ang.x ) ) * distance);

	return newPos;
}

inline void drawSnapLines( Vector2 entPos2D, D3DCOLOR colour )
{
	g_draw.get( )->DrawLine( entPos2D.x, entPos2D.y, g_dxStuff.get()->m_window.windowWidth / 2, g_dxStuff.get( )->m_window.windowHeight, 2, colour );
}

inline void DrawCrossHair( )
{
	Vector2 crossHair2D;
	crossHair2D.x = g_dxStuff.get( )->m_directX.window.windowWidth / 2;
	crossHair2D.y = g_dxStuff.get( )->m_directX.window.windowHeight / 2;
	int crossHairSize{ 4 };

	Vector2 l, r, t, b;

	l = r = t = b = crossHair2D;
	l.x -= crossHairSize;
	r.x += crossHairSize;
	b.y += crossHairSize;
	t.y -= crossHairSize;

	g_draw.get( )->DrawLine( l, r, 2, D3DCOLOR_ARGB( 255, 255, 255, 255 ) );
	g_draw.get( )->DrawLine( t, b, 2, D3DCOLOR_ARGB( 255, 255, 255, 255 ) );
}

inline void DrawESPBox2D( Vector2 top, Vector2 bottom, int thickness, D3DCOLOR color )
{
	int height = std::abs( top.y - bottom.y );

	Vector2 topLeft{};
	topLeft.x = top.x - height / 4;
	topLeft.y = top.y;


	Vector2 topRight{};
	topRight.x = top.x + height / 4;
	topRight.y = top.y;

	Vector2 botLeft{};
	botLeft.x = bottom.x - height / 4;
	botLeft.y = bottom.y;

	Vector2 botRight{};
	botRight.x = bottom.x + height / 4;
	botRight.y = bottom.y;

	g_draw.get( )->DrawLine( topLeft, topRight, thickness, color );
	g_draw.get( )->DrawLine( botLeft, botRight, thickness, color );
	g_draw.get( )->DrawLine( topLeft, botLeft, thickness, color );
	g_draw.get( )->DrawLine( topRight, botRight, thickness, color );
}

inline void DrawESPBox3D( Vector3 top, Vector3 bottom, float a, int width, int thickness, D3DCOLOR colour )
{
	int height3D = std::abs( top.z - bottom.z );
	std::array<Vector3, 4> bottomCorner3D;
	std::array<Vector3, 4> topCorner3D;

	for ( short i{ 0 }; i < 4; ++i )
	{
		bottomCorner3D[i].z = bottom.z;

		topCorner3D[i].x = bottomCorner3D[i].x = bottom.x + (cos( TORAD( a + 45 + (i * 90) ) ) * width);
		topCorner3D[i].y = bottomCorner3D[i].y = bottom.y + (sin( TORAD( a + 45 + (i * 90) ) ) * width);

		topCorner3D[i].z = bottomCorner3D[i].z + height3D;
	}

	std::array<Vector2, 4> bottomCorner2D;
	std::array<Vector2, 4> topCorner2D;

	for ( short i{ 0 }; i < 4; ++i )
	{
		if ( WorldToScreen( bottomCorner3D[i], bottomCorner2D[i] ) && WorldToScreen( topCorner3D[i], topCorner2D[i] ) )
		{
			g_draw.get( )->DrawLine( topCorner2D[i], bottomCorner2D[i], thickness, colour );

			if ( i == 3 )
			{
				g_draw.get( )->DrawLine( topCorner2D[i], topCorner2D[0], thickness, colour );
				g_draw.get( )->DrawLine( bottomCorner2D[i], bottomCorner2D[0], thickness, colour );
			}
			else
			{
				if ( WorldToScreen( bottomCorner3D[i + 1], bottomCorner2D[i + 1] ) && WorldToScreen( topCorner3D[i + 1], topCorner2D[i + 1] ) )
				{
					g_draw.get( )->DrawLine( topCorner2D[i], topCorner2D[i + 1], thickness, colour );
					g_draw.get( )->DrawLine( bottomCorner2D[i], bottomCorner2D[i + 1], thickness, colour );
				}
			}
		}
	}
}

inline void DrawStatus( int health, Vector2 entHead2D, Vector2 entPos2D )
{
	int height = std::abs( entPos2D.y - entHead2D.y );
	int dx = entPos2D.x - entHead2D.x;

	float healthPercent{ health / 100.f };

	Vector2 botttomHealth{};
	Vector2 topHealth{};

	int healthHeight = height * healthPercent;

	botttomHealth.y = entPos2D.y;
	botttomHealth.x = entPos2D.x - (height / 4) - 5;

	topHealth.y = entHead2D.y + height - healthHeight;
	topHealth.x = entPos2D.x - (height / 4) - 5 - (dx * healthPercent);

	g_draw.get( )->DrawLine( botttomHealth, topHealth, 2, Colour::health );
}

inline void DisplayStatus( int health, Vector2 entPos2D )
{
	std::stringstream s1;
	s1 << health;

	std::string t1 = "Health(%): " + s1.str( );

	char* healthMsg = (char*)t1.c_str( );
	g_draw.get( )->DrawText( healthMsg, entPos2D.x, entPos2D.y + 4, D3DCOLOR_ARGB( 255, 255, 255, 255 ) );
}

inline void DrawHeadLine( PlayerEnt* currEnt, Vector3 entHead3D, D3DCOLOR headLineColour )
{
	Vector3  head3D = entHead3D;
	head3D.z -= 8;

	Vector3 entAngles{ currEnt->viewAngles.x, currEnt->viewAngles.z, 0 };

	Vector3 endPoint{ TransformVector( head3D, entAngles, 60 ) };

	Vector2 endPoint2D{};
	Vector2 head2D{};

	WorldToScreen( head3D, head2D );

	if ( WorldToScreen( endPoint, endPoint2D ) )
	{
		g_draw.get( )->DrawLine( head2D, endPoint2D, 2, headLineColour );
	}
}

inline void DrawMenu( )
{
	int menuOffX = g_dxStuff.get( )->m_window.windowWidth / 2;
	int menuOffY = 50;

	D3DCOLOR enabled{ D3DCOLOR_ARGB( 255, 0, 255, 0 ) };
	D3DCOLOR disabled{ D3DCOLOR_ARGB( 255, 255, 0, 0 ) };

	if ( !bools.bShowMenu )
	{
		g_draw.get( )->DrawText( "Show Menu (INS)", menuOffX, menuOffY, Colour::text );
	}
	else
	{
		g_draw.get( )->DrawText( "Trigger Bot (NUM_1)", menuOffX, menuOffY + 0 * 12, bools.bTriggerBot ? enabled : disabled );
		g_draw.get( )->DrawText( "Glow (NUM_2)", menuOffX, menuOffY + 1 * 12, bools.bGlowHack ? enabled : disabled );
		g_draw.get( )->DrawText( "AimBot (NUM_3)", menuOffX, menuOffY + 2 * 12, bools.bAimbot ? enabled : disabled );
		g_draw.get( )->DrawText( "Show Teammates (NUM_4)", menuOffX, menuOffY + 3 * 12, bools.bShowTeamates ? enabled : disabled );
		g_draw.get( )->DrawText( "Snaplines (NUM_5)", menuOffX, menuOffY + 4 * 12, bools.bSnapLines ? enabled : disabled );
		g_draw.get( )->DrawText( "2D Box (NUM_6)", menuOffX, menuOffY + 5 * 12, bools.bBox2D ? enabled : disabled );
		g_draw.get( )->DrawText( "2D StatusBars (NUM_7)", menuOffX, menuOffY + 6 * 12, bools.bStatus2D ? enabled : disabled );
		g_draw.get( )->DrawText( "Status Text (NUM_8)", menuOffX, menuOffY + 7 * 12, bools.bStatusText ? enabled : disabled );
		g_draw.get( )->DrawText( "3D Box (NUM_9)", menuOffX, menuOffY + 8 * 12, bools.bBox3D ? enabled : disabled );
		g_draw.get( )->DrawText( "Velocity ESP(F1)", menuOffX, menuOffY + 9 * 12, bools.bVelEsp ? enabled : disabled );
		g_draw.get( )->DrawText( "HeadLine ESP (F3)", menuOffX, menuOffY + 10 * 12, bools.bHeadlineEsp ? enabled : disabled );
		g_draw.get( )->DrawText( "Recoil Crosshair (F4)", menuOffX, menuOffY + 11 * 12, bools.bRcsCrosshair ? enabled : disabled );

		g_draw.get( )->DrawText( "Hide Menu (INS)", menuOffX, menuOffY + 12 * 12, Colour::text );
	}
}