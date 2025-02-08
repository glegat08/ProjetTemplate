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
	template<class InputIt, class OutputIt>
	OutputIt copy(InputIt firstElem, InputIt lastElem, OutputIt output)
	{
		for (; firstElem != lastElem; (void)++firstElem, (void)++output)
			*output = *firstElem;

		return output;
	}

	template<typename Input, typename Output, typename Op>
	Output transform(Input firstElem, Input secondElem, Output startOfElem, Op operation)
	{
		for (; firstElem != secondElem; ++startOfElem, ++firstElem)
			*startOfElem = operation(*firstElem);

		return startOfElem;
	}

	template<class Input, class Output>
	Output move(Input firstElem, Input lastElem, Output new_first)
	{
		for (; firstElem != lastElem; ++new_first, ++firstElem)
			*new_first = std::move(*firstElem);

		return new_first;
	}

	template<class firstIt, class secondIt>
	secondIt move_backward(firstIt firstElem, firstIt lastElem, secondIt new_last)
	{
		while (firstElem != lastElem)
			*(--new_last) = std::move(*(--lastElem));

		return new_last;
	}

	template<typename ForwardIt, typename T>
	void fill(ForwardIt first, ForwardIt last, const T& value)
	{
		for (; first != last; ++first)
			*first = value;
	}

	template<typename Container>
	void swap(Container& first, Container& second)
	{
		auto temp = first;
		first = second;
		second = temp;
	}

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