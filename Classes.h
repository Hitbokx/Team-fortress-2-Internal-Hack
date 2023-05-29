#pragma once

#include <iostream>
#include <Windows.h>
#include "Vector.h"
#include "structs.h"

#define NUM_ENT_ENTRY_BITS		(MAX_EDICT_BITS + 1)
#define NUM_ENT_ENTRIES			(1 << NUM_ENT_ENTRY_BITS)
#define ENT_ENTRY_MASK			(NUM_ENT_ENTRIES - 1)
#define INVALID_EHANDLE_INDEX	0xFFFFFFFF
#define NUM_SERIAL_NUM_BITS		(32 - NUM_ENT_ENTRY_BITS)

#define	MAX_EDICT_BITS				11			
#define	MAX_EDICTS					(1<<MAX_EDICT_BITS)

class CBaseHandle
{
public:
	friend class EntityList;

public:

	int GetEntryIndex( ) const;

	int GetSerialNumber( ) const;

protected:

	unsigned long	m_Index;
};

class PlayerEnt
{
public:
	char pad_0000[32]; //0x0000
	Vector3 vecAngles; //0x0020
	char pad_002C[121]; //0x002C
	int8_t lifeState; //0x00A5
	char pad_00A6[2]; //0x00A6
	int32_t health; //0x00A8
	char pad_00AC[4]; //0x00AC
	int32_t team; //0x00B0
	char pad_00B4[72]; //0x00B4
	Vector3 viewOffset; //0x00FC
	char pad_0108[24]; //0x0108
	Vector3 velocity; //0x0120
	char pad_012C[126]; //0x012C
	bool bDormant; //0x01AA
	char pad_01AB[225]; //0x01AB
	Vector3 playerCoordinates; //0x028C
	Vector3 viewAngles; //0x0298
	char pad_02A4[208]; //0x02A4
	Vector3 playerCoordinates2; //0x0374
	char pad_0380[12]; //0x0380
	uint32_t flag; //0x038C
	char pad_0390[544]; //0x0390
	Matrix3x4( *pBoneMatrix )[128]; //0x05B0
	char pad_05B4[96]; //0x05B4
	int32_t flag2; //0x0614
	char pad_0618[760]; //0x0618
	Vector3 gunCrossHair; //0x0910
	char pad_091C[864]; //0x091C
	int32_t primaryAmmoMag; //0x0C7C
	int32_t secondaryAmmoMag; //0x0C80
	char pad_0C84[40]; //0x0C84
	Vector3 N00000B51; //0x0CAC
	Vector3 N00000B52; //0x0CB8
	char pad_0CC4[248]; //0x0CC4
	bool specGlowEnabled; //0x0DBC
	bool glowEnabled; //0x0DBD
	bool boldGlowEnabled; //0x0DBE
	char pad_0DBF[1]; //0x0DBF
	int32_t glowIndex; //0x0DC0
	char pad_0DC4[180]; //0x0DC4
	uint32_t commandFlags; //0x0E78
	char pad_0E7C[732]; //0x0E7C
	float onTarget; //0x1158
	char pad_115C[24]; //0x115C
	uint32_t commandFlag2; //0x1174
	char pad_1178[8]; //0x1178
	uint32_t commandFlags3; //0x1180
	char pad_1184[304]; //0x1184
	int32_t primaryAmmo; //0x12B4
	int32_t secondaryAmmo; //0x12B8
	char pad_12BC[156]; //0x12BC
	int32_t commandFlags4; //0x1358
	char pad_135C[1320]; //0x135C
	int32_t crossHairId; //0x1884
	char pad_1888[14316]; //0x1888
}; //Size: 0x5074

class CEntInfo
{
public:
	class PlayerEnt* m_pEntity; //0x0000
	int32_t m_SerialNumber; //0x0004
	class CEntInfo* previous; //0x0008
	class CEntInfo* next; //0x000C
}; //Size: 0x0010

CEntInfo m_EntPtrArray[NUM_ENT_ENTRIES];

class Entity
{
public:
	char pad_0000[168]; //0x0000
	int32_t health; //0x00A8
}; //Size: 0x00AC

class EntityList
{
public:
	char pad_0000[4]; //0x0000
	class CEntInfo world; //0x0004
	class CEntInfo EntList[23]; //0x0014

}; //Size: 0x01C4

inline int CBaseHandle::GetEntryIndex( ) const
{
	return m_Index & ENT_ENTRY_MASK;
}

inline int CBaseHandle::GetSerialNumber( ) const
{
	return m_Index >> NUM_ENT_ENTRY_BITS;
}

struct GlowObjectDefinition_t
{
	CBaseHandle m_hEntity;
	Vector3 m_vGlowColor;
	float m_flGlowAlpha;
	bool m_bRenderWhenOccluded;
	bool m_bRenderWhenUnoccluded;
	int m_nSplitScreenSlot;
	int m_nNextFreeSlot;
};

class CGlowObjectManager
{
public:
	CUtlVector<GlowObjectDefinition_t> m_GlowObjectDefinitions;
	int m_nFirstFreeSlot;
};

#define PI 3.14159265358f

class Player :public PlayerEnt
{
public:

	Vector3 GetBonePos( int boneID )
	{
		Vector3 bonePos{};

		auto boneArrayAccess{ this->pBoneMatrix };

		bonePos.x = (*boneArrayAccess)[boneID].matrix[3];
		bonePos.y = (*boneArrayAccess)[boneID].matrix[7];
		bonePos.z = (*boneArrayAccess)[boneID].matrix[11];

		return bonePos;
	}

	Vector3 GetHeadBone( )
	{
		Vector3 headBonePos{ this->GetBonePos( 0 ) };
		int j{ 0 };
		for ( int i{ 0 }; i < 69; ++i )
		{
			Vector3 bonePos = this->GetBonePos( i );

			if ( bonePos.x == 0 || bonePos.y == 0 || bonePos.z == 0 )
				break;

			if ( bonePos.z > headBonePos.z )
			{
				headBonePos = bonePos;
				j = i;
			}
		}

		if ( j == 27 )
			headBonePos = this->GetBonePos( 6 );

		return headBonePos;

	}
};

class LocalPlayer :public PlayerEnt
{
public:

	void aimAt( Vector3 target )
	{
		static Vector3* viewAngles{ (Vector3*)(modBase.engine + offs.ViewAnglesW) };

		Vector3 origin{ this->playerCoordinates };
		Vector3 viewOffset{ this->viewOffset };

		Vector3 pos{ origin + viewOffset };

		Vector3* myPos{ &pos };

		Vector3 deltaVec{ Vector3( target.x - myPos->x, target.y - myPos->y, target.z - myPos->z ) };

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

	Vector3 getEyePosition( )
	{
		return ( Vector3 )( hack.pLocalPlayer->playerCoordinates + hack.pLocalPlayer->viewOffset );
	}
};