#pragma once

#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <Psapi.h>

class SigScanner
{
private:

	HMODULE hModule{};
	intptr_t moduleBaseAddress{};
	intptr_t moduleLength{};
	intptr_t m_address{};

public:

	SigScanner( ) = default;

	void MsgBoxAddy( uintptr_t addy )
	{
		char szBuffer[1024];
		sprintf_s( szBuffer, "Addy: %02x", addy );
		MessageBox( NULL, (wchar_t*)szBuffer, L"Title", MB_OK );
	}

	void GetModuleInfo( const wchar_t* szModule )
	{
		hModule = GetModuleHandle( szModule );

		if ( hModule == nullptr )
		{
			std::cout << "Module not found.\n";
			return;
		}

		MODULEINFO modInfo{ 0 };

		BOOL infoReturn{ GetModuleInformation( GetCurrentProcess( ), hModule, &modInfo, sizeof( modInfo ) ) };
		if ( infoReturn == FALSE )
		{
			std::cout << "GetModuleInformation failed. GetLastError = " << GetLastError( ) << '\n';
			system( "pause" );
		}

		moduleBaseAddress = (intptr_t)modInfo.lpBaseOfDll;
		moduleLength = (intptr_t)modInfo.SizeOfImage;

		MEMORY_BASIC_INFORMATION mbi{};

		VirtualQuery( (LPCVOID)moduleBaseAddress, &mbi, sizeof( mbi ) );
		if (  mbi.State != MEM_COMMIT )
		{
			std::cout << "Base Address of the target process memory not found.\n";
		}
	}

	void WriteToMemory( uintptr_t addressToWrite, const char* valueToWrite )
	{
		std::size_t byteNum{ sizeof( valueToWrite ) };
		unsigned long oldProtection{};

		try
		{
			VirtualProtect( (LPVOID)addressToWrite, byteNum, PAGE_EXECUTE_READWRITE, &oldProtection );
			memcpy( (LPVOID)addressToWrite, valueToWrite, byteNum );
			VirtualProtect( (LPVOID)addressToWrite, byteNum, oldProtection, &oldProtection );
		}
		catch ( int error )
		{
			std::cout << "Error in writing to memory found. GetLastError = " << GetLastError( ) << '\n';
		}
	}

	SigScanner& FindPattern( const char* aobPattern, const char* szMask )
	{
		DWORD patternLength = (DWORD)strlen( szMask );
		for ( DWORD i = 0; i < moduleLength - patternLength; ++i )
		{

			bool found = true;
			for ( DWORD j = 0; j < patternLength; ++j )
			{
				found &= (szMask[j] == '?') || (aobPattern[j] == *(char*)(moduleBaseAddress + i + j));
			}
			//found = true, our entire pattern was found
			// return the memory address so we acn write it
			if ( found )
			{
				m_address = moduleBaseAddress + i;
				break; // break out of the main outer loop if pattern is found VIMP
			}
			else
			{
				//address cant be found , pattern may be wrong
				m_address = NULL;// else print 

			}
		}
		return *this;
	}

	SigScanner& operator()( const wchar_t* moduleName, const char* aobPattern, const char* szMask )
	{
		GetModuleInfo( moduleName );
		return { FindPattern( aobPattern, szMask ) };
	}

	SigScanner& add( intptr_t bytesMore )
	{
		m_address += bytesMore;
		return *this;
	}

	SigScanner& subtract( intptr_t bytesLess )
	{
		m_address -= bytesLess;
		return *this;
	}

	intptr_t getAddress( )
	{
		return m_address;
	}

	intptr_t getOffset(int diff_btw_firstInsByte_firstAddrByte )
	{
		intptr_t offsetAddr = *(intptr_t*)(m_address + diff_btw_firstInsByte_firstAddrByte);
		return offsetAddr;
	}

	intptr_t getOffset2( int whole_inst_size, int diff_btw_firstInsByte_firstAddrByte )
	{
		intptr_t rip{ m_address + whole_inst_size }; // address of next instruction to execute
		intptr_t offsetAddr = rip + *(intptr_t*)(m_address + diff_btw_firstInsByte_firstAddrByte);
		return offsetAddr;
	}
};