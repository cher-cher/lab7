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
		,m_endOfCapacity(arr.m_endOfCapacity)
	{
		arr.m_begin = nullptr;
		arr.m_end = nullptr;
		arr.m_endOfCapacity = nullptr;
	}

	CMyArray<T> & operator=(CMyArray<T> && arr)
	{
		if (&arr != this)
		{
			Clear();
			m_begin = arr.m_begin;
			m_end = arr.m_end;
			m_endOfCapacity = arr.m_endOfCapacity;
			arr.m_begin = nullptr;
			arr.m_end = nullptr;
			arr.m_endOfCapacity = nullptr;
		}
		return *this;
	}

	CMyArray<T> & operator=(const CMyArray<T> & arr)
	{
		if (&arr != this)
		{
			Clear();
			const auto size = arr.GetSize();
			if (size != 0)
			{
				CMyArray<T> arr2 = *this;
				m_begin = RawAlloc(size);
				try
				{
					CopyItems(arr.m_begin, arr.m_end, m_begin, m_end);
					m_endOfCapacity = m_end;
				}
				catch (...)
				{
					DeleteItems(m_begin, m_end); 
					m_endOfCapacity = m_begin;
					CopyItems(arr2.m_begin, arr2.m_end, m_begin, m_end);
					throw;
				}
			}
		}
		return *this;
	}
	
	T & operator[](size_t index)
	{
		if (index >= (m_end - m_begin))
		{
			throw std::out_of_range("index out of range");
		}
		return *(m_begin + index);
	}

	const T & operator[](size_t index)const
	{
		if (index >= (m_end - m_begin))
		{
			throw std::out_of_range("index out of range");
		}
		return *(m_begin + index);
	}

	void Clear()
	{
		DestroyItems(m_begin, m_end);
		m_end = m_begin;
		m_endOfCapacity = m_begin;
	}

	void Resize(size_t size)
	{
		auto end = m_end;
		if (GetSize() < size)
		{
			if (GetCapacity() > size)
			{
				m_end += size - GetSize();
			}
			else if (GetCapacity() < size)
			{
				ResizeCapcity(size);
			}
			try
			{
				end = m_end;
				m_end = m_begin + size;
				for (; end != m_end; end++)
				{
					new (end)T();
				}
			}
			catch (...)
			{
				throw;
			}
		}
		else if (GetSize() > size)
		{
			m_end -= GetSize() - size;
			DestroyItems(m_end, end);
		}
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

	CMyIterator<T, false> begin()
	{//нет возможности получть итератор у const arr, переименовать 
		CMyIterator<T, false> it(m_begin);
		return it;
	}

	CMyIterator<const T, false> begin() const
	{
		CMyIterator<const T, false> it(m_begin);
		return it;
	}

	CMyIterator<T, false> end()
	{//исправить итератор, не должен совпадать rbegin
		CMyIterator<T, false> it(m_end - 1);
		return it;
	}
	
	CMyIterator<const T, false> end() const
	{
		CMyIterator<T, false> it(m_end - 1);
		return it;
	}
	CMyIterator<T, true> rbegin()
	{
		CMyIterator<T, true> it(m_end - 1);
		return it;
	}

	CMyIterator<const T, true> rbegin()const
	{
		CMyIterator<T, true> it(m_end - 1);
		return it;
	}
	
	CMyIterator<T, true> rend()
	{//не должен совпадать с begin
		CMyIterator<T, true> it(m_begin);
		return it;
	}

	CMyIterator<const T, true> rend() const
	{//не должен совпадать с begin
		CMyIterator<T, true> it(m_begin);
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
	
	void ResizeCapcity(size_t size)
	{
		if (GetCapacity() < size)
		{
			auto newBegin = RawAlloc(size);
			T *newEnd = newBegin;
			try 
			{
				CopyItems(m_begin, m_end, newBegin, newEnd);
				
				DestroyItems(m_begin, m_end);
				RawDealloc(m_begin);
			}
			catch (...)
			{
				throw;
			}
			
			m_begin = newBegin;
			m_end = newEnd;
			m_endOfCapacity = m_begin + size;
		}
	}
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