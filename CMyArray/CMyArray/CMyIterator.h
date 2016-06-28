#pragma once
#include "stdafx.h"

template <typename T>
class CMyIterator
{
public:
	CMyIterator(T * current, bool isReverse)
		:m_current(current)
		,m_isReverse(isReverse)
	{
	}

	T CMyIterator<T>::operator*() const
	{
		return *m_current;
	}

	CMyIterator<T> &CMyIterator<T>::operator++()
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

	CMyIterator<T>& CMyIterator<T>::operator--()
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

private:
	T * m_current;
	bool m_isReverse;
};