#include "ProgramLogic.h"

DWORD WINAPI myThreadProc( HMODULE hInstDLL )
{
	AllocConsole( ); // To allocate console for logging
	FILE* f;
	freopen_s( &f, "CONOUT$", "w", stdout );
	std::cout << "Yo! Hitbokx here.\n";

	Run( );

	if ( f )
		fclose( f );
	FreeConsole( );
	FreeLibraryAndExitThread( hInstDLL, 0 );//to call DLL_PROCESS_DETACH and resource deallocation
	return 0;
}

BOOL WINAPI DllMain( HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved )
{
	switch ( fdwReason )
	{
		case DLL_PROCESS_ATTACH:

			::DisableThreadLibraryCalls( hinstDLL );
			CloseHandle( CreateThread( nullptr, 0, LPTHREAD_START_ROUTINE( myThreadProc ), hinstDLL, 0, nullptr ) );
			break;

		case DLL_PROCESS_DETACH:
			//perform any necesary clean-up
			break;

	}
	return TRUE; //Succesful DLL_PROCESS_ATTACH
}
