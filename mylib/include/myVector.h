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

 /**
  * @brief Custom vector implementation with fixed capacity
  * @tparam T Type of elements stored in the vector
  * @tparam N Maximum capacity of the vector
  */
template<typename T, size_t N>
struct myVector
{
	/**
	* @brief Iterator class for myVector
	* Provides random access iterator functionality
	*/
	class iterator
	{
	public:
		using iterator_category = std::random_access_iterator_tag;
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using pointer = T*;
		using reference = T&;

		/**
	   * @brief Constructs iterator pointing to specific element
	   * @param ptr Pointer to the element
	   */
		iterator(pointer ptr) : m_ptr(ptr) {}

		/**
		* @brief Dereference operator
		* @return Reference to the pointed element
		*/
		reference operator*()
		{
			return *m_ptr;
		}
		/**
		 * @brief Arrow operator for member access
		 * @return Pointer to the element
		 */
		pointer operator->()
		{
			return m_ptr;
		}

		/**
		* @brief Compound addition assignment operator
		* @param n Number of positions to advance
		* @return Reference to this iterator
		*/
		iterator& operator+=(difference_type n)
		{
			m_ptr += n;
			return *this;
		}

		/**
		* @brief Addition operator
		* @param n Number of positions to advance
		* @return New iterator at the advanced position
		*/
		iterator operator+(difference_type n) const
		{
			iterator tmp = *this;
			return tmp += n;
		}

		/**
		* @brief Compound subtraction assignment operator
		* @param n Number of positions to move backward
		* @return Reference to this iterator
		*/
		iterator& operator-=(difference_type n)
		{
			m_ptr -= n;
			return *this;
		}

		/**
		* @brief Subtraction operator
		* @param n Number of positions to move backward
		* @return New iterator at the moved position
		*/
		iterator operator-(difference_type n) const
		{
			iterator tmp = *this;
			return tmp -= n;
		}

		/**
		* @brief Distance operator between iterators
		* @param other Iterator to calculate distance to
		* @return Distance between iterators
		*/
		difference_type operator-(const iterator& other) const
		{
			return m_ptr - other.m_ptr;
		}

		/**
		* @brief Array subscript operator
		* @param n Index offset
		* @return Reference to element at offset position
		*/
		reference operator[](difference_type n) const
		{
			return *(*this + n);
		}

		/**
		 * @brief Pre-increment operator
		 * @return Reference to this iterator
		 */
		iterator& operator++()
		{
			++m_ptr;
			return *this;
		}

		/**
		 * @brief Pre-decrement operator
		 * @return Reference to this iterator
		 */
		iterator& operator--()
		{
			--m_ptr;
			return *this;
		}

		/**
		 * @brief Post-increment operator
		 * @return Iterator to previous position
		 */
		iterator operator++(int)
		{
			iterator tmp = *this;
			++m_ptr;
			return tmp;
		}

		/**
		 * @brief Post-decrement operator
		 * @return Iterator to previous position
		 */
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

	/**
	 * @brief Const iterator class for myVector
	 * Provides read-only random access iterator functionality
	 */
	class const_iterator
	{
	public:
		using iterator_category = std::random_access_iterator_tag;
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using pointer = const T*;
		using reference = const T&;

		/**
		 * @brief Constructs const_iterator pointing to specific element
		 * @param ptr Pointer to the element
		 */
		const_iterator(pointer ptr) : m_ptr(ptr) {}

		/**
		 * @brief Dereference operator
		 * @return Const reference to the pointed element
		 */
		reference operator*() const
		{
			return *m_ptr;
		}

		/**
		* @brief Arrow operator for member access
		* @return Const pointer to the element
		*/
		pointer operator->() const
		{
			return m_ptr;
		}

		// SAME THING AS ITERATOR CLASS
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

	/**
	 * @brief Default constructor
	 * Initializes an empty vector with capacity N
	 */
	myVector()
	: m_data(new T[N])
	, m_size(0)
	, m_capacity(N) {}

	/**
	* @brief Copy constructor
	* @param newVector Vector to copy from
	*/
	myVector(const myVector& newVector)
	: m_data(new value_type[newVector.m_capacity])
	, m_size(newVector.m_size)
	, m_capacity(newVector.m_capacity)
	{
		glg::copy(newVector.m_data, newVector.m_data + newVector.m_size, m_data);
	}

	/**
	 * @brief Initializer list constructor
	 * @param init Initializer list of elements
	 * @throw std::out_of_range if init size exceeds capacity
	 */
	myVector(std::initializer_list<T> init)
		: m_data(new T[N])
		, m_size(init.size())
		, m_capacity(N)
	{
		if (init.size() > N)
			throw std::out_of_range("Initializer list size exceeds vector capacity");

		glg::copy(init.begin(), init.end(), m_data);
	}

	/**
	* @brief Assignment operator
	* @param newVector Vector to assign from
	* @return Reference to this vector
	*/
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

	/**
	 * @brief Destructor
	 * Deallocates the internal array
	 */
	~myVector()
	{
		delete[] m_data;
		m_data = nullptr;
	}

	/**
	 * @brief Checks if the vector is empty
	 * @return true if the vector is empty, false otherwise
	 */
	bool is_empty() const
	{
		if (m_size > 0)
			return false;

		return true;
	}

	/**
	* @brief Returns the current size of the vector
	* @return Number of elements in the vector
	*/
	size_type size() const
	{
		return m_size;
	}

	/**
	* @brief Returns the current capacity of the vector
	* @return Maximum number of elements that can be stored
	*/
	size_type capacity() const
	{
		return m_capacity;
	}

