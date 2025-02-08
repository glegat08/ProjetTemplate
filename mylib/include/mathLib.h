/**
 * @file mathLib.h
 * @brief Implementation of a Math namespace for products.
 * @author Guillaume
 * @date 08/02/2025
 */

#pragma once
#include <iostream>
#include "myVector.h"
#include "myVectorND.h"

namespace Math
{

	/**
	 * @brief Computes the scalar product of two vectors.
	 *
	 * @tparam T The type of elements in the vectors.
	 * @tparam N The size of the vectors.
	 * @param vec1 The first vector.
	 * @param vec2 The second vector.
	 * @return The scalar product of the two vectors.
	 * @throw std::runtime_error if the sizes of the vectors are not equal.
	 */
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

	/**
	 * @brief Computes the scalar product of two N-dimensional vectors.
	 *
	 * @tparam T The type of elements in the vectors.
	 * @tparam N The size of the vectors.
	 * @param vec1 The first vector.
	 * @param vec2 The second vector.
	 * @return The scalar product of the two vectors.
	 * @throw std::runtime_error if the sizes of the vectors are not equal.
	 */
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

	/**
	 * @brief Computes the cross product of two 3-dimensional vectors.
	 *
	 * @tparam T The type of elements in the vectors.
	 * @tparam N The size of the vectors (must be 3).
	 * @param vec1 The first vector.
	 * @param vec2 The second vector.
	 * @return The cross product of the two vectors.
	 * @throw static_assert if the size of the vectors is not 3.
	 */
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

	/**
	 * @brief Computes the cross product of two 3-dimensional N-dimensional vectors.
	 *
	 * @tparam T The type of elements in the vectors.
	 * @tparam N The size of the vectors (must be 3).
	 * @param vec1 The first vector.
	 * @param vec2 The second vector.
	 * @return The cross product of the two vectors.
	 * @throw static_assert if the size of the vectors is not 3.
	 */
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

	/**
	 * @brief Computes the norm of an N-dimensional vector.
	 *
	 * @tparam type The type of elements in the vector.
	 * @tparam size The size of the vector.
	 * @param data The vector.
	 * @return The norm of the vector.
	 */
	template<typename type, size_t size>
	type Norme(const myVectorND<type, size>& data)
	{
		type result = type{};
		for (auto it = data.begin(); it != data.end(); ++it)
		{
			result += (*it * *it);
		}
		return std::sqrt(result);
	};

	/**
	* @brief Computes the norm of a vector.
	*
	* @tparam type The type of elements in the vector.
	* @tparam size The size of the vector.
	* @param data The vector.
	* @return The norm of the vector.
	*/
	template<typename type, size_t size>
	type Norme(const myVector<type, size>& data)
	{
		type result = type{};
		for (auto it = data.begin(); it != data.end(); ++it)
		{
			result += (*it * *it);
		}
		return std::sqrt(result);
	};

	/**
	 * @brief Normalizes an N-dimensional vector.
	 *
	 * @tparam type The type of elements in the vector.
	 * @tparam size The size of the vector.
	 * @param data The vector to normalize.
	 * @return The normalized vector.
	 */
	template<typename type, size_t size>
	myVectorND<type, size> VectorNormalization(const myVectorND<type, size>& data)
	{
		myVectorND<type, size> result;
		type norme = Norme<type, size>(data);
		auto itresult = result.begin();
		for (auto it = data.begin(); it != data.end(); ++it)
		{
			*itresult = (*it / norme);
			++itresult;
		}
		return result;
	};

	/**
	 * @brief Normalizes a vector.
	 *
	 * @tparam type The type of elements in the vector.
	 * @tparam size The size of the vector.
	 * @param data The vector to normalize.
	 * @return The normalized vector.
	 */
	template<typename type, size_t size>
	myVector<type, size> VectorNormalization(const myVector<type, size>& data)
	{
		myVector<type, size> result;
		type norme = Norme<type, size>(data);
		auto itresult = result.begin();
		for (auto it = data.begin(); it != data.end(); ++it)
		{
			*itresult = (*it / norme);
			++itresult;
		}
		return result;
	};
};