#pragma once
#include <vector>
#include "structs.h"
ModuleBases mBase{};

using RegisterGlowObject_t = int( __thiscall* )(void*, PlayerEnt*, const Vector3Colour&, float, bool, bool, int);

RegisterGlowObject_t RegisterGlowObject{ (RegisterGlowObject_t)(mBase.cModuleBase + 0x198CE0) };

void Glow(uintptr_t cModuleBase, EntityList* pEntList, PlayerEnt* pLocalPlayer )
{
	//Vector3 tColour{ 0,0,2 };
	//Vector3 EColour{ 2,0,0 };
	uintptr_t glowObject{ (uintptr_t)(cModuleBase + offs.dwGlowObjectManager) };
	std::vector<int> glowIndex{};
	int i{ 0 };

	for ( const auto& ent : pEntList->EntList )
	{
		if ( ent.entPtr )
		{
			if ( ent.entPtr->team == pLocalPlayer->team )
			{
				RegisterGlowObject( (void*)glowObject, ent.entPtr, { 0,0,2 }, 1.7, true, false, -1 );
			}
			else
			{
				RegisterGlowObject( (void*)glowObject, ent.entPtr, { 2,0,0 }, 1.7, true, false, -1 );
			}
			++i;
		}
	}
}