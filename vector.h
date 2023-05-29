#pragma once

#include "Include.h"

template <typename T, typename I = int>
class CUtlMemory
{
public:

	T& operator[]( int i )
	{
		return m_pMemory[i];
	}

	T* m_pMemory;
	int m_nAllocationCount;
	int m_nGrowSize;
};

template <typename T, typename A = CUtlMemory<T>>
class CUtlVector
{
public:

	using CAllocator = A;

	T& operator[]( int i )
	{
		return m_memory[i];
	}

	CAllocator m_memory;
	int m_Size;
	T* m_pElements;
};

struct Vector2
{
	float x{};
	float y{};

	Vector2( )
	{
		x = y = 0;
	}

	Vector2( float x, float y )
	{
		this->x = x;
		this->y = y;
	}

	Vector2( Vector2& rhs )
	{
		this->x = rhs.x;
		this->y = rhs.y;
	}

	Vector2& operator=( const Vector2& rhs )
	{
		this->x = rhs.x;
		this->y = rhs.y;

		return *this;
	}

	~Vector2( ) = default;

	Vector2 operator + ( const Vector2& rhs ) const { return Vector2( x + rhs.x, y + rhs.y ); }
	Vector2 operator - ( const Vector2& rhs ) const { return Vector2( x - rhs.x, y - rhs.y ); }
	Vector2 operator * ( const float& rhs ) const { return Vector2( x * rhs, y * rhs ); }
	Vector2 operator / ( const float& rhs ) const { return Vector2( x / rhs, y / rhs ); }

	Vector2& operator += ( const Vector2& rhs ) { return *this = *this + rhs; }
	Vector2& operator -= ( const Vector2& rhs ) { return *this = *this - rhs; }
	Vector2& operator *= ( const float& rhs ) { return *this = *this * rhs; }
	Vector2& operator /= ( const float& rhs ) { return *this = *this / rhs; }

	float Length( ) const
	{
		return sqrtf( x * x + y * y );
	}

	Vector2 Normalize( ) const
	{
		return *this * (1 / Length( ));
	}

	float Distance( const Vector2& rhs ) const {
		return (*this - rhs).Length( );
	}
};

struct Vector3
{
public:

	float x{};
	float y{};
	float z{};

public:

    Vector3( void )
    {
        Invalidate( );
    }
    Vector3( float X, float Y, float Z )
    {
        x = X;
        y = Y;
        z = Z;
    }
    Vector3( const float* clr )
    {
        x = clr[0];
        y = clr[1];
        z = clr[2];
    }

    void Init( float ix = 0.0f, float iy = 0.0f, float iz = 0.0f )
    {
        x = ix; y = iy; z = iz;
    }
    bool IsValid( ) const
    {
        return std::isfinite( x ) && std::isfinite( y ) && std::isfinite( z );
    }
    void Invalidate( )
    {
        x = y = z = std::numeric_limits<float>::infinity( );
    }

    float& operator[]( int i )
    {
        return ((float*)this)[i];
    }
    float operator[]( int i ) const
    {
        return ((float*)this)[i];
    }

    void Zero( )
    {
        x = y = z = 0.0f;
    }

    bool operator==( const Vector3& src ) const
    {
        return (src.x == x) && (src.y == y) && (src.z == z);
    }
    bool operator!=( const Vector3& src ) const
    {
        return (src.x != x) || (src.y != y) || (src.z != z);
    }

