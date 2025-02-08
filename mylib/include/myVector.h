/**
 * @file myVector.h
 * @brief Implementation of a vector with iterators and utility functions.
 * @author Guillaume
 * @date 08/02/2025
 */

#pragma once
#include <iterator>
#include <stdexcept>
#include "helper.h"

template<typename T, size_t N>
struct myVector
{
	class iterator
	{
	public:
		using iterator_category = std::random_access_iterator_tag;
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using pointer = T*;
		using reference = T&;

		iterator(pointer ptr) : m_ptr(ptr) {}

		reference operator*()
		{
			return *m_ptr;
		}
		pointer operator->()
		{
			return m_ptr;
		}

		// Random access operations
		iterator& operator+=(difference_type n)
		{
			m_ptr += n;
			return *this;
		}

		iterator operator+(difference_type n) const
		{
			iterator tmp = *this;
			return tmp += n;
		}

		iterator& operator-=(difference_type n)
		{
			m_ptr -= n;
			return *this;
		}

		iterator operator-(difference_type n) const
		{
			iterator tmp = *this;
			return tmp -= n;
		}

		difference_type operator-(const iterator& other) const
		{
			return m_ptr - other.m_ptr;
		}

		reference operator[](difference_type n) const
		{
			return *(*this + n);
		}

		iterator& operator++()
		{
			++m_ptr;
			return *this;
		}

		iterator& operator--()
		{
			--m_ptr;
			return *this;
		}

		iterator operator++(int)
		{
			iterator tmp = *this;
			++m_ptr;
			return tmp;
		}

		iterator operator--(int)
		{
			iterator tmp = *this;
			--m_ptr;
			return tmp;
		}

		friend bool operator==(const iterator& lhs, const iterator& rhs)
		{
			return lhs.m_ptr == rhs.m_ptr;
		}

		friend bool operator!=(const iterator& lhs, const iterator& rhs)
		{
			return lhs.m_ptr != rhs.m_ptr;
		}

		friend bool operator<(const iterator& lhs, const iterator& rhs)
		{
			return lhs.m_ptr < rhs.m_ptr;
		}

		friend bool operator>(const iterator& lhs, const iterator& rhs)
		{
			return rhs < lhs;
		}

		friend bool operator<=(const iterator& lhs, const iterator& rhs)
		{
			return !(rhs < lhs);
		}

		friend bool operator>=(const iterator& lhs, const iterator& rhs)
		{
			return !(lhs < rhs);
		}

	private:
		pointer m_ptr;
	};

	class const_iterator
	{
	public:
		using iterator_category = std::random_access_iterator_tag;
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using pointer = const T*;
		using reference = const T&;

		const_iterator(pointer ptr) : m_ptr(ptr) {}

		reference operator*() const
		{
			return *m_ptr;
		}

		pointer operator->() const
		{
			return m_ptr;
		}

		// Random access operations
		const_iterator& operator+=(difference_type n)
		{
			m_ptr += n;
			return *this;
		}

		const_iterator operator+(difference_type n) const
		{
			const_iterator tmp = *this;
			return tmp += n;
		}

		const_iterator& operator-=(difference_type n)
		{
			m_ptr -= n;
			return *this;
		}

		const_iterator operator-(difference_type n) const
		{
			const_iterator tmp = *this;
			return tmp -= n;
		}

		difference_type operator-(const const_iterator& other) const
		{
			return m_ptr - other.m_ptr;
		}

		reference operator[](difference_type n) const
		{
			return *(*this + n);
		}

		const_iterator& operator++()
		{
			++m_ptr;
			return *this;
		}

		const_iterator operator++(int)
		{
			const_iterator tmp = *this;
			++m_ptr;
			return tmp;
		}

		const_iterator& operator--()
		{
			--m_ptr;
			return *this;
		}

		const_iterator operator--(int)
		{
			const_iterator tmp = *this;
			--m_ptr;
			return tmp;
		}

		friend bool operator==(const const_iterator& lhs, const const_iterator& rhs)
		{
			return lhs.m_ptr == rhs.m_ptr;
		}

