#pragma once
#include "Classes.h"
#include "Vector.h"
#include "Structs.h"
#include "Include.h"

#define PI 3.14159265358f

class Player :public PlayerEnt
{
public:

	Vector3* GetBonePos( int boneID )
	{
		static Vector3 bonePos{};

		auto boneArrayAccess{ this->pBoneMatrix };

		bonePos.x = (*boneArrayAccess)[35].matrix[3];
		bonePos.y = (*boneArrayAccess)[35].matrix[7];
		bonePos.z = (*boneArrayAccess)[35].matrix[11];

		return &bonePos;
	}
};

class LocalPlayer :public PlayerEnt
{
public:

	void aimAt( Vector3* target )
	{
		static Vector3* viewAngles{ (Vector3*)(modBase.engine + offs.ViewAnglesW) };

		Vector3 origin{ this->playerCoordinates };
		Vector3 viewOffset{ this->viewOffset };

		Vector3 pos{ origin + viewOffset };

		Vector3* myPos{ &pos };

		Vector3 deltaVec{ Vector3( target->x - myPos->x, target->y - myPos->y, target->z - myPos->z ) };

		float deltaVecLength{ sqrt( deltaVec.x * deltaVec.x + deltaVec.y * deltaVec.y + deltaVec.z * deltaVec.z ) };

		float pitch{ -(asin( deltaVec.z / deltaVecLength ) * (180 / PI)) };
		float yaw{ atan2( deltaVec.y, deltaVec.x ) * (180 / PI) };

		if ( pitch >= -89 && pitch <= 89 && yaw >= -180 && yaw <= 180 )
		{
			viewAngles->x = pitch;
			viewAngles->y = yaw;
		}
	}

	float getDistance( Vector3 other )
	{
		Vector3 myPos{ this->playerCoordinates };
		Vector3 delta{ Vector3( other.x - myPos.x, other.y - myPos.y, other.z - myPos.z ) };

		return sqrt( delta.x * delta.x + delta.y * delta.y + delta.z * delta.z );
	}
};

Player* getClosestEnemy( LocalPlayer* pLocalPlayer, EntityList* pEntList, int numPlayers )
{
	float closestDistance{ 1000000 };
	int closestDistanceIndex{ -1 };

	for ( int i{ 1 }; i < numPlayers; ++i )
	{
		Player* currPlayer{ (Player*)(pEntList->EntList[i].m_pEntity) };

		if ( (!currPlayer) || (!(*(uintptr_t*)currPlayer)) || ((uintptr_t)currPlayer == (uintptr_t)pLocalPlayer)) 
			continue;

		if ( currPlayer->bDormant )
			continue;

		if ( currPlayer->health < 1 || pLocalPlayer->health < 1 )
			continue;

		if ( currPlayer->team == pLocalPlayer->team )
			continue;

		float currDistance{ pLocalPlayer->getDistance( currPlayer->playerCoordinates ) };

		if ( currDistance < closestDistance )
		{
			closestDistance = currDistance;
			closestDistanceIndex = i;
		}
	}

	if ( closestDistanceIndex == -1 )
		return NULL;
	else
		return (Player*)(pEntList->EntList[closestDistanceIndex].m_pEntity);
}

void Aimbot( PlayerEnt* pLocalPlayer, EntityList* pEntList, int numPlayers )
{
	Player* closestEnemy{ getClosestEnemy( (LocalPlayer*)pLocalPlayer ,pEntList, numPlayers ) };

	if ( closestEnemy )
	{
		Vector3* bonePos{ closestEnemy->GetBonePos( 35 ) };
		((LocalPlayer*)pLocalPlayer)->aimAt( bonePos );
	}
}