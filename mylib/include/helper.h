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
		Container temp = first;
		first = second;
		second = temp;
	}

	template<typename Random>
	void InsertionSort(Random first, Random last)
	{
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

	template<typename Random>
	void BubbleSort(Random first, Random last)
	{
		bool swapped;
		do
		{
			swapped = false;
			for (auto it = first; it != last; ++it)
			{
				auto next = it;
				++next;
				if (next == last)
					break;
				if (*it > *next)
				{
					std::swap(*it, *next);
					swapped = true;
				}
			}
			if (last != first) 
			{
				--last;
			}
		} while (swapped);
	}

	template<typename Random>
	void merge(Random first, Random mid, Random last)
	{
		std::vector<typename std::iterator_traits<Random>::value_type> temp(std::distance(first, last));
		auto left = first;
		auto right = mid;
		auto mergeIt = temp.begin();

		while (left != mid && right != last)
		{
			if (*left <= *right)
			{
				*mergeIt = *left;
				++left;
			}
			else
			{
				*mergeIt = *right;
				++right;
			}
			++mergeIt;
		}

		while (left != mid)
		{
			*mergeIt = *left;
			++left;
			++mergeIt;
		}
		while (right != last)
		{
			*mergeIt = *right;
			++right;
			++mergeIt;
		}

		std::move(temp.begin(), temp.end(), first);
	}


	template<typename Random>
	void FusionSort(Random first, Random last)
	{
		auto size = std::distance(first, last);
		if (size <= 1) return;

		Random mid = first;
		std::advance(mid, size / 2);

		FusionSort(first, mid);
		FusionSort(mid, last);
		merge(first, mid, last);
	}

	template<typename Container>
	void sort(Container& container)
	{
		size_t size = container.size();
		if (size >= 100000)
			FusionSort(container.begin(), container.end());
		else if (size >= 10000)
			BubbleSort(container.begin(), container.end());
		else
			InsertionSort(container.begin(), container.end());
	}
};