// CMyArray.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "CMyArray.h"
#include <stdexcept>
#include <iostream>
using namespace std;


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
	arr.Resize(4);
	BOOST_CHECK_EQUAL(arr.GetSize(), 4);
	for (auto i = 0; i < 6; ++i)
	{
		arr.Append(i);
	}
	arr.Resize(7);
	BOOST_CHECK_EQUAL(arr.GetSize(), 7);
	arr.Resize(5);
	BOOST_CHECK_EQUAL(arr.GetSize(), 5);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_CASE(assignment_operator)
{
	bool result = true; 
	CMyArray<int> arr;
	CMyArray<int> arr1;
	CMyArray<int> arr2;
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
	arr1 = arr2;
	BOOST_CHECK_EQUAL(arr1.GetSize(), 0);
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

BOOST_AUTO_TEST_CASE(begin_and_iterator)
{
	CMyArray<int> arr;
	for (auto i = 0; i < 6; ++i)
	{
		arr.Append(i);
	}
	auto it = arr.begin();

	it++;
	BOOST_CHECK_EQUAL(*arr.begin(), 0);
	BOOST_CHECK_EQUAL(*arr.end(), 5);
}

BOOST_AUTO_TEST_CASE(rbegin_iterator)
{
	CMyArray<int> arr;
	for (auto i = 0; i < 6; ++i)
	{
		arr.Append(i);
	}
	CMyIterator<int, true> it = arr.rbegin();
	//++it;
	BOOST_CHECK_EQUAL(*it, 5);
}

BOOST_AUTO_TEST_CASE(iterator_operator_brackets)
{
	CMyArray<int> arr;
	for (auto i = 0; i < 6; ++i)
	{
		arr.Append(i);
	}
	int ind = 0;
	bool result = true;
	CMyIterator<int, false> it = arr.begin();
	for (size_t i = 0; i < arr.GetSize(); i++, ind++)
	{
		if (it[i] != ind)
		{
			result = false;
		}
	}
	BOOST_CHECK(result);
}

BOOST_AUTO_TEST_CASE(operator_not_equal)
{
	CMyArray<int> arr5;
	bool result1 = true;
	for (auto i = 0; i < 6; ++i)
	{
		arr5.Append(i);
	}
	CMyIterator<int, false> it2 = arr5.begin();
	if (it2[1] != it2[2])
	{
		result1 = true;
	}
	BOOST_CHECK(result1);
}

BOOST_AUTO_TEST_CASE(operator_less)
{
	CMyArray<int> arr6;
	bool result2 = true;
	for (auto i = 0; i < 6; ++i)
	{
		arr6.Append(i);
	}
	CMyIterator<int, false> it1 = arr6.begin();
	if (it1[1] < it1[2])
	{
		result2 = true;
	}
	BOOST_CHECK(result2);
}

BOOST_AUTO_TEST_CASE(minus_plus)
{
	CMyArray<int> arr;
	arr.Append(1);
	arr.Append(2);
	arr.Append(3);

	auto ptr = arr.begin();
	ptr += 1;
	BOOST_CHECK_EQUAL(*ptr, 2);
	ptr += 1;
	BOOST_CHECK_EQUAL(*ptr, 3);
	ptr -= 1;
	BOOST_CHECK_EQUAL(*ptr, 2);
}