		friend bool operator!=(const const_iterator& lhs, const const_iterator& rhs)
		{
			return lhs.m_ptr != rhs.m_ptr;
		}

		friend bool operator<(const const_iterator& lhs, const const_iterator& rhs)
		{
			return lhs.m_ptr < rhs.m_ptr;
		}

		friend bool operator>(const const_iterator& lhs, const const_iterator& rhs)
		{
			return rhs < lhs;
		}

		friend bool operator<=(const const_iterator& lhs, const const_iterator& rhs)
		{
			return !(rhs < lhs);
		}

		friend bool operator>=(const const_iterator& lhs, const const_iterator& rhs)
		{
			return !(lhs < rhs);
		}

	private:
		pointer m_ptr;
	};

	template<typename T, size_t N>
	friend std::ostream& operator<<(std::ostream& os, const myVector<T, N>& vec);

	using value_type = T;
	using size_type = size_t;
	using difference_type = std::ptrdiff_t;
	using reference = value_type&;
	using const_reference = const value_type&;
	using pointer = value_type*;
	using const_pointer = const value_type*;
	using iterator = iterator;
	using const_iterator = const_iterator;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using reverse_const_iterator = std::reverse_iterator<const_iterator>;

	/// <summary>
	/// Constructor
	/// </summary>
	myVector()
	: m_data(new T[N])
	, m_size(0)
	, m_capacity(N) {}

	/// <summary>
	/// Copy constructor
	/// </summary>
	myVector(const myVector& newVector)
	: m_data(new value_type[newVector.m_capacity])
	, m_size(newVector.m_size)
	, m_capacity(newVector.m_capacity)
	{
		glg::copy(newVector.m_data, newVector.m_data + newVector.m_size, m_data);
	}

	/// <summary>
	/// Constructor with initializer_list
	/// </summary>
	myVector(std::initializer_list<T> init)
		: m_data(new T[N])
		, m_size(init.size())
		, m_capacity(N)
	{
		if (init.size() > N)
			throw std::out_of_range("Initializer list size exceeds vector capacity");

		glg::copy(init.begin(), init.end(), m_data);
	}

	/// <summary>
	/// Assignment operator
	/// </summary>
	myVector& operator=(const myVector& newVector)
	{
		if (this != &newVector)
		{
			delete[] m_data;
			m_data = new value_type[newVector.m_capacity];
			m_size = newVector.m_size;
			m_capacity = newVector.m_capacity;
			glg::copy(newVector.m_data, newVector.m_data + newVector.m_size, m_data);
		}
		return *this;
	}

	/// <summary>
	/// Destructor
	/// </summary>
	~myVector()
	{
		delete[] m_data;
		m_data = nullptr;
	}

	/// <summary>
	/// Capacity methods
	/// </summary>
	bool is_empty() const
	{
		if (m_size > 0)
			return false;

		return true;
	}

	/// <summary>
	/// Capacity methods
	/// </summary>
	size_type size() const
	{
		return m_size;
	}

	/// <summary>
	/// Capacity methods
	/// </summary>
	size_type capacity() const
	{
		return m_capacity;
	}

	/// <summary>
	/// Capacity methods
	/// </summary>
	void reserve(size_t new_capacity)
	{
		if (new_capacity > m_capacity)
		{
			value_type* new_data = new value_type[new_capacity];
			glg::copy(m_data, m_data + m_size, new_data);

			delete[] m_data;
			m_data = new_data;
			m_capacity = new_capacity;
		}
	}

	/// <summary>
	/// Capacity methods
	/// </summary>
	void resize(size_t new_size)
	{
		if (new_size > m_capacity)
			reserve(new_size);

		if (new_size > m_size)
		{
			for (size_t i = m_size; i < new_size; ++i)
			{
				m_data[i] = T{};
			}
		}

		m_size = new_size;
	}

	/// <summary>
	/// Iterators methods
	/// </summary>
	iterator begin()
	{
		return iterator(m_data);
	}
	/// <summary>
	/// Iterators methods
	/// </summary>
	const_iterator begin() const
	{
		return const_iterator(m_data);
	}

