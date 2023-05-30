#pragma once
#include "TraceLineDefines.h"

bool isVisible( PlayerEnt* ent )
{
	Vector3 rayStart{ ((LocalPlayer*)hack.pLocalPlayer)->getEyePosition( ) };

	Vector3 rayEnd{ ((Player*)ent)->GetHeadBone( ) };
	CGameTrace trace{};
	Ray_t ray{};
	CTraceFilter traceFilter{};

	traceFilter.pSkip = hack.pLocalPlayer;
	ray.Init( rayStart, rayEnd );

	void** pECX = (void**)(modBase.client + offs.dwIEngineTrace);

	hack.TraceRay( *pECX, ray, MASK_NPCWORLDSTATIC | CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_MONSTER | CONTENTS_WINDOW | CONTENTS_DEBRIS | CONTENTS_HITBOX, &traceFilter, &trace );

	return (trace.hit_entity == ent);
}