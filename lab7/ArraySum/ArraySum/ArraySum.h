#pragma once
#include <vector>

template <typename T>
T ArraySum(std::vector<T> const& arr)
{
	T sumOfElements = T();

	if (!arr.empty())
	{
		for (auto& elem : arr)
			sumOfElements += elem;
	}
	return sumOfElements;
};