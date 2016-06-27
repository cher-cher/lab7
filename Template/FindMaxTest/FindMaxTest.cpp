// FindMaxTest.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../FindMax/FindMax.h"
#include <stdexcept>

using namespace std;

BOOST_AUTO_TEST_SUITE(findmax)

	BOOST_AUTO_TEST_CASE(vector_is_empty)
	{
		vector<int> a;
		int maxValue;
		BOOST_CHECK(!FindMax(a, maxValue));
	}

	BOOST_AUTO_TEST_CASE(int_max_element)
	{
		vector<int> a = { 13, 66, 99 };
		int maxValue;
		BOOST_CHECK(FindMax(a, maxValue));
		BOOST_CHECK_EQUAL(99, maxValue);
	}

	BOOST_AUTO_TEST_CASE(double_max_element)
	{
		vector<double> a = { -13.666, 0.0, 666.666, -666.666 };
		double maxValue;
		BOOST_CHECK(FindMax(a, maxValue));
		BOOST_CHECK_EQUAL(666.666, maxValue);
	}

	BOOST_AUTO_TEST_CASE(string_max_element)
	{
		vector<string> a = { "lol", "olol", "ololo" };
		string maxValue;
		BOOST_CHECK(FindMax(a, maxValue));
		BOOST_CHECK_EQUAL("ololo", maxValue);
	}

	BOOST_AUTO_TEST_CASE(const_char_max_element)
	{
		vector<const char*> a = { "mama", "ma", "mam", "mamama" };
		const char* maxValue;
		BOOST_CHECK(FindMax(a, maxValue));
		BOOST_CHECK_EQUAL("mamama", maxValue);
	}

	/*BOOST_AUTO_TEST_CASE(commit_or_rollback_supported)
	{
		std::string b(900'000'000, 'l');
		vector<string> a = { "pap", "lol", "maaaam", b };
		string maxValue;
		BOOST_CHECK(FindMax(a, maxValue));
		BOOST_CHECK_THROW(FindMax(a, maxValue), std::bad_alloc);
		BOOST_CHECK_EQUAL("maaaam", maxValue);
	}*/

BOOST_AUTO_TEST_SUITE_END()