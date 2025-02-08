/**
 * @file helper.h
 * @brief Implementation of a namespace with utility functions
 * @author Guillaume
 * @date 08/02/2025
 */

#pragma once
#include <vector>

namespace glg
{

    /**
     * @brief Copy elements from one range to another.
     *
     * @tparam InputIt Input iterator type.
     * @tparam OutputIt Output iterator type.
     * @param firstElem Iterator to the first element in the input range.
     * @param lastElem Iterator to the last element in the input range.
     * @param output Iterator to the first element in the output range.
     * @return OutputIt Iterator to the element past the last element copied.
     */
	template<class InputIt, class OutputIt>
	OutputIt copy(InputIt firstElem, InputIt lastElem, OutputIt output)
	{
		for (; firstElem != lastElem; (void)++firstElem, (void)++output)
			*output = *firstElem;

		return output;
	}

    /**
     * @brief Transform elements in a range using a specified operation.
     *
     * @tparam Input Input iterator type.
     * @tparam Output Output iterator type.
     * @tparam Op Unary operation type.
     * @param firstElem Iterator to the first element in the input range.
     * @param secondElem Iterator to the last element in the input range.
     * @param startOfElem Iterator to the first element in the output range.
     * @param operation Unary operation to apply to each element.
     * @return Output Iterator to the element past the last element transformed.
     */
	template<typename Input, typename Output, typename Op>
	Output transform(Input firstElem, Input secondElem, Output startOfElem, Op operation)
	{
		for (; firstElem != secondElem; ++startOfElem, ++firstElem)
			*startOfElem = operation(*firstElem);

		return startOfElem;
	}

    /**
     * @brief Move elements from one range to another.
     *
     * @tparam Input Input iterator type.
     * @tparam Output Output iterator type.
     * @param firstElem Iterator to the first element in the input range.
     * @param lastElem Iterator to the last element in the input range.
     * @param new_first Iterator to the first element in the output range.
     * @return Output Iterator to the element past the last element moved.
     */
	template<class Input, class Output>
	Output move(Input firstElem, Input lastElem, Output new_first)
	{
		for (; firstElem != lastElem; ++new_first, ++firstElem)
			*new_first = std::move(*firstElem);

		return new_first;
	}

    /**
     * @brief Move elements from one range to another in reverse order.
     *
     * @tparam firstIt Input iterator type.
     * @tparam secondIt Output iterator type.
     * @param firstElem Iterator to the first element in the input range.
     * @param lastElem Iterator to the last element in the input range.
     * @param new_last Iterator to the last element in the output range.
     * @return secondIt Iterator to the element past the last element moved.
     */
	template<class firstIt, class secondIt>
	secondIt move_backward(firstIt firstElem, firstIt lastElem, secondIt new_last)
	{
		while (firstElem != lastElem)
			*(--new_last) = std::move(*(--lastElem));

		return new_last;
	}

    /**
     * @brief Fill a range with a specified value.
     *
     * @tparam ForwardIt Forward iterator type.
     * @tparam T Value type.
     * @param first Iterator to the first element in the range.
     * @param last Iterator to the last element in the range.
     * @param value The value to fill the range with.
     */
	template<typename ForwardIt, typename T>
	void fill(ForwardIt first, ForwardIt last, const T& value)
	{
		for (; first != last; ++first)
			*first = value;
	}

    /**
     * @brief Swap the contents of two containers.
     *
     * @tparam Container Container type.
     * @param first The first container.
     * @param second The second container.
     */
	template<typename Container>
	void swap(Container& first, Container& second)
	{
		auto temp = first;
		first = second;
		second = temp;
	}

    /**
     * @brief Sort a range using insertion sort.
     *
     * @tparam Iterator Iterator type.
     * @param first Iterator to the first element in the range.
     * @param last Iterator to the last element in the range.
     */
    template<typename Iterator>
    void InsertionSort(Iterator first, Iterator last)
    {
        if (first == last) return;

        for (auto it = first; it != last; ++it)
        {
            auto key = *it;
            auto j = it;

            while (j != first)
            {
                auto prev = j;
                --prev;

                if (*prev <= key)
                    break;

                *j = *prev;
                j = prev;
            }
            *j = key;
        }
    }

    /**
     * @brief Sort a range using bubble sort.
     *
     * @tparam Iterator Iterator type.
     * @param first Iterator to the first element in the range.
     * @param last Iterator to the last element in the range.
     */
    template<typename Iterator>
    void BubbleSort(Iterator first, Iterator last)
    {
        if (first == last) return;

        bool swapped;
        do {
            swapped = false;
            auto current = first;
            auto next = current;
            ++next;

            while (next != last)
            {
                if (*current > *next)
                {
                    glg::swap(*current, *next);
                    swapped = true;
                }
                ++current;
                ++next;
            }

            auto prev = last;
            --prev;
            last = prev;

        } while (swapped);
    }

    /**
     * @brief Merge two sorted ranges into one sorted range.
     *
     * @tparam Iterator Iterator type.
     * @param first Iterator to the first element in the first range.
     * @param mid Iterator to the first element in the second range.
     * @param last Iterator to the last element in the second range.
     */
    template<typename Iterator>
    void merge(Iterator first, Iterator mid, Iterator last)
    {
        using ValueType = typename std::iterator_traits<Iterator>::value_type;
        std::vector<ValueType> temp;

        auto left = first;
        auto right = mid;

        while (left != mid && right != last)
        {
            if (*left <= *right)
            {
                temp.push_back(*left);
                ++left;
            }
            else
            {
                temp.push_back(*right);
                ++right;
            }
        }

        while (left != mid)
        {
            temp.push_back(*left);
            ++left;
        }

        while (right != last)
        {
            temp.push_back(*right);
            ++right;
        }

        auto it = first;
        for (const auto& val : temp)
        {
            *it = val;
            ++it;
        }
    }

    /**
     * @brief Sort a range using merge sort.
     *
     * @tparam Iterator Iterator type.
     * @param first Iterator to the first element in the range.
     * @param last Iterator to the last element in the range.
     */
    template<typename Iterator>
    void FusionSort(Iterator first, Iterator last)
    {
        auto distance = std::distance(first, last);
        if (distance <= 1) return;

        auto mid = first;
        std::advance(mid, distance / 2);

        FusionSort(first, mid);
        FusionSort(mid, last);
        merge(first, mid, last);
    }

    /**
     * @brief Sort a container using an appropriate sorting algorithm.
     *
     * @tparam Container Container type.
     * @param container The container to sort.
     */
    template<typename Container>
    void sort(Container& container)
    {
        auto size = std::distance(container.begin(), container.end());
        if (size <= 16)
            InsertionSort(container.begin(), container.end());
        else if (size <= 1000)
            BubbleSort(container.begin(), container.end());
        else
            FusionSort(container.begin(), container.end());
    }
};