#pragma once

#include <iostream>
#include <Windows.h>
#include "structs.h"

class PlayerEnt
{
public:
	char pad_0000[32]; //0x0000
	Vector3 vecAngles; //0x0020
	char pad_002C[124]; //0x002C
	int32_t health; //0x00A8
	char pad_00AC[4]; //0x00AC
	int32_t team; //0x00B0
	char pad_00B4[72]; //0x00B4
	Vector3 viewOffset; //0x00FC
	char pad_0108[24]; //0x0108
	Vector3 velocity; //0x0120
	char pad_012C[126]; //0x012C
	bool bDormant; //0x01AA
	char pad_01AB[237]; //0x01AB
	Vector3 viewAngles; //0x0298
	char pad_02A4[192]; //0x02A4
	Vector3 playerCoordinates; //0x0364
	char pad_0370[12]; //0x0370
	unsigned int flag; //0x037C
	char pad_0380[660]; //0x0380
	uint32_t flag2; //0x0614
	char pad_0618[728]; //0x0618
	Vector3 gunCrossHair; //0x08F0
	char pad_08FC[896]; //0x08FC
	int32_t primaryAmmoMag; //0x0C7C
	int32_t secondaryAmmoMag; //0x0C80
	char pad_0C84[40]; //0x0C84
	Vector3 N00000B51; //0x0CAC
	Vector3 N00000B52; //0x0CB8
	char pad_0CC4[436]; //0x0CC4
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

class ClientInfo
{
public:
	class PlayerEnt* entPtr; //0x0000
	int32_t serialNum; //0x0004
	class ClientInfo* previous; //0x0008
	class ClientInfo* next; //0x000C
}; //Size: 0x0010

class EntityList
{
public:
	class ClientInfo world; //0x0004
	class ClientInfo EntList[23]; //0x0014
	char pad_0184[64]; //0x0184

	virtual void Function0( );
	virtual void Function1( );
	virtual void Function2( );
	virtual void Function3( );
	virtual void Function4( );
	virtual void Function5( );
	virtual void Function6( );
	virtual void Function7( );
	virtual void Function8( );
	virtual void Function9( );
	virtual void Function10( );
	virtual void Function11( );
	virtual void Function12( );
	virtual void Function13( );
	virtual void Function14( );
	virtual void Function15( );
	virtual void Function16( );
	virtual void Function17( );
	virtual void Function18( );
	virtual void Function19( );
	virtual void Function20( );
	virtual void Function21( );
	virtual void Function22( );
	virtual void Function23( );
	virtual void Function24( );
	virtual void Function25( );
	virtual void Function26( );
	virtual void Function27( );
	virtual void Function28( );
	virtual void Function29( );
	virtual void Function30( );
	virtual void Function31( );
	virtual void Function32( );
	virtual void Function33( );
	virtual void Function34( );
	virtual void Function35( );
	virtual void Function36( );
	virtual void Function37( );
	virtual void Function38( );
	virtual void Function39( );
	virtual void Function40( );
	virtual void Function41( );
	virtual void Function42( );
	virtual void Function43( );
	virtual void Function44( );
	virtual void Function45( );
	virtual void Function46( );
	virtual void Function47( );
	virtual void Function48( );
	virtual void Function49( );
	virtual void Function50( );
	virtual void Function51( );
	virtual void Function52( );
	virtual void Function53( );
	virtual void Function54( );
	virtual void Function55( );
	virtual void Function56( );
	virtual void Function57( );
	virtual void Function58( );
	virtual void Function59( );
	virtual void Function60( );
	virtual void Function61( );
	virtual void Function62( );
	virtual void Function63( );
	virtual void Function64( );
	virtual void Function65( );
	virtual void Function66( );
	virtual void Function67( );
	virtual void Function68( );
	virtual void Function69( );
	virtual void Function70( );
	virtual void Function71( );
	virtual void Function72( );
	virtual void Function73( );
}; //Size: 0x01C4

class Entity
{
public:
	char pad_0000[168]; //0x0000
	int32_t health; //0x00A8
}; //Size: 0x00AC