    Vector3& operator+=( const Vector3& v )
    {
        x += v.x; y += v.y; z += v.z;
        return *this;
    }
    Vector3& operator-=( const Vector3& v )
    {
        x -= v.x; y -= v.y; z -= v.z;
        return *this;
    }
    Vector3& operator*=( float fl )
    {
        x *= fl;
        y *= fl;
        z *= fl;
        return *this;
    }
    Vector3& operator*=( const Vector3& v )
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        return *this;
    }
    Vector3& operator/=( const Vector3& v )
    {
        x /= v.x;
        y /= v.y;
        z /= v.z;
        return *this;
    }
    Vector3& operator+=( float fl )
    {
        x += fl;
        y += fl;
        z += fl;
        return *this;
    }
    Vector3& operator/=( float fl )
    {
        x /= fl;
        y /= fl;
        z /= fl;
        return *this;
    }
    Vector3& operator-=( float fl )
    {
        x -= fl;
        y -= fl;
        z -= fl;
        return *this;
    }

    void NormalizeInPlace( )
    {
        *this = Normalized( );
    }

    Vector3 Normalized( ) const
    {
        Vector3 res = *this;
        float l = res.Length( );
        if ( l != 0.0f ) {
            res /= l;
        }
        else {
            res.x = res.y = res.z = 0.0f;
        }
        return res;
    }

    float DistTo( const Vector3& vOther ) const
    {
        Vector3 delta;

        delta.x = x - vOther.x;
        delta.y = y - vOther.y;
        delta.z = z - vOther.z;

        return delta.Length( );
    }

    float DistToSqr( const Vector3& vOther ) const
    {
        Vector3 delta;

        delta.x = x - vOther.x;
        delta.y = y - vOther.y;
        delta.z = z - vOther.z;

        return delta.LengthSqr( );
    }

    float Dot( const Vector3& vOther ) const
    {
        return (x * vOther.x + y * vOther.y + z * vOther.z);
    }
    float Length( ) const
    {
        return sqrt( x * x + y * y + z * z );
    }
    float LengthSqr( void ) const
    {
        return (x * x + y * y + z * z);
    }
    float Length2D( ) const
    {
        return sqrt( x * x + y * y );
    }

    Vector3& operator=( const Vector3& vOther )
    {
        x = vOther.x; y = vOther.y; z = vOther.z;
        return *this;
    }

    Vector3& operator=( Vector3& vOther )
    {
        x = vOther.x; y = vOther.y; z = vOther.z;
        return *this;
    }

    Vector3 operator-( void ) const
    {
        return Vector3( -x, -y, -z );
    }
    Vector3 operator+( const Vector3& v ) const
    {
        return Vector3( x + v.x, y + v.y, z + v.z );
    }
    Vector3 operator-( const Vector3& v ) const
    {
        return Vector3( x - v.x, y - v.y, z - v.z );
    }
    Vector3 operator*( float fl ) const
    {
        return Vector3( x * fl, y * fl, z * fl );
    }
    Vector3 operator*( const Vector3& v ) const
    {
        return Vector3( x * v.x, y * v.y, z * v.z );
    }
    Vector3 operator/( float fl ) const
    {
        return Vector3( x / fl, y / fl, z / fl );
    }
    Vector3 operator/( const Vector3& v ) const
    {
        return Vector3( x / v.x, y / v.y, z / v.z );
    }
	
	Vector3 Normalize( ) const
	{
		return *this * (1 / Length( ));
	}

	float Distance( const Vector3& rhs ) const {
		return (*this - rhs).Length( );
	}
};

void VectorClear( Vector3& a )
{
	a.x = a.y = a.z = 0.0f;
}

void VectorSubtract( const Vector3& a, const Vector3& b, Vector3& c )
{
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
}

void VectorCopy( const Vector3& src, Vector3& dst )
{
	dst.x = src.x;
	dst.y = src.y;
	dst.z = src.z;
}

#define DECL_ALIGN(x) __declspec(align(x))
#define ALIGN16 DECL_ALIGN(16)
#define ALIGN16_POST DECL_ALIGN(16)

class ALIGN16 VectorAligned : public Vector3
{
public:
	inline VectorAligned( void ) {};
	inline VectorAligned( float X, float Y, float Z )
	{
		Init( X, Y, Z );
	}

	explicit VectorAligned( const Vector3& vOther )
	{
		Init( vOther.x, vOther.y, vOther.z );
	}

	VectorAligned& operator=( const Vector3& vOther )
	{
		Init( vOther.x, vOther.y, vOther.z );
		return *this;
	}

	float w;	// this space is used anyway
} ALIGN16_POST;

struct Vector4
{
	float x{};
	float y{};
	float z{};
	float w{};

	Vector4( )
	{
		x = y = z = w = 0;
	}

	Vector4( float x, float y, float z, float w )
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	Vector4( Vector4& rhs )
	{
		this->x = rhs.x;
		this->y = rhs.y;
		this->z = rhs.z;
		this->w = rhs.w;
	}

	Vector4& operator=( const Vector4& rhs )
	{
		this->x = rhs.x;
		this->y = rhs.y;
		this->z = rhs.z;
		this->w = rhs.w;

		return *this;
	}

	~Vector4( ) = default;

	Vector4 operator + ( const Vector4& rhs ) const { return Vector4( x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w ); }
	Vector4 operator - ( const Vector4& rhs ) const { return Vector4( x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w ); }
	Vector4 operator * ( const float& rhs ) const { return Vector4( x * rhs, y * rhs, z * rhs, w * rhs ); }
	Vector4 operator / ( const float& rhs ) const { return Vector4( x / rhs, y / rhs, z / rhs, w / rhs ); }

	Vector4& operator += ( const Vector4& rhs ) { return *this = *this + rhs; }
	Vector4& operator -= ( const Vector4& rhs ) { return *this = *this - rhs; }
	Vector4& operator *= ( const float& rhs ) { return *this = *this * rhs; }
	Vector4& operator /= ( const float& rhs ) { return *this = *this / rhs; }

	float Length( ) const
	{
		return sqrtf( x * x + y * y + z * z + w * w );
	}

	Vector4 Normalize( ) const
	{
		return *this * (1 / Length( ));
	}

	float Distance( const Vector4& rhs ) const 
	{
		return (*this - rhs).Length( );
	}
};

struct Matrix3x4
{
	float matrix[12];
};

struct Matrix4x4
{
	float matrix[4][4];

	Matrix4x4( ) = default;
};