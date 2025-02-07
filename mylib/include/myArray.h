

#pragma once
#include <initializer_list>
#include "helper.h"

template<typename T, size_t N>
struct myArray
{
	template<typename Type, size_t Size>
	friend std::ostream& operator<<(std::ostream& os, const myArray<Type, Size>& tab);

    class iterator
	{
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        // Constructor
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

    // Custom const_iterator class
    class const_iterator
	{
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        // Constructor
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
	 * Default constructor
	 */
	myArray()
	{
		glg::fill(begin(), end(), value_type{});
	}

	/**
	 * Constructor with an initializer list
	 * @param list 
	 */
	myArray(const std::initializer_list<value_type>& list)
	{
		if (list.size() != N)
			throw std::runtime_error("size is different");

		glg::copy(list.begin(), list.end(), m_data);
	}

	/**
	 * Copy constructor
	 * @param tab 
	 */
	myArray(const myArray& tab)
	{
		glg::copy(tab.begin(), tab.end(), m_data);
	}

	myArray& operator=(const myArray& tab)
	{
		if (this != &tab)
			glg::copy(tab.begin(), tab.end(), m_data);

		return *this;
	}

	reference operator[](const size_t& data_idx)
	{
		return m_data[data_idx];
	}

    const_reference operator[](const size_t& data_idx) const
    {
        return m_data[data_idx];
    }

	/**
	 * Return the first element of the array
	 * @return m_data
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
	 * Return the last element of the array
	 * @return m_data + N
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
	 * 
	 * @param pos 
	 * @return m_data[pos]
	 */
	reference at(size_t pos)
	{
		if (pos >= N)
			throw std::out_of_range("Array index out of range");

		return m_data[pos];
	}

	const_reference at(size_t pos) const
	{
		if (pos >= N)
			throw std::out_of_range("Array index out of range");

		return m_data[pos];
	}

	reference front()
	{
		return m_data[0];
	}
	const_reference front() const
	{
		return m_data[0];
	}

	reference back()
	{
		return m_data[N - 1];
	}
	const_reference back() const
	{
		return m_data[N - 1];
	}

	pointer data()
	{
		return m_data;
	}
	const_pointer data() const
	{
		return m_data;
	}

	// Capacity methods
	bool empty() const
	{
		return N == 0;
	}

	size_type size() const
	{
		return N;
	}

	size_type max_size() const
	{
		return N;
	}

	// New iterator methods
	reverse_iterator rbegin()
	{
		return reverse_iterator(end());
	}
	reverse_iterator rend()
	{
		return reverse_iterator(begin());
	}
	const_reverse_iterator rbegin() const
	{
		return const_reverse_iterator(end());
	}
	const_reverse_iterator rend() const
	{
		return const_reverse_iterator(begin());
	}

	const_iterator cbegin() const
	{
		return begin();
	}
	const_iterator cend() const
	{
		return end();
	}

	~myArray() = default;

private:
	value_type m_data[N];
};

template<typename Type, size_t Size>
std::ostream& operator<<(std::ostream& os, const myArray<Type, Size>& tab)
{
	os << "(";
	for (auto i = 0; i < tab.size() - 1; ++i)
		os << tab.m_data[i] << ", ";

	os << tab.m_data[tab.size() - 1] << ")";

	return os;
}
