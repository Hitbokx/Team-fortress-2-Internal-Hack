#pragma once
#include "Include.h"
#include "Structs.h"

typedef HRESULT( APIENTRY* tEndScene )(LPDIRECT3DDEVICE9 pDevice);

inline BOOL CALLBACK enumWind( HWND handle, LPARAM lp )
{
	DWORD procId;
	GetWindowThreadProcessId( handle, &procId );

	if ( GetCurrentProcessId( ) != procId )
		return TRUE;

	directx.window.hWnd = handle;

	return FALSE;
}

inline HWND GetProcessWindow( )
{
	directx.window.hWnd = NULL;

	EnumWindows( enumWind, NULL );

	RECT rect;

	if ( directx.window.hWnd != nullptr)
	{
		if ( GetWindowRect( directx.window.hWnd, &rect ) )
		{
			directx.window.windowWidth = rect.right - rect.left;
			directx.window.windowHeight = rect.bottom - rect.top;
		}
	}

	if ( directx.window.windowWidth < 848 && directx.window.windowHeight < 480 )
	{
		directx.window.windowWidth += 171;
		directx.window.windowHeight += 138;
	}

	return directx.window.hWnd;
}

inline bool GetD3D9Device( void** pTable, size_t size )
{
	if ( !pTable )
		return false;

	IDirect3D9* pD3D{ Direct3DCreate9( D3D_SDK_VERSION ) };

	if ( !pD3D )
		return false;

	IDirect3DDevice9* pDummyDevice{ nullptr };

	D3DPRESENT_PARAMETERS d3dpp{};
	d3dpp.Windowed = false;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = GetProcessWindow( );

	HRESULT dummyDevCreated{ pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDummyDevice ) };

	if ( dummyDevCreated != S_OK )
	{
		d3dpp.Windowed = !d3dpp.Windowed;

		HRESULT dummyDevCreated{ pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDummyDevice ) };

		if ( dummyDevCreated != S_OK )
		{
			pD3D->Release( );
			return false;
		}
	}

	memcpy( pTable, *(void***)pDummyDevice, size );

	pDummyDevice->Release( );
	pD3D->Release( );

	return true;
}