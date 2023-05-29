#pragma once

#include "Vector.h"
#include "Structs.h"
#include "Classes.h"
#include "TraceLineDefines.h"

#define	CONTENTS_SOLID			0x1		
#define	CONTENTS_WINDOW			0x2		
#define	CONTENTS_GRATE			0x8		
#define CONTENTS_MOVEABLE		0x4000
#define	CONTENTS_MONSTER		0x2000000
#define	CONTENTS_MONSTERCLIP	0x20000
#define	CONTENTS_DEBRIS			0x4000000
#define CONTENTS_HITBOX			0x40000000

#define MASK_NPCWORLDSTATIC	    ( CONTENTS_SOLID | CONTENTS_WINDOW | CONTENTS_MONSTERCLIP | CONTENTS_GRATE )
#define STANDARD_TRACE_MASK     ( MASK_NPCWORLDSTATIC | CONTENTS_MOVEABLE | CONTENTS_MONSTER | CONTENTS_DEBRIS | CONTENTS_HITBOX )
#define   MASK_SHOT                     (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_HITBOX)

#define DISPSURF_FLAG_SURFACE		(1<<0)
#define DISPSURF_FLAG_WALKABLE		(1<<1)
#define DISPSURF_FLAG_BUILDABLE		(1<<2)
#define DISPSURF_FLAG_SURFPROP1		(1<<3)
#define DISPSURF_FLAG_SURFPROP2		(1<<4)

enum TraceType_t
{
	TRACE_EVERYTHING = 0,
	TRACE_WORLD_ONLY,				// NOTE: This does *not* test static props!!!
	TRACE_ENTITIES_ONLY,			// NOTE: This version will *not* test static props
	TRACE_EVERYTHING_FILTER_PROPS,	// NOTE: This version will pass the IHandleEntity for props through the filter, unlike all other filters
};

class ITraceFilter
{
public:
	virtual bool ShouldHitEntity( void* pEntity, int contentsMask ) = 0;
	virtual TraceType_t	GetTraceType( ) const = 0;
};

class CTraceFilter : public ITraceFilter
{
public:
	void* pSkip;

	bool ShouldHitEntity( void* pEntityHandle, int /*contentsMask*/ )
	{
		return !(pEntityHandle == pSkip);
	}
	virtual TraceType_t GetTraceType( ) const
	{
		return TRACE_EVERYTHING;
	}
};

class CTraceFilterEntitiesOnly : public ITraceFilter
{
public:
	virtual TraceType_t	GetTraceType( ) const
	{
		return TRACE_ENTITIES_ONLY;
	}
};

struct Ray_t
{
	VectorAligned  m_Start;	// starting point, centered within the extents
	VectorAligned  m_Delta;	// direction + length of the ray
	VectorAligned  m_StartOffset;	// Add this to m_Start to get the actual ray start
	VectorAligned  m_Extents;	// Describes an axis aligned box extruded along a ray
	bool	m_IsRay;	// are the extents zero?
	bool	m_IsSwept;	// is delta != 0?

	void Init( Vector3 const& start, Vector3 const& end )
	{
		VectorSubtract( end, start, m_Delta );

		m_IsSwept = (m_Delta.LengthSqr( ) != 0);

		VectorClear( m_Extents );
		m_IsRay = true;

		// Offset m_Start to be in the center of the box...
		VectorClear( m_StartOffset );
		VectorCopy( start, m_Start );
	}

	void Init( Vector3 const& start, Vector3 const& end, Vector3 const& mins, Vector3 const& maxs )
	{
		m_Delta = end - start;

		m_IsSwept = (m_Delta.LengthSqr( ) != 0);

		m_Extents = maxs - mins;
		m_Extents *= 0.5f;
		m_IsRay = (m_Extents.LengthSqr( ) < 1e-6);

		// Offset m_Start to be in the center of the box...
		m_StartOffset = mins + maxs;
		m_StartOffset *= 0.5f;
		m_Start = start + m_StartOffset;
		m_StartOffset *= -1.0f;
	}

	// compute inverse delta
	Vector3 InvDelta( ) const
	{
		Vector3 vecInvDelta;
		for ( int iAxis = 0; iAxis < 3; ++iAxis )
		{
			if ( m_Delta[iAxis] != 0.0f )
			{
				vecInvDelta[iAxis] = 1.0f / m_Delta[iAxis];
			}
			else
			{
				vecInvDelta[iAxis] = FLT_MAX;
			}
		}
		return vecInvDelta;
	}
};

