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

class Vector3
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

struct Vector2
{
	float x{};
	float y{};

	Vector2( )
	{
		x = y = 0;
	}

	Vector2( float x, float y)
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

	Vector2 operator + ( const Vector2 & rhs ) const { return Vector2( x + rhs.x, y + rhs.y ); }
	Vector2 operator - ( const Vector2& rhs ) const { return Vector2( x - rhs.x, y - rhs.y ); }
	Vector2 operator * ( const float& rhs ) const { return Vector2( x * rhs, y * rhs ); }
	Vector2 operator / ( const float& rhs ) const { return Vector2( x / rhs, y / rhs ); }

	Vector2& operator += ( const Vector2 & rhs ) { return *this = *this + rhs; }
	Vector2& operator -= ( const Vector2 & rhs ) { return *this = *this - rhs; }
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

	float Distance( const Vector2 & rhs ) const {
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

	Vector4( float x, float y, float z )
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

	float Length( ) const
	{
		return sqrtf( x * x + y * y + z * z + w * w );
	}
};

struct Vec4
{
	float values[4];

	Vec4( )
	{
		values[0] = values[1] = values[2] = values[3] = 0;
	}

	Vec4( float x, float y, float z, float w )
	{
		values[0] = x;
		values[1] = y;
		values[2] = z;
		values[3] = w;
	}

	const float& operator[]( int index ) const
	{
		return values[index];
	}

	float& operator[]( int index )
	{
		return values[index];
	}

	Vec4& operator+( Vec4 arg )
	{
		values[0] += arg.values[0];
		values[1] += arg.values[1];
		values[2] += arg.values[2];
		values[3] += arg.values[3];

		return *this;
	}

	Vec4& operator-( Vec4 arg )
	{

		values[0] += arg.values[0];
		values[1] += arg.values[1];
		values[2] += arg.values[2];
		values[3] += arg.values[3];

		return *this;
	}
};

struct Matrix3x4
{
	float matrix[12];
};

struct Matrix4x4
{
	Vec4 columns[4];

	Matrix4x4( )
	{
		columns[0] = Vec4( 1, 0, 0, 0 );
		columns[1] = Vec4( 0, 1, 0, 0 );
		columns[2] = Vec4( 0, 0, 1, 0 );
		columns[3] = Vec4( 0, 0, 0, 1 );
	}

	Matrix4x4( Vec4 x, Vec4 y, Vec4 z, Vec4 w )
	{
		columns[0] = x;
		columns[1] = y;
		columns[2] = z;
		columns[3] = w;
	}

	const Vec4& operator[]( int index ) const
	{
		return columns[index];
	}

	Vec4& operator[]( int index )
	{
		return columns[index];
	}

	// Pre-multiply a vector by a matrix on the left.

	
};

// Pre-multiply a vector by a matrix on the left.
// i.e. multiply the rows of matirix to the column vector v
// ROW MAJOR

Vec4 operator*( const Matrix4x4& m, const Vec4& v )
{
	return Vec4
	(
		m[0][0] * v[0] + m[1][0] * v[1] + m[2][0] * v[2] + m[3][0] * v[3],
		m[0][1] * v[0] + m[1][1] * v[1] + m[2][1] * v[2] + m[3][1] * v[3],
		m[0][2] * v[0] + m[1][2] * v[1] + m[2][2] * v[2] + m[3][2] * v[3],
		m[0][3] * v[0] + m[1][3] * v[1] + m[2][3] * v[2] + m[3][3] * v[3]
	);
}

// Pre-multiply a vector by a matrix on the right.
// i.e. multiply the columns of matirix to the row vector v
// COLUMN MAJOR

Vec4 operator*( const Vec4& v, const Matrix4x4& m  )
{
	return Vec4
	(
		v[0] + m[0][0] * v[1] + m[0][1] * v[2] + m[0][2] * v[3] * m[0][3],
		v[0] + m[1][0] * v[1] + m[1][1] * v[2] + m[1][2] * v[3] * m[1][3], 
		v[0] + m[2][0] * v[1] + m[2][1] * v[2] + m[2][2] * v[3] * m[2][3],
		v[0] + m[3][0] * v[1] + m[3][1] * v[2] + m[3][2] * v[3] * m[3][3]
	);
}

// Multiply matrix m1 by matrix m2.
// i.e. multiply the rows of m1 by the columns of m2

Matrix4x4 operator*( const Matrix4x4& m1, const Matrix4x4& m2 )
{
	Vec4 x
	{
		m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1] + m1[2][0] * m2[0][2] + m1[3][0] * m2[0][3],
		m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1] + m1[2][1] * m2[0][2] + m1[3][1] * m2[0][3],
		m1[0][2] * m2[0][0] + m1[1][2] * m2[0][1] + m1[2][2] * m2[0][2] + m1[3][2] * m2[0][3],
		m1[0][3] * m2[0][0] + m1[1][3] * m2[0][1] + m1[2][3] * m2[0][2] + m1[3][3] * m2[0][3]
	};

	Vec4 y
	{
		m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1] + m1[2][0] * m2[1][2] + m1[3][0] * m2[1][3],
		m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1] + m1[2][1] * m2[1][2] + m1[3][1] * m2[1][3],
		m1[0][2] * m2[1][0] + m1[1][2] * m2[1][1] + m1[2][2] * m2[1][2] + m1[3][2] * m2[1][3],
		m1[0][3] * m2[1][0] + m1[1][3] * m2[1][1] + m1[2][3] * m2[1][2] + m1[3][3] * m2[1][3]
	};

	Vec4 z
	{
	    m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1] + m1[2][0] * m2[2][2] + m1[3][0] * m2[2][3],
		m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1] + m1[2][1] * m2[2][2] + m1[3][1] * m2[2][3],
		m1[0][2] * m2[2][0] + m1[1][2] * m2[2][1] + m1[2][2] * m2[2][2] + m1[3][2] * m2[2][3],
		m1[0][3] * m2[2][0] + m1[1][3] * m2[2][1] + m1[2][3] * m2[2][2] + m1[3][3] * m2[2][3]
	};

	Vec4 w
	{
		m1[0][0] * m2[3][0] + m1[1][0] * m2[3][1] + m1[2][0] * m2[3][2] + m1[3][0] * m2[3][3],
		m1[0][1] * m2[3][0] + m1[1][1] * m2[3][1] + m1[2][1] * m2[3][2] + m1[3][1] * m2[3][3],
		m1[0][2] * m2[3][0] + m1[1][2] * m2[3][1] + m1[2][2] * m2[3][2] + m1[3][2] * m2[3][3],
		m1[0][3] * m2[3][0] + m1[1][3] * m2[3][1] + m1[2][3] * m2[3][2] + m1[3][3] * m2[3][3]
	};

	return Matrix4x4( x, y, z, w );
}