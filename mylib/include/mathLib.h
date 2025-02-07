#pragma once
#include <iostream>
#include "myVector.h"
#include "myVectorND.h"

namespace Math
{
	template<typename T, size_t N>
	auto scalarProduct(const myVector<T, N>& vec1, const myVector<T, N>& vec2)
	{
		if (vec1.size() != vec2.size())
			throw std::runtime_error("size must be equal");

		float result = 0;
		for (size_t i = 0; i < vec1.size(); ++i)
		{
			result += vec1[i] * vec2[i];
		}

		return result;
	}

	template<typename T, size_t N>
	auto scalarProduct(const myVectorND<T, N>& vec1, const myVectorND<T, N>& vec2)
	{
		if (vec1.Size() != vec2.Size())
			throw std::runtime_error("size must be equal");

		float result = 0;
		for (size_t i = 0; i < vec1.Size(); ++i)
		{
			result += vec1[i] * vec2[i];
		}

		return result;
	}

	template<typename T, size_t N>
	auto crossProduct(const myVector<T, N>& vec1, const myVector<T, N>& vec2)
	{
		static_assert(N == 3, "Cross product is only defined for 3-dimensional vectors");

		myVector<T, 3> result;
		result[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
		result[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
		result[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];

		return result;
	}

	template<typename T, size_t N>
	auto crossProduct(const myVectorND<T, N>& vec1, const myVectorND<T, N>& vec2)
	{
		static_assert(N == 3, "Cross product is only defined for 3-dimensional vectors");

		myVectorND<T, 3> result;
		result[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
		result[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
		result[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];

		return result;
	}

};