struct cplane_t
{
	Vector3 normal;
	float dist;
	uint8_t type;   // for fast side tests
	uint8_t signbits;  // signx + (signy<<1) + (signz<<1)
	uint8_t pad[2];
};

struct csurface_t
{
	const char* name;
	short		surfaceProps;
	unsigned short	flags;
};

class CBaseTrace
{
public:

	// Displacement flags tests.
	bool IsDispSurface( void )				{ return ((dispFlags & DISPSURF_FLAG_SURFACE) != 0); }
	bool IsDispSurfaceWalkable( void )		{ return ((dispFlags & DISPSURF_FLAG_WALKABLE) != 0); }
	bool IsDispSurfaceBuildable( void )		{ return ((dispFlags & DISPSURF_FLAG_BUILDABLE) != 0); }
	bool IsDispSurfaceProp1( void )			{ return ((dispFlags & DISPSURF_FLAG_SURFPROP1) != 0); }
	bool IsDispSurfaceProp2( void )			{ return ((dispFlags & DISPSURF_FLAG_SURFPROP2) != 0); }

public:

	// these members are aligned!!
	Vector3			startpos;				// start position
	Vector3			endpos;					// final position
	cplane_t		plane;					// surface normal at impact

	float			fraction;				// time completed, 1.0 = didn't hit anything

	int				contents;				// contents on other side of surface hit
	unsigned short	dispFlags;				// displacement flags for marking surfaces with data

	bool			allsolid;				// if true, plane is not valid
	bool			startsolid;				// if true, the initial point was in a solid area

	CBaseTrace( ) {}

private:
	// No copy constructors allowed
	CBaseTrace( const CBaseTrace& vOther );
};

class CGameTrace : public CBaseTrace
{
public:
	bool DidHitWorld( ) const;

	bool DidHitNonWorldEntity( ) const;

	int GetEntityIndex( ) const;

	// Returns true if there was any kind of impact at all
	bool DidHit( ) const;

	bool IsVisible( ) const;

public:

	float		fractionleftsolid;		// time we left a solid, only valid if we started in solid
	csurface_t	surface;				// surface hit (impact surface)

	int			hitgroup;				// 0 == generic, non-zero is specific body part
	short		physicsbone;			// physics bone hit by trace in studio

	void* hit_entity;

	int			hitbox;					// box hit by trace in studio

	CGameTrace( ) = default;

private:

	CGameTrace( const CGameTrace& other ) :
		fractionleftsolid( other.fractionleftsolid ),
		surface( other.surface ),
		hitgroup( other.hitgroup ),
		physicsbone( other.physicsbone ),
		hit_entity( other.hit_entity ),
		hitbox( other.hitbox )
	{
		startpos = other.startpos;
		endpos = other.endpos;
		plane = other.plane;
		fraction = other.fraction;
		contents = other.contents;
		dispFlags = other.dispFlags;
		allsolid = other.allsolid;
		startsolid = other.startsolid;
	}

	CGameTrace& operator=( const CGameTrace& other )
	{
		startpos = other.startpos;
		endpos = other.endpos;
		plane = other.plane;
		fraction = other.fraction;
		contents = other.contents;
		dispFlags = other.dispFlags;
		allsolid = other.allsolid;
		startsolid = other.startsolid;
		fractionleftsolid = other.fractionleftsolid;
		surface = other.surface;
		hitgroup = other.hitgroup;
		physicsbone = other.physicsbone;
		hit_entity = other.hit_entity;
		hitbox = other.hitbox;
		return *this;
	}
};

inline bool CGameTrace::DidHit( ) const
{
	return fraction < 1 || allsolid || startsolid;
}

inline bool CGameTrace::IsVisible( ) const
{
	return fraction > 0.97f;
}

class IEngineTrace
{
public:
	virtual int		GetPointContents( const Vector3& vecAbsPosition, void** ppEntity = NULL ) = 0;

	virtual int		GetPointContents_Collideable( void* pCollide, const Vector3& vecAbsPosition ) = 0;

	virtual void	ClipRayToEntity( const Ray_t& ray, unsigned int fMask, void* pEnt, CGameTrace* pTrace ) = 0;

	virtual void	ClipRayToCollideable( const Ray_t& ray, unsigned int fMask, void* pCollide, CGameTrace* pTrace ) = 0;

	virtual void	TraceRay( const Ray_t& ray, unsigned int fMask, ITraceFilter* pTraceFilter, CGameTrace* pTrace ) = 0;
};

typedef void( __thiscall* tTraceRay )(void* thisptr, Ray_t& ray, unsigned int fMask, CTraceFilter* pTraceFilter, CGameTrace* pTrace);