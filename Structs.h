#pragma once
#include <Windows.h>
#include <bitset>
#include "FindSig.h"
#include "Include.h"

class PlayerEnt;
class EntityList;

struct offsets_t
{
	uintptr_t entList{ 0xBDD998 };
	uintptr_t entList2{ 0xc56474 };
	uintptr_t localPlayer{ 0xC484F0 };
	uintptr_t flags{ 0x37C };
	uintptr_t fJump{ 0xC8F7C0 };
	uintptr_t fAttack{ 0xC8F7CC };
	uintptr_t crossHairId{ 0x1884 };
	uintptr_t numPlayers{ 0x5DBE44 };
	uintptr_t dwGlowObjectManager{ 0xBE0890 };
	uintptr_t clientState{ 0x465a58 };
	uintptr_t ViewAnglesW{ 0x46a5dc };
	uintptr_t MaxClients{ 0x465d0c };
	uintptr_t dwViewMatrix{ 0x59e9c8 };
};

struct ModuleBases
{
	uintptr_t client{ (uintptr_t)GetModuleHandle( L"client.dll" ) };
	uintptr_t engine{ (uintptr_t)GetModuleHandle( L"engine.dll" ) };
};

struct bools_t
{
	bool bHop{ false };
	bool bTriggerBot{ false };
	bool bShotNow{ true };
	bool bGlowHack{ false };
	bool bAimbot{ false };

	bool bShowMenu{ false };
	bool bShowTeamates{ true };
	bool bSnapLines{ false };
	bool bBox2D{ false };
	bool bStatus2D{ false };
	bool bStatusText{ false };
	bool bBox3D{ false };
	bool bVelEsp{ false };
	bool bHeadlineEsp{ false };
	bool bRcsCrosshair{ false };
};

struct values_t
{
	int bHopVal{ 6 };
	int shoot{ 5 };
	int dontShoot{ 4 };
};

struct FLAG_t
{
	const unsigned int onGround { 0b0000'0001 };
	const std::bitset<8> ducking  { 0b0000'0010 };
	const std::bitset<8> waterJump{ 0b0000'0100 };
	const std::bitset<8> onTrain  { 0b0000'1000 };
	const std::bitset<8> inRain   { 0b0001'0000 };
	const std::bitset<8> frozen   { 0b0010'0000 };
	const std::bitset<8> atControls{ 0b0100'0000 };
	const std::bitset<8> client    { 0b1000'0000 };
	const std::bitset<12> fly      { 0b0100'0000'0000 }; // 1 << 10
	const std::bitset<12> swim     { 0b1000'0000'0000 }; // 1 << 11
};

struct ForceMask_t
{
	const unsigned int jump{ 0b0000'0001 };
	const unsigned int attack{ 0b0000'0001 };
};

struct Vector3Colour
{
	float red{};
	float green{};
	float blue{};
};

namespace Colour
{
	D3DCOLOR health{ D3DCOLOR_ARGB( 255, 46, 139, 87 ) };
	D3DCOLOR crosshair = { D3DCOLOR_ARGB( 255, 255, 255, 255 ) };
	D3DCOLOR text{ D3DCOLOR_ARGB( 255, 255, 255, 255 ) };

	namespace Ally
	{
		D3DCOLOR esp{ D3DCOLOR_ARGB( 255, 0, 255, 0 ) };
		D3DCOLOR snapline{ D3DCOLOR_ARGB( 255, 0, 255, 0 ) };
		D3DCOLOR velocity{ D3DCOLOR_ARGB( 255, 0, 0, 255 ) };
		D3DCOLOR headline{ D3DCOLOR_ARGB( 255, 0, 0, 255 ) };
	}

	namespace Enemy
	{
		D3DCOLOR esp{ D3DCOLOR_ARGB( 255, 255, 0, 0 ) };
		D3DCOLOR snapline{ D3DCOLOR_ARGB( 255, 255, 0, 0 ) };
		D3DCOLOR velocity{ D3DCOLOR_ARGB( 255, 0, 255, 255 ) };
		D3DCOLOR headline{ D3DCOLOR_ARGB( 255, 0, 255, 255 ) };
	}
}

namespace Buttons
{
	DWORD bHop{ VK_NUMPAD0 };
	DWORD triggerBotBtn{ VK_NUMPAD1 };
	DWORD glowBtn{ VK_NUMPAD2 };
	DWORD aimBotBtn{ VK_NUMPAD3 };

	DWORD showTeamatesBtn{ VK_NUMPAD4 };
	DWORD snapLinesBtn{ VK_NUMPAD5 };
	DWORD box2DBtn{ VK_NUMPAD6 };
	DWORD status2DBtn{ VK_NUMPAD7 };
	DWORD statusTextBtn{ VK_NUMPAD8 };
	DWORD box3DBtn{ VK_NUMPAD9 };
	DWORD velEspBtn{ VK_F1 };
	DWORD headlineEspBtn{ VK_F3 };
	DWORD rcsCrosshairBtn{ VK_F4 };

	DWORD showMenuBtn{ VK_INSERT };
}

inline offsets_t offs{};
inline bools_t bools{};
inline values_t val{};
inline FLAG_t FLAG{};
inline ForceMask_t force{};
inline ModuleBases modBase{};

struct Hack
{
	PlayerEnt* pLocalPlayer{ nullptr };
	EntityList* pEntList{ nullptr };
	int numPlayers{ 0 };
	float viewMatrix[16]{};

	void Init( )
	{
		PlayerEnt* pLocalPlayer{ *(PlayerEnt**)(modBase.client + offs.localPlayer) };
		EntityList* pEntList{ *(EntityList**)(modBase.client + offs.entList) };
		int numPlayers{ *(int*)(modBase.engine + offs.numPlayers) };
	}

	void Update( )
	{
		pLocalPlayer = *(PlayerEnt**)(modBase.client + offs.localPlayer);
		pEntList = *(EntityList**)(modBase.client + offs.entList);
		numPlayers = *(int*)(modBase.engine + offs.numPlayers);
		memcpy( &viewMatrix, (PBYTE*)(modBase.engine + offs.dwViewMatrix), sizeof( viewMatrix ) );
	}
};

inline Hack hack{};