#pragma once
#include "stdafx.h"

template <typename T , bool isReversed>
class CMyIterator
{
public:
	CMyIterator(T * current)
		:m_current(current)
	{
	}
	
	T* operator ->()
	{
		return m_current;
	}

	T operator*() const
	{
		return *m_current;
	}

	CMyIterator & operator+=(const size_t numb)
	{
		if (m_isReverse)
		{
			m_current += numb * (-1);
		}
		else
		{
			m_current += numb;
		}
		return *this;
	}

	CMyIterator & operator-=(const size_t numb)
	{
		if (m_isReverse)
		{
			m_current -= numb * (-1);
		}
		else
		{
			m_current -= numb;
		}
		return *this;
	}

	CMyIterator & operator++()
	{
		if (m_isReverse)
		{
			--m_current;
		}
		else
		{
			++m_current;
		}
		return *this;
	}

	CMyIterator operator++(int)
	{
		if (m_isReverse)
		{
			m_current--;
		}
		else
		{
			m_current++;
		}
		return *this;
	}

	CMyIterator& operator--()
	{
		if (m_isReverse)
		{
			--m_current;
		}
		else
		{
			++m_current;
		}
		return *this;
	}

	CMyIterator operator--(int)
	{
		if (m_isReverse)
		{
			m_current--;
		}
		else
		{
			m_current++;
		}
		return *this;
	}

	bool operator!=(CMyIterator const& other) const
	{
		return it != other.it;
	}

	bool operator==(CMyIterator const& other) const
	{
		return it == other.it;
	}

	bool operator<(CMyIterator const& other) const
	{
		return (*this) < other;
	}

	bool operator>(CMyIterator const& other) const
	{
		return (*this) > other;
	}

	bool operator<=(CMyIterator const& other) const
	{
		return (*this) <= other;
	}

	bool operator>=(CMyIterator const& other) const
	{
		return (*this) >= other;
	}

	T & operator[](size_t index)
	{
		return m_current[index];
	}

	const T & operator[](const size_t index)const
	{
		return m_current[index];
	}

private:
	T * m_current;
	bool m_isReverse;
};