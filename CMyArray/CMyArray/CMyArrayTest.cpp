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

/*BOOST_AUTO_TEST_CASE(get_item_by_index)
{
	arr.Append(2);
	arr.Append(5);
	arr.Append(7);
	BOOST_CHECK_EQUAL(arr[0], 2);
	BOOST_CHECK_EQUAL(arr[1], 5);
	BOOST_CHECK_EQUAL(arr[2], 7);
	BOOST_CHECK_THROW(arr[3], std::out_of_range);
}

BOOST_AUTO_TEST_CASE(resize_array_width_start_item)
{
	arr.Resize(10, 5);
	BOOST_CHECK_EQUAL(arr.GetSize(), 10);
	BOOST_CHECK_EQUAL(arr[0], 5);
	BOOST_CHECK_EQUAL(arr[9], 5);
	arr.Resize(2, 5);
	BOOST_CHECK_EQUAL(arr.GetSize(), 2);
	BOOST_CHECK_EQUAL(arr[1], 5);
}

BOOST_AUTO_TEST_CASE(clear_array)
{
	arr.Resize(10, 1);
	arr.Clear();
	BOOST_CHECK_EQUAL(arr.GetSize(), 0);
	BOOST_CHECK_THROW(arr[0], std::out_of_range);
}

BOOST_AUTO_TEST_CASE(resize_with_one_argument_default_value)
{
	arr.Resize(10);
	BOOST_CHECK_EQUAL(arr.GetSize(), 10);
	BOOST_CHECK_EQUAL(arr[0], 0);
}

BOOST_AUTO_TEST_CASE(construct_copy_array_elements)
{
	CMyArray<int> arrays({ 1, 2, 3, 4, 5 });
	BOOST_CHECK_EQUAL(arrays.GetSize(), 5);
	BOOST_CHECK_EQUAL(arrays[1], 2);
}

BOOST_AUTO_TEST_CASE(assigment_cmyarray)
{
	CMyArray<int> arrays({ 1, 2, 3, 4, 5 });
	arr = arrays;
	BOOST_CHECK_EQUAL(arr.GetSize(), 5);
	BOOST_CHECK_EQUAL(arr[1], 2);
}

BOOST_AUTO_TEST_CASE(assigment_array_int)
{
	arr = { 1, 2, 3, 4, 5 };
	BOOST_CHECK_EQUAL(arr.GetSize(), 5);
	BOOST_CHECK_EQUAL(arr[2], 3);
}*/


/*struct ArrayItem
{
	ArrayItem(int value = 0) : value(value)
	{}
	int value;
};

struct EmptyStringArray
{
	CMyArray<ArrayItem> arr;
};

BOOST_FIXTURE_TEST_SUITE(MyArray, EmptyStringArray)
	BOOST_AUTO_TEST_SUITE(by_default)
		BOOST_AUTO_TEST_CASE(is_empty)
		{
			BOOST_CHECK_EQUAL(arr.GetSize(), 0u);
		}
		BOOST_AUTO_TEST_CASE(has_0_capacity)
		{
			BOOST_CHECK_EQUAL(arr.GetCapacity(), 0u);
		}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(after_appending_an_item)
	BOOST_AUTO_TEST_CASE(increases_its_size_and_capacity)
	{
		arr.Append(ArrayItem());
		BOOST_CHECK_EQUAL(arr.GetSize(), 1u);
		BOOST_CHECK_EQUAL(arr.GetCapacity(), 1u);
		arr.Append(ArrayItem());
		BOOST_CHECK_EQUAL(arr.GetSize(), 2u);
		BOOST_CHECK_EQUAL(arr.GetCapacity(), 2u);
		arr.Append(ArrayItem());
		BOOST_CHECK_EQUAL(arr.GetSize(), 3u);
		BOOST_CHECK_EQUAL(arr.GetCapacity(), 4u);
		arr.Append(ArrayItem());
		BOOST_CHECK_EQUAL(arr.GetSize(), 4u);
		BOOST_CHECK_EQUAL(arr.GetCapacity(), 4u);
	}
BOOST_AUTO_TEST_CASE(it_becomes_available_at_the_back)
{
	arr.Append(1);
	BOOST_CHECK_EQUAL(arr.GetBack().value, 1);
	arr.Append(2);
	BOOST_CHECK_EQUAL(arr.GetBack().value, 2);
	arr.Append(3);
	BOOST_CHECK_EQUAL(arr.GetBack().value, 3);
	arr.Append(4);
	BOOST_CHECK_EQUAL(arr.GetBack().value, 4);
}
BOOST_AUTO_TEST_SUITE_END()*/

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
		//BOOST_CHECK_EQUAL(arr[2], 3);
	}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_CASE(clear_array)
{
	for (auto i = 0; i < 6; ++i)
	{
		arr.Append(i);
	}
	arr.Clear();
	BOOST_CHECK_EQUAL(arr.GetSize(), 0);
	//(arr[0], std::out_of_range);
}

BOOST_AUTO_TEST_CASE(assigment_cmyarray)
{
	for (auto i = 0; i < 6; ++i)
	{
		arr.Append(i);
	}
	BOOST_CHECK_EQUAL(arr.GetSize(), 6);
	BOOST_CHECK_EQUAL(arr[1], 1);
}
BOOST_AUTO_TEST_SUITE_END()
