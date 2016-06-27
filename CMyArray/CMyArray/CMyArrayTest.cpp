// CMyArray.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "CMyArray.h"

using namespace std;

#include "stdafx.h"
#include <stdexcept>

struct MyStruct
{
	CMyArray<int> arr;
};

BOOST_FIXTURE_TEST_SUITE(Array_tests, MyStruct)
	BOOST_AUTO_TEST_CASE(get_size_tests)
	{
		BOOST_CHECK_EQUAL(arr.GetSize(), 0);
		arr.Append(0);
		BOOST_CHECK_EQUAL(arr.GetSize(), 1);
		arr.Append(0);
		BOOST_CHECK_EQUAL(arr.GetSize(), 2);
		arr.Append(0);
		BOOST_CHECK_EQUAL(arr.GetSize(), 3);
	}

BOOST_AUTO_TEST_SUITE(after_copy_construction)
	BOOST_AUTO_TEST_CASE(has_size_capacity_equal_to_size_of_original_array)
	{
		for (auto i = 0; i < 6; ++i)
		{
			arr.Append(i);
		}
		BOOST_CHECK_NE(arr.GetSize(), arr.GetCapacity());

		auto copy(arr);
		BOOST_CHECK_EQUAL(copy.GetSize(), arr.GetSize());
		BOOST_CHECK_EQUAL(copy.GetCapacity(), arr.GetSize());
		BOOST_CHECK_EQUAL(arr.GetSize(), 6);
		BOOST_CHECK_EQUAL(arr[2], 2);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_CASE(assigment_cmyarray)
{
	for (auto i = 0; i < 6; ++i)
	{
		arr.Append(i);
	}
	BOOST_CHECK_EQUAL(arr.GetSize(), 6);
	BOOST_CHECK_EQUAL(arr[1], 1);
}

BOOST_AUTO_TEST_CASE(clear_array)
	{
		for (auto i = 0; i < 6; ++i)
		{
			arr.Append(i);
		}
		arr.Clear();
		BOOST_CHECK_EQUAL(arr.GetSize(), 0);
		BOOST_CHECK_THROW(arr[2], std::out_of_range);
	}

BOOST_AUTO_TEST_CASE(resize_array)
{
	arr.Resize(4, 0);
	BOOST_CHECK_EQUAL(arr.GetSize(), 4);
	BOOST_CHECK_EQUAL(arr.GetCapacity(), 8);
	for (auto i = 0; i < 6; ++i)
	{
		arr.Append(i);
	}
	BOOST_CHECK_EQUAL(arr.GetCapacity(), 16);
	arr.Resize(7, 0);
	BOOST_CHECK_EQUAL(arr.GetSize(), 7);
	BOOST_CHECK_EQUAL(arr.GetCapacity(), 14);
	arr.Resize(5, 0);
	BOOST_CHECK_EQUAL(arr.GetSize(), 5);
	BOOST_CHECK_EQUAL(arr.GetCapacity(), 10);
}

BOOST_AUTO_TEST_CASE(assignment_operator)
{
	bool result = true; 
	CMyArray<int> arr1;
	for (auto i = 0; i < 6; ++i)
	{
		arr.Append(i);
	}
	arr1 = arr;
	for (auto i = 0; i < 6; i++)
	{
		if (arr[i] != arr1[i])
		{
			result = false;
		}
	}
	BOOST_CHECK_EQUAL(result, true);
}

BOOST_AUTO_TEST_CASE(moves_constructor)
{
	CMyArray<int> arr1;
	for (auto i = 0; i < 6; ++i)
	{
		arr1.Append(i);
	}
	size_t size = arr1.GetSize();
	CMyArray<int> arr2(std::move(arr1));
	BOOST_CHECK_EQUAL(arr1.GetSize(), 0);
	BOOST_CHECK_EQUAL(arr2.GetSize(), size);
}

BOOST_AUTO_TEST_CASE(moves_assignment_operator)
{
	CMyArray<int> arr3;
	for (auto i = 0; i < 6; ++i)
	{
		arr3.Append(i);
	}
	size_t size = arr3.GetSize();
	CMyArray<int> arr4 = std::move(arr3);
	BOOST_CHECK_EQUAL(arr3.GetSize(), 0);
	BOOST_CHECK_EQUAL(arr4.GetSize(), size);
}

BOOST_AUTO_TEST_CASE(begin)
{
	CMyArray<int> arr;
	for (auto i = 0; i < 6; ++i)
	{
		arr.Append(i);
	}
	CMyIterator<int> it = arr.Begin();
	++it;
	BOOST_CHECK_EQUAL(*it, 1);
}

BOOST_AUTO_TEST_CASE(rbegin)
{
	CMyArray<int> arr;
	for (auto i = 0; i < 6; ++i)
	{
		arr.Append(i);
	}
	CMyIterator<int> it = arr.RBegin();
	--it;
	BOOST_CHECK_EQUAL(*it, 5);
}

BOOST_AUTO_TEST_CASE(end)
{
	CMyArray<int> arr;
	for (auto i = 0; i < 6; ++i)
	{
		arr.Append(i);
	}
	CMyIterator<int> it = arr.End();
	--it;
	BOOST_CHECK_EQUAL(*it, 5);
}

BOOST_AUTO_TEST_CASE(rend)
{
	CMyArray<int> arr;
	for (auto i = 0; i < 6; ++i)
	{
		arr.Append(i);
	}
	CMyIterator<int> it = arr.REnd();
	++it;
	BOOST_CHECK_EQUAL(*it, 1);
}
BOOST_AUTO_TEST_SUITE_END()