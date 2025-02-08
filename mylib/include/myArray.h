/**
 * @file myArray.h
 * @brief Implementation of a fixed-size array with iterators and utility functions.
 * @author Guillaume
 * @date 08/02/2025
 */

#pragma once
#include <initializer_list>
#include "helper.h"

 /**
  * @struct myArray
  * @brief Template class representing a fixed-size array with iterator support.
  * @tparam T Type of elements stored in the array.
  * @tparam N Size of the array.
  */
template<typename T, size_t N>
struct myArray
{
	template<typename Type, size_t Size>
	friend std::ostream& operator<<(std::ostream& os, const myArray<Type, Size>& tab);

    /**
     * @class iterator
     * @brief Random-access iterator for myArray.
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
         * @brief Constructor for iterator.
         * @param ptr Pointer to the array element.
         */
        iterator(pointer ptr) : m_ptr(ptr) {}

        // Dereference operators
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

        // Increment/decrement operators
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

        // Comparison operators
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
     * @class const_iterator
     * @brief Random-access const iterator for myArray.
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
         * @brief Constructor for const iterator.
         * @param ptr Pointer to the array element.
         */
        const_iterator(pointer ptr) : m_ptr(ptr) {}

        // Allow construction from non-const iterator
        const_iterator(const iterator& other) : m_ptr(other.operator->()) {}

        // Dereference operators
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

        // Increment/decrement operators
        const_iterator& operator++()
    	{
            ++m_ptr;
            return *this;
        }

        const_iterator& operator--()
    	{
            --m_ptr;
            return *this;
        }

        const_iterator operator++(int)
    	{
            const_iterator tmp = *this;
            ++m_ptr;
            return tmp;
        }

        const_iterator operator--(int)
    	{
            const_iterator tmp = *this;
            --m_ptr;
            return tmp;
        }

        // Comparison operators
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
        friend struct myArray;
    };

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
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    /**
     * @brief Default constructor initializes array with default values.
     */
	myArray()
	{
		glg::fill(begin(), end(), value_type{});
	}

    /**
	* @brief Constructor with initializer list.
	* @param list Initial values for the array.
	* @throws std::runtime_error if the size of the list does not match N.
	*/
	myArray(const std::initializer_list<value_type>& list)
	{
		if (list.size() != N)
			throw std::runtime_error("size is different");

		glg::copy(list.begin(), list.end(), m_data);
	}

    /**
     * @brief Copy constructor.
     * @param tab Another myArray to copy.
     */
	myArray(const myArray& tab)
	{
		glg::copy(tab.begin(), tab.end(), m_data);
	}

    /**
     * @brief Copy assignment operator.
     * @param tab Another myArray to copy.
     * @return Reference to the current instance.
     */
	myArray& operator=(const myArray& tab)
	{
		if (this != &tab)
			glg::copy(tab.begin(), tab.end(), m_data);

		return *this;
	}

    /**
     * @brief Access element at specified index without bounds checking.
     * @param index Position of the element.
     * @return Reference to the element.
     */
	reference operator[](const size_t& data_idx)
	{
		return m_data[data_idx];
	}

    /**
     * @brief Const version of operator[].
     * @param index Position of the element.
     * @return Const reference to the element.
     */
    const_reference operator[](const size_t& data_idx) const
    {
        return m_data[data_idx];
    }

    /**
     * @brief Returns an iterator to the beginning of the array.
     * @return iterator pointing to the first element.
     */
	iterator begin()
	{
		return m_data;
	}

	/**
	 * Const version of the begin() method
	 * @return 
	 */
	const_iterator begin() const
	{
		return m_data;
	}

    /**
    * @brief Returns an iterator to the end of the array.
    * @return iterator pointing past the last element.
    */
	iterator end()
	{
		return m_data + N;
	}

	/**
	 * Const version of the end() method
	 * @return 
	 */
	const_iterator end() const
	{
		return m_data + N;
	}

    /**
     * @brief Access element at specified index with bounds checking.
     * @param index Position of the element.
     * @return Reference to the element.
     * @throws std::out_of_range if index is out of bounds.
     */
	reference at(size_t pos)
	{
		if (pos >= N)
			throw std::out_of_range("Array index out of range");

		return m_data[pos];
	}

    /**
    * @brief Const version of at().
    * @param index Position of the element.
    * @return Const reference to the element.
    * @throws std::out_of_range if index is out of bounds.
    */
	const_reference at(size_t pos) const
	{
		if (pos >= N)
			throw std::out_of_range("Array index out of range");

		return m_data[pos];
	}

	/**
	 * @brief Returns a reference to the first element in the array
	 * @return m_data[0]
	 */
	reference front()
	{
		return m_data[0];
	}

	/**
	 * @brief Returns a const reference to the first element in the array
	 * @return m_data[0]
	 */
	const_reference front() const
	{
		return m_data[0];
	}

	/**
	 * @brief Returns a reference to the last element in the array.
	 * @return m_data[N - 1]
	 */
	reference back()
	{
		return m_data[N - 1];
	}

	/**
	 * @brief Returns a const reference to the last element in the array.
	 * @return m_data[N - 1]
	 */
	const_reference back() const
	{
		return m_data[N - 1];
	}

	/**
	 * @brief Returns a pointer to the underlying array.
	 * @return m_data
	 */
	pointer data()
	{
		return m_data;
	}

	/**
	 * @brief Returns a const pointer to the underlying array
	 * @return m_data
	 */
	const_pointer data() const
	{
		return m_data;
	}

	
	/**
	 * @brief Returns the empty array
	 * @return true (N = 0)
	 */
	bool empty() const
	{
		return N == 0;
	}

    /**
     * @brief Returns the size of the array.
     * @return Number of elements in the array.
     */
	size_type size() const
	{
		return N;
	}

	/**
	 * @brief Returns the maximum size of the array
	 * @return Number of elements in the array
	 */
	size_type max_size() const
	{
		return N;
	}

	/**
	 * @brief Returns the end of the array
	 * @return an iterator to the end of the array
	 */
	reverse_iterator rbegin()
	{
		return reverse_iterator(end());
	}

	/**
	 * @brief Returns the beginning of the array
	 * @return an iterator to the beginning of the array
	 */
	reverse_iterator rend()
	{
		return reverse_iterator(begin());
	}

	/**
	 * @brief Const version of rbegin()
	 * @return a const iterator to the end of the array
	 */
	const_reverse_iterator rbegin() const
	{
		return const_reverse_iterator(end());
	}

	/**
	 * @brief Const version of rend()
	 * @return a const iterator to the beginning of the array
	 */
	const_reverse_iterator rend() const
	{
		return const_reverse_iterator(begin());
	}


	/**
	 * @brief Returns the beginning of the array
	 * @return begin()
	 */
	const_iterator cbegin() const
	{
		return begin();
	}

	/**
	 * @brief Returns the end of the array
	 * @return end()
	 */
	const_iterator cend() const
	{
		return end();
	}

    /**
    * @brief Destructor.
    */
	~myArray() = default;

private:
	value_type m_data[N]; ///< Internal array storage.
};

/**
 * @brief Overloaded stream output operator for myArray.
 * @tparam Type Element type.
 * @tparam Size Array size.
 * @param os Output stream.
 * @param tab Array to print.
 * @return Modified output stream.
 */
template<typename Type, size_t Size>
std::ostream& operator<<(std::ostream& os, const myArray<Type, Size>& tab)
{
	os << "(";
	for (auto i = 0; i < tab.size() - 1; ++i)
		os << tab.m_data[i] << ", ";

	os << tab.m_data[tab.size() - 1] << ")";

	return os;
}
