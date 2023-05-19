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

struct Vector4
{
	float values[4];

	Vector4( )
	{
		values[0] = values[1] = values[2] = values[3] = 0;
	}

	Vector4( float x, float y, float z, float w )
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

	Vector4& operator+( Vector4 arg )
	{
		values[0] += arg.values[0];
		values[1] += arg.values[1];
		values[2] += arg.values[2];
		values[3] += arg.values[3];

		return *this;
	}

	Vector4& operator-( Vector4 arg )
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
	Vector4 columns[4];

	Matrix4x4( )
	{
		columns[0] = Vector4( 1, 0, 0, 0 );
		columns[1] = Vector4( 0, 1, 0, 0 );
		columns[2] = Vector4( 0, 0, 1, 0 );
		columns[3] = Vector4( 0, 0, 0, 1 );
	}

	Matrix4x4( Vector4 x, Vector4 y, Vector4 z, Vector4 w )
	{
		columns[0] = x;
		columns[1] = y;
		columns[2] = z;
		columns[3] = w;
	}

	const Vector4& operator[]( int index ) const
	{
		return columns[index];
	}

	Vector4& operator[]( int index )
	{
		return columns[index];
	}

	// Pre-multiply a vector by a matrix on the left.

	
};

// Pre-multiply a vector by a matrix on the left.
// i.e. multiply the rows of matirix to the column vector v
// ROW MAJOR

Vector4 operator*( const Matrix4x4& m, const Vector4& v )
{
	return Vector4
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

Vector4 operator*( const Vector4& v, const Matrix4x4& m  )
{
	return Vector4
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
	Vector4 x
	{
		m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1] + m1[2][0] * m2[0][2] + m1[3][0] * m2[0][3],
		m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1] + m1[2][1] * m2[0][2] + m1[3][1] * m2[0][3],
		m1[0][2] * m2[0][0] + m1[1][2] * m2[0][1] + m1[2][2] * m2[0][2] + m1[3][2] * m2[0][3],
		m1[0][3] * m2[0][0] + m1[1][3] * m2[0][1] + m1[2][3] * m2[0][2] + m1[3][3] * m2[0][3]
	};

	Vector4 y
	{
		m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1] + m1[2][0] * m2[1][2] + m1[3][0] * m2[1][3],
		m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1] + m1[2][1] * m2[1][2] + m1[3][1] * m2[1][3],
		m1[0][2] * m2[1][0] + m1[1][2] * m2[1][1] + m1[2][2] * m2[1][2] + m1[3][2] * m2[1][3],
		m1[0][3] * m2[1][0] + m1[1][3] * m2[1][1] + m1[2][3] * m2[1][2] + m1[3][3] * m2[1][3]
	};

	Vector4 z
	{
	    m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1] + m1[2][0] * m2[2][2] + m1[3][0] * m2[2][3],
		m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1] + m1[2][1] * m2[2][2] + m1[3][1] * m2[2][3],
		m1[0][2] * m2[2][0] + m1[1][2] * m2[2][1] + m1[2][2] * m2[2][2] + m1[3][2] * m2[2][3],
		m1[0][3] * m2[2][0] + m1[1][3] * m2[2][1] + m1[2][3] * m2[2][2] + m1[3][3] * m2[2][3]
	};

	Vector4 w
	{
		m1[0][0] * m2[3][0] + m1[1][0] * m2[3][1] + m1[2][0] * m2[3][2] + m1[3][0] * m2[3][3],
		m1[0][1] * m2[3][0] + m1[1][1] * m2[3][1] + m1[2][1] * m2[3][2] + m1[3][1] * m2[3][3],
		m1[0][2] * m2[3][0] + m1[1][2] * m2[3][1] + m1[2][2] * m2[3][2] + m1[3][2] * m2[3][3],
		m1[0][3] * m2[3][0] + m1[1][3] * m2[3][1] + m1[2][3] * m2[3][2] + m1[3][3] * m2[3][3]
	};

	return Matrix4x4( x, y, z, w );
}