	/**
	 * @brief Reserves memory for specified number of elements
	 * @param new_capacity New capacity to reserve
	 */
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

	/**
	* @brief Resizes the vector to contain specified number of elements
	* @param new_size New size of the vector
	*/
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

	/**
	 * @brief Returns iterator to beginning
	 * @return Iterator pointing to first element
	 */
	iterator begin()
	{
		return iterator(m_data);
	}

	/**
	 * @brief Returns const iterator to beginning
	 * @return Const iterator pointing to first element
	 */
	const_iterator begin() const
	{
		return const_iterator(m_data);
	}

	/**
	 * @brief Returns iterator to end
	 * @return Iterator pointing to past-the-end element
	 */
	iterator end()
	{
		return iterator(m_data + m_size);
	}

	/**
	 * @brief Returns const iterator to end
	 * @return Const iterator pointing to past-the-end element
	 */
	const_iterator end() const
	{
		return const_iterator(m_data + m_size);
	}

	/**
	 * @brief Access first element
	 * @return Reference to first element
	 * @throw std::runtime_error if vector is empty
	 */
	T& front() const
	{
		if (is_empty())
			throw std::runtime_error("The vector is empty");

		return m_data[0];
	}

	/**
	 * @brief Access last element
	 * @return Reference to last element
	 * @throw std::runtime_error if vector is empty
	 */
	T& back() const
	{
		if (is_empty())
			throw std::runtime_error("The vector is empty");

		return m_data[m_size - 1];
	}

	/**
	 * @brief Subscript operator
	 * @param data_idx Index of element to access
	 * @return Reference to element at specified position
	 */
	T& operator[](const size_t& data_idx)
	{
		return m_data[data_idx];
	}

	/**
	* @brief Const subscript operator
	* @param data_idx Index of element to access
	* @return Const reference to element at specified position
	*/
	const T& operator[](const size_t& data_idx) const
	{
		return m_data[data_idx];
	}

	/**
	 * @brief Adds element to end
	 * @param value Element to add
	 */
	void push_back(const T& value)
	{
		if (m_size >= m_capacity)
			reserve(m_capacity * 2);

		m_data[m_size] = value;
		++m_size;
	}

	/**
	 * @brief Removes last element
	 * @throw std::runtime_error if vector is empty
	 */
	void pop_back()
	{
		if (is_empty())
			throw std::runtime_error("The vector is empty");

		--m_size;
	}

	/**
	 * @brief Inserts element at specified position
	 * @param index Iterator to insertion position
	 * @param value Element to insert
	 * @return Iterator pointing to inserted element
	 * @throw std::out_of_range if index is out of range
	 */
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

	/**
	* @brief Erases element at specified position
	* @param index Iterator to element to erase
	* @return Iterator pointing to new element at same position
	*/
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

	/**
	 * @brief Clears the contents
	 */
	void clear()
	{
		m_size = 0;
	}

	/**
	* @brief Returns the maximum size possible
	* @return Maximum number of elements that can be stored
	*/
	size_type max_size() const
	{
		return m_size;
	}

	/**
	 * @brief Assigns new contents to the vector
	 * @param count Number of elements to assign
	 * @param value Value to assign to each element
	 */
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

	/**
	 * @brief Assigns new contents from initializer list
	 * @param iList Initializer list to assign from
	 */
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

	/**
	 * @brief Assigns new contents from range
	 * @tparam Input Iterator type
	 * @param first Iterator to start of range
	 * @param last Iterator to end of range
	 */
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

	/**
	 * @brief Access element at specified index with bounds checking
	 * @param index Position of element to access
	 * @return Reference to element at specified position
	 * @throw std::out_of_range if index is out of range
	 */
	reference at(size_type index)
	{
		if (index >= m_size)
			throw std::out_of_range("Index out of range");

		return m_data[index];
	}

	/**
	 * @brief Access element at specified index with bounds checking
	 * @param index Position of element to access
	 * @return Const reference to element at specified position
	 * @throw std::out_of_range if index is out of range
	 */
	const_reference at(size_type index) const
	{
		if (index >= m_size)
			throw std::out_of_range("Index out of range");

		return m_data[index];
	}

	/**
	 * @brief Direct access to underlying array
	 * @return Pointer to underlying array
	 */
	pointer data()
	{
		return m_data;
	}

	/**
	 * @brief Direct access to underlying array
	 * @return Const pointer to underlying array
	 */
	const_pointer data() const
	{
		return m_data;
	}

	/**
	 * @brief Returns reverse iterator to reverse beginning
	 * @return Reverse iterator pointing to last element
	 */
	reverse_iterator rbegin()
	{
		return reverse_iterator(m_data + m_size);
	}

	/**
	 * @brief Returns const reverse iterator to reverse beginning
	 * @return Const reverse iterator pointing to last element
	 */
	reverse_const_iterator rbegin() const
	{
		return reverse_const_iterator(m_data + m_size);
	}

	/**
	 * @brief Returns reverse iterator to reverse end
	 * @return Reverse iterator pointing to theoretical element preceding first element
	 */
	reverse_iterator rend()
	{
		return reverse_iterator(m_data);
	}

	/**
	 * @brief Returns const reverse iterator to reverse end
	 * @return Const reverse iterator pointing to theoretical element preceding first element
	 */
	reverse_const_iterator rend() const
	{
		return reverse_const_iterator(m_data);
	}

private:
	T* m_data;        ///< Pointer to the underlying array
	size_t m_size;    ///< Current number of elements
	size_t m_capacity;///< Current capacity of the array
};

/**
 * @brief Output stream operator for myVector
 * @param os Output stream to write to
 * @param vec Vector to output
 * @return Reference to the output stream
 */
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
