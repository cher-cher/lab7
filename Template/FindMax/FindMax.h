#pragma once

#include "stdafx.h"

template <typename T>

bool FindMax(std::vector<T> const& arr, T& maxValue)
{
	if (arr.empty())
	{
		return false;
	}
	maxValue = *std::max_element(arr.begin(), arr.end());
	return true;
}

template <>
bool FindMax<const char *>(std::vector<const char*> const& arr, const char* & maxValue)
{
	if (arr.empty())
	{
		return false;
	}
	/*maxValue = arr[0];
	for (size_t i = 1; i < arr.size(); i++)
	{
		if (strcmp(maxValue, arr[i]) < 0)
		{
			maxValue = arr[i];
		}
	}*/
	maxValue = *std::max_element(arr.begin(), arr.end());
	return true;
}