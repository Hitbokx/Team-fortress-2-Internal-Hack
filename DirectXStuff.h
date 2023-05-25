#pragma once
#include "HookingClass.h"
#include "Include.h"

using tEndScene = HRESULT( APIENTRY* )(LPDIRECT3DDEVICE9 pDevice);
tEndScene g_oEndScene{ nullptr };

BOOL CALLBACK EnumWindowsProc( HWND handle, LPARAM lp );
extern void APIENTRY HkEndScene( LPDIRECT3DDEVICE9 o_pDevice );

struct Window
{
	int windowHeight{ 0 };
	int windowWidth{ 0 };

	HWND hWnd{ nullptr };
};

struct Directx
{
	void* d3d9Device[119];
	void* oEndScene{ nullptr };
	LPDIRECT3DDEVICE9 pDevice{ nullptr };

	Window window;
};

class DxStuff
{
public:

	Directx m_directX{};
	Window m_window{};

public:
	~DxStuff( )
	{
		void* oEndScene{ nullptr };
		LPDIRECT3DDEVICE9 pDevice{ nullptr };
	}

	HWND GetProcessWindow( )
	{
		m_window.hWnd = NULL;

		EnumWindows( EnumWindowsProc, NULL );

		RECT rect;

		if ( m_window.hWnd )
		{
			if ( GetWindowRect( m_window.hWnd, &rect ) )
			{
				m_window.windowWidth = rect.right - rect.left;
				m_window.windowHeight = rect.bottom - rect.top;
			}

			m_window.windowWidth += 171;
			m_window.windowHeight += 138;

			return m_window.hWnd;
		}

		else return nullptr;
	}

	bool GetD3D9Device( void** pTable, size_t size )
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

	void hookEndScene( )
	{
		if ( GetD3D9Device( m_directX.d3d9Device, sizeof( m_directX.d3d9Device ) ) )
		{
			g_oEndScene = (tEndScene)g_hook.TrampHook32<7>( (BYTE*)m_directX.d3d9Device[42], (BYTE*)HkEndScene );
		}
	}
};

extern auto g_dxStuff{ std::make_unique<DxStuff>( ) };

BOOL CALLBACK EnumWindowsProc( HWND handle, LPARAM lp )
{
	DWORD procId;
	GetWindowThreadProcessId( handle, &procId );

	if ( GetCurrentProcessId( ) != procId )
		return TRUE;

	g_dxStuff.get( )->m_window.hWnd = handle;

	return FALSE;
}