	/// <summary>
	/// Iterators methods
	/// </summary>
	iterator end()
	{
		return iterator(m_data + m_size);
	}
	/// <summary>
	/// Iterators methods
	/// </summary>
	const_iterator end() const
	{
		return const_iterator(m_data + m_size);
	}

	/// <summary>
	/// Element access methods
	/// </summary>
	T& front() const
	{
		if (is_empty())
			throw std::runtime_error("The vector is empty");

		return m_data[0];
	}

	/// <summary>
	/// Element access methods
	/// </summary>
	T& back() const
	{
		if (is_empty())
			throw std::runtime_error("The vector is empty");

		return m_data[m_size - 1];
	}

	/// <summary>
	/// Element access methods
	/// </summary>
	T& operator[](const size_t& data_idx)
	{
		return m_data[data_idx];
	}

	const T& operator[](const size_t& data_idx) const
	{
		return m_data[data_idx];
	}

	/// <summary>
	/// Modifiers
	/// </summary>
	void push_back(const T& value)
	{
		if (m_size >= m_capacity)
			reserve(m_capacity * 2);

		m_data[m_size] = value;
		++m_size;
	}

	/// <summary>
	/// Modifiers
	/// </summary>
	void pop_back()
	{
		if (is_empty())
			throw std::runtime_error("The vector is empty");

		--m_size;
	}

	/// <summary>
	/// Modifiers
	/// </summary>
	iterator insert(iterator index, const T& value)
	{
		if (index > end())
			throw std::out_of_range("Index out of range");

		if (m_size >= m_capacity)
			reserve(m_capacity * 2);

		glg::move_backward(index, end(), end() + 1);
		*index = value;
		++m_size;
		return index;
	}

	/// <summary>
	/// Modifiers
	/// </summary>
	iterator erase(iterator index)
	{
		if (index >= begin() && index < end()) 
		{
			for (auto it = index; it != end() - 1; ++it) 
			{
				*it = *(it + 1);
			}
			--m_size;
		}
		return index;
	}

	/// <summary>
	/// Modifiers
	/// </summary>
	void clear()
	{
		m_size = 0;
	}

	size_type max_size() const
	{
		return m_size;
	}

	void assign(size_t count, const T& value)
	{
		if (count > m_capacity)
			reserve(count);

		m_size = count;
		for (size_t i = 0; i < count; ++i)
		{
			m_data[i] = value;
		}
	}

	void assign(std::initializer_list<T> iList)
	{
		if (iList.size() > m_capacity)
			reserve(iList.size());

		m_size = 0;
		for (const auto& elem : iList)
		{
			m_data[m_size] = elem;
			++m_size;
		}
	}

	template<class Input>
	typename std::enable_if<!std::is_integral<Input>::value>::type
	assign(Input first, Input last)
	{
		m_size = 0;
		while (first != last && m_size < m_capacity)
		{
			m_data[m_size] = *first;
			++m_size;
			++first;
		}
	}

	reference at(size_type index)
	{
		if (index >= m_size)
			throw std::out_of_range("Index out of range");

		return m_data[index];
	}

	const_reference at(size_type index) const
	{
		if (index >= m_size)
			throw std::out_of_range("Index out of range");

		return m_data[index];
	}

	pointer data()
	{
		return m_data;
	}

	const_pointer data() const
	{
		return m_data;
	}

	reverse_iterator rbegin()
	{
		return reverse_iterator(m_data + m_size);
	}

	reverse_const_iterator rbegin() const
	{
		return reverse_const_iterator(m_data + m_size);
	}

	reverse_iterator rend()
	{
		return reverse_iterator(m_data);
	}

	reverse_const_iterator rend() const
	{
		return reverse_const_iterator(m_data);
	}

private:
	T* m_data;
	size_t m_size;
	size_t m_capacity;
};

template<typename T, size_t N>
std::ostream& operator<<(std::ostream& os, const myVector<T, N>& vec)
{
	if (vec.m_size == 0)
	{
		os << "Empty vector";
		return os;
	}

	os << "(";
	for (auto i = 0; i < vec.m_size - 1; ++i)
		os << vec.m_data[i] << ", ";

	os << vec.m_data[vec.m_size - 1] << ")";

	return os;
}
