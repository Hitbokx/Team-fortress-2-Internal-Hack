#pragma once

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

	Vector3& operator+( Vector3 arg )
	{
		x += arg.x;
		y += arg.y;
		z += arg.z;

		return *this;
	}

	Vector3& operator-( Vector3 arg )
	{
		x -= arg.x;
		y -= arg.y;
		z -= arg.z;

		return *this;
	}
};

struct Matrix3x4
{
	float matrix[12];
};