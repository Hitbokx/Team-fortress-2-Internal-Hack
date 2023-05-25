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

	Vector3( )
	{
		x = y = z = 0;
	}

	Vector3( float x, float y, float z )
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector3( Vector3& rhs )
	{
		this->x = rhs.x;
		this->y = rhs.y;
		this->z = rhs.z;
	}

	Vector3& operator=( const Vector3& rhs )
	{
		this->x = rhs.x;
		this->y = rhs.y;
		this->z = rhs.z;

		return *this;
	}

	~Vector3( ) = default;

	Vector3 operator + ( const Vector3& rhs ) const { return Vector3( x + rhs.x, y + rhs.y, z + rhs.z ); }
	Vector3 operator - ( const Vector3& rhs ) const { return Vector3( x - rhs.x, y - rhs.y, z - rhs.z ); }
	Vector3 operator * ( const float& rhs ) const { return Vector3( x * rhs, y * rhs, z * rhs ); }
	Vector3 operator / ( const float& rhs ) const { return Vector3( x / rhs, y / rhs, z / rhs ); }

	Vector3& operator += ( const Vector3& rhs ) { return *this = *this + rhs; }
	Vector3& operator -= ( const Vector3& rhs ) { return *this = *this - rhs; }
	Vector3& operator *= ( const float& rhs ) { return *this = *this * rhs; }
	Vector3& operator /= ( const float& rhs ) { return *this = *this / rhs; }

	float Length( ) const
	{
		return sqrtf( x * x + y * y + z * z );
	}

	Vector3 Normalize( ) const
	{
		return *this * (1 / Length( ));
	}

	float Distance( const Vector3& rhs ) const {
		return (*this - rhs).Length( );
	}
};

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