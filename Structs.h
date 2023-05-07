#pragma once
#include <Windows.h>
#include <bitset>

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
};

struct ModuleBases
{
	uintptr_t cModuleBase{ (uintptr_t)GetModuleHandle( L"client.dll" ) };
	uintptr_t eModuleBase{ (uintptr_t)GetModuleHandle( L"engine.dll" ) };
};

struct bools_t
{
	bool bHop{ false };
	bool bTriggerBot{ false };
	bool bShotNow{ true };
	bool bGlowHack{ false };
	bool bRecoil{ false };
	bool bAimbot{ false };
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

inline offsets_t offs{};
inline bools_t bools{};
inline values_t val{};
inline FLAG_t FLAG{};
inline ForceMask_t force{};