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