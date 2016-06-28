#pragma once
#include "stdafx.h"
#include "CMyIterator.h"
#include <new>
#include <algorithm>

template <typename T>
class CMyArray
{
public:
	CMyArray() = default;

	CMyArray(const CMyArray& arr)
	{
		const auto size = arr.GetSize();
		if (size != 0)
		{
			m_begin = RawAlloc(size);
			try
			{
				CopyItems(arr.m_begin, arr.m_end, m_begin, m_end);
				m_endOfCapacity = m_end;
			}
			catch (...)
			{
				DeleteItems(m_begin, m_end);
				throw;
			}
		}
	}

	CMyArray(CMyArray&& arr)
		:m_begin(arr.m_begin)
		,m_end(arr.m_end)
	{
		arr.m_begin = nullptr;
		arr.m_end = nullptr;
	}

	CMyArray<T> & operator=(CMyArray<T> && arr)
	{
		if (&arr != this)
		{
			Clear();
			m_begin = arr.m_begin;
			m_end = arr.m_end;
			arr.m_begin = nullptr;
			arr.m_end = nullptr;
		}
		return *this;
	}

	CMyArray<T> & operator=(const CMyArray<T> & arr)
	{
		const auto size = arr.GetSize();
		if (size != 0)
		{
			m_begin = RawAlloc(size);
			try
			{
				CopyItems(arr.m_begin, arr.m_end, m_begin, m_end);
				m_endOfCapacity = m_end;
			}
			catch (...)
			{
				DeleteItems(m_begin, m_end);
				throw;
			}
		}
		return *this;
	}
	
	T & operator[](size_t index)
	{
		if (index < 0 || index >= (m_end - m_begin))
		{
			throw std::out_of_range("index out of range");
		}
		return *(m_begin + index);
	}

	void Clear()
	{
		DeleteItems(m_begin, m_end);
		m_begin = nullptr;
		m_end = nullptr;
	}

	void Resize(size_t size, T const& value = T())
	{
		size_t newCapacity = std::max(1u, size * 2);

		auto newBegin = RawAlloc(newCapacity);
		T *newEnd = newBegin;
		try
		{
			if (size > GetSize())
			{
				CopyItems(m_begin, m_end, newBegin, newEnd);
				for (size_t i = 0; i < size - GetSize(); i++)
				{
					new (newEnd)T(value);
					++newEnd;
				}
			}
			else
			{
				CopyItems(m_begin, m_begin + size, newBegin, newEnd);
			}
		}
		catch (...)
		{
			DeleteItems(newBegin, newEnd);
			throw;
		}
		DeleteItems(m_begin, m_end);

		// Переключаемся на использование нового хранилища элементов
		m_begin = newBegin;
		m_end = newEnd;
		m_endOfCapacity = m_begin + newCapacity;
	}

	void Append(const T & value)
	{
		if (m_end == m_endOfCapacity) // no free space
		{
			size_t newCapacity = std::max(1u, GetCapacity() * 2);

			auto newBegin = RawAlloc(newCapacity);
			T *newEnd = newBegin;
			try
			{
				CopyItems(m_begin, m_end, newBegin, newEnd);
				// Конструируем копию value по адресу newItemLocation
				new (newEnd)T(value);
				++newEnd;
			}
			catch (...)
			{
				DeleteItems(newBegin, newEnd);
				throw;
			}
			DeleteItems(m_begin, m_end);

			// Переключаемся на использование нового хранилища элементов
			m_begin = newBegin;
			m_end = newEnd;
			m_endOfCapacity = m_begin + newCapacity;
		}
		else // has free space
		{
			new (m_end) T(value);
			++m_end;
		}
	}

	CMyIterator<T> Begin()
	{
		CMyIterator<T> it(m_begin, false);
		return it;
	}

	CMyIterator<T> RBegin()
	{
		CMyIterator<T> it(m_end - 1, true);
		return it;
	}

	CMyIterator<T> End()
	{
		CMyIterator<T> it(m_end - 1, true);
		return it;
	}
	
	CMyIterator<T> REnd()
	{
		CMyIterator<T> it(m_begin, false);
		return it;
	}

	T & GetBack()
	{
		assert(GetSize() != 0u);
		return m_end[-1];
	}

	const T & GetBack()const
	{
		assert(GetSize() != 0u);
		return m_end[-1];
	}

	size_t GetSize()const
	{
		return m_end - m_begin;
	}

	size_t GetCapacity()const
	{
		return m_endOfCapacity - m_begin;
	}
	~CMyArray()
	{
		DeleteItems(m_begin, m_end);
	}
private:

	static void DeleteItems(T *begin, T *end)
	{
		// Разрушаем старые элементы
		DestroyItems(begin, end);
		// Освобождаем область памяти для их хранения
		RawDealloc(begin);
	}

	// Копирует элементы из текущего вектора в to, возвращает newEnd
	static void CopyItems(const T *srcBegin, T *srcEnd, T * const dstBegin, T * & dstEnd)
	{
		for (dstEnd = dstBegin; srcBegin != srcEnd; ++srcBegin, ++dstEnd)
		{
			// Construct "T" at "dstEnd" as a copy of "*begin"
			new (dstEnd)T(*srcBegin);
		}
	}

	static void DestroyItems(T *from, T *to)
	{
		// dst - адрес объект, при конструирование которого было выброшено исключение
		// to - первый скорнструированный объект
		while (to != from)
		{
			--to;
			// явно вызываем деструктор для шаблонного типа T
			to->~T();
		}
	}

	static T *RawAlloc(size_t n)
	{
		size_t memSize = n * sizeof(T);
		T *p = static_cast<T*>(malloc(memSize));
		if (!p)
		{
			throw std::bad_alloc();
		}
		return p;
	}

	static void RawDealloc(T *p)
	{
		free(p);
	}

private:
	T *m_begin = nullptr;
	T *m_end = nullptr;
	T *m_endOfCapacity = nullptr;
};