#pragma once
#include "Include.h"
#include "DirectXStuff.h"
#include "Structs.h"

#define TORAD(x) ((x)*0.01745329252f) 

class Draw
{
public:
	ID3DXLine* LineL{ nullptr };
	ID3DXFont* FontF{ nullptr };

public:
	Draw( )
	{
		D3DXCreateLine( g_dxStuff.get( )->m_directX.pDevice, &LineL );

		D3DXCreateFont( g_dxStuff.get( )->m_directX.pDevice, 14, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Aerial", &FontF );
	}

	~Draw( )
	{
		g_hook.unHook<7>( (BYTE*)g_dxStuff.get( )->m_directX.d3d9Device[42] );

		if ( FontF )
			this->FontF->Release( );

		if ( LineL )
			this->LineL->Release( );
	}

	void DrawFilledRect( int x, int y, int width, int height, D3DCOLOR color )
	{
		D3DRECT rect{ x, y, x + width, y + height };
		g_dxStuff.get( )->m_directX.pDevice->Clear( 1, &rect, D3DCLEAR_TARGET, color, 0, 0 );
	}

	void DrawLine( int x1, int y1, int x2, int y2, int thickness, D3DCOLOR colour )
	{
		if ( !LineL )
			D3DXCreateLine( g_dxStuff.get( )->m_directX.pDevice, &LineL );

		if ( LineL )
		{
			D3DXVECTOR2 Line[2];
			Line[0] = D3DXVECTOR2( x1, y1 );
			Line[1] = D3DXVECTOR2( x2, y2 );
			LineL->SetWidth( thickness );
			LineL->Draw( Line, 2, colour );
		}
	}

	void DrawLine( Vector2 src, Vector2 dst, int thickness, D3DCOLOR colour )
	{
		DrawLine( src.x, src.y, dst.x, dst.y, thickness, colour );
	}

	void DrawText( const char* text, float x, float y, D3DCOLOR colour )
	{
		RECT rect;

		if ( !FontF )
			D3DXCreateFont( g_dxStuff.get( )->m_directX.pDevice, 14, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Aerial", &FontF );

		if ( FontF )
		{
			SetRect( &rect, x + 1, y + 1, x + 1, y + 1 );
			FontF->DrawTextA( NULL, text, -1, &rect, DT_CENTER | DT_NOCLIP, D3DCOLOR_ARGB( 255, 0, 0, 0 ) );

			SetRect( &rect, x, y, x, y );
			FontF->DrawTextA( NULL, text, -1, &rect, DT_CENTER | DT_NOCLIP, colour );
		}
	}
};

extern auto g_draw{ std::make_unique<Draw>( ) };