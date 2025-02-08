/**
 * @file myVectorND.h
 * @brief Implementation of a vector of N-Dimensions
 * @author Guillaume (and thank you Kroktur for your help)
 * @date 08/02/2025
 */

#pragma once
#include <exception>
#include <initializer_list>
#include <sstream>
#include "myArray.h"
#include "helper.h"

 /**
  * @brief Custom vectorND implementation with fixed capacity
  * @tparam T Type of elements stored in the vector
  * @tparam N Maximum capacity of the vector
  */
template<typename type, size_t size>
struct myVectorND
{
public:
    using value_type = type;
    using pointer = type*;
    using const_pointer = const type*;
    using reference = type&;
    using const_reference = const type&;
    using reverse_iterator = myArray<type, size>::reverse_iterator;
    using const_reverse_iterator = myArray<type, size>::const_reverse_iterator;
    using iterator = myArray<type, size>::iterator;
    using const_iterator = myArray<type, size>::const_iterator;

    /**
     * @brief Initializer list constructor
     * @param list Initializer list of elements
     * @throw std::out_of_range if list size exceeds capacity
     */
    myVectorND(std::initializer_list<type> list)
    {
        if (list.size() > size)
            throw std::runtime_error("Out of Range");

        glg::copy(list.begin(), list.end(), m_data.data());
    	glg::fill((m_data.begin() + list.size()), m_data.end(), type());
    }

    /**
	* @brief Default constructor
	* Initializes all elements to default values.
	*/
    myVectorND()
    {
        glg::fill(m_data.begin(), m_data.end(), type());
    }

    /**
     * @brief Copy constructor
     * @param tab
	 * @throw std::out_of_range if size of tab does not match size
     */
    myVectorND(const myVectorND& tab)
    {
        if (tab.m_data.size() != size)
            throw std::runtime_error("size must be equal");

        glg::copy(tab.m_data.begin(), tab.m_data.end(), m_data.data());
    }
    /**
     * @brief Copy assignment operator
     * @param tab The vector to copy from
     * @return Reference to this vector
     * @throw std::out_of_range if sizes of vectors do not match
     */
    myVectorND& operator=(const myVectorND& tab)
    {
        if (m_data.size() != tab.m_data.size())
            throw std::out_of_range("size must be equal");

        if (this != &tab)
            std::copy(tab.m_data.begin(), tab.m_data.end(), m_data.data());

        return *this;
    }

    /**
     * @brief Subscript operator
     * @param idx Index of the element
     * @return Reference to the element at the specified index
     */
    reference operator[](const size_t& idx)
    {
        return m_data[idx];
    }

    /**
     * @brief Const subscript operator
     * @param idx Index of the element
     * @return Const reference to the element at the specified index
     */
    const_reference operator[](const size_t& idx) const
    {
        return m_data[idx];
    }

    /**
     * @brief Access element at specified index with bounds checking
     * @param idx Index of the element
     * @return Reference to the element at the specified index
     * @throw std::out_of_range if index is out of bounds
     */
    reference at(const size_t& idx)
    {
        if (idx >= size)
            throw std::out_of_range("Out of Range");

        return m_data[idx];
    }

    /**
     * @brief Access element at specified index with bounds checking
     * @param idx Index of the element
     * @return Const reference to the element at the specified index
     * @throw std::out_of_range if index is out of bounds
     */
    const_reference at(const size_t& idx) const
    {
        if (idx >= size)
            throw std::out_of_range("Out of Range");

        return m_data[idx];
    }

    /**
     * @brief Get the number of elements in the vector
     * @return Number of elements in the vector
     */
    size_t Size()
    {
        return m_data.Size();
    }

    /**
     * @brief Get the number of elements in the vector
     * @return Number of elements in the vector
     */
    const size_t Size() const
    {
        return m_data.size();
    }

    /**
     * @brief Check if the vector is empty
     * @return true if the vector is empty, false otherwise
     */
    bool Empty()
    {
        return m_data.empty();
    }

    /**
     * @brief Check if the vector is empty
     * @return true if the vector is empty, false otherwise
     */
    bool Empty() const
    {
        return  m_data.empty();
    }

    /**
     * @brief Get a pointer to the underlying data
     * @return Pointer to the underlying data
     */
    pointer data()
    {
        return m_data.data();
    }

    /**
     * @brief Get a const pointer to the underlying data
     * @return Const pointer to the underlying data
     */
    const_pointer data() const
    {
        return m_data.data();
    }

    /**
     * @brief Get an iterator to the beginning of the vector
     * @return Iterator to the beginning of the vector
     * @throw std::out_of_range if the vector is empty
     */
    iterator begin()
    {
        if (Empty())
            throw std::out_of_range("Array is empty");

        return iterator(data());
    }

    /**
     * @brief Get an iterator to the end of the vector
     * @return Iterator to the end of the vector
     * @throw std::out_of_range if the vector is empty
     */
    iterator end()
    {
        if (Empty())
            throw std::out_of_range("Array is empty");

        return iterator(data() + size);
    }

    /**
     * @brief Get a const iterator to the beginning of the vector
     * @return Const iterator to the beginning of the vector
     * @throw std::out_of_range if the vector is empty
     */
    const_iterator begin() const
    {
        if (Empty())
            throw std::out_of_range("Array is empty");

        return const_iterator(data());
    }

    /**
     * @brief Get a const iterator to the end of the vector
     * @return Const iterator to the end of the vector
     * @throw std::out_of_range if the vector is empty
     */
    const_iterator end() const
    {
        if (Empty())
            throw std::out_of_range("Array is empty");

        return const_iterator(data() + size);
    }

    /**
     * @brief Get a reverse iterator to the beginning of the reversed vector
     * @return Reverse iterator to the beginning of the reversed vector
     * @throw std::out_of_range if the vector is empty
     */
    reverse_iterator rbegin()
    {
        if (Empty())
            throw std::out_of_range("Array is empty");

        return reverse_iterator(data() + size - 1);
    }

    /**
     * @brief Get a reverse iterator to the end of the reversed vector
     * @return Reverse iterator to the end of the reversed vector
     * @throw std::out_of_range if the vector is empty
     */
    reverse_iterator rend()
    {
        if (Empty())
            throw std::out_of_range("Array is empty");

        return reverse_iterator(data() - 1);
    }

    /**
     * @brief Get a const reverse iterator to the beginning of the reversed vector
     * @return Const reverse iterator to the beginning of the reversed vector
     * @throw std::out_of_range if the vector is empty
     */
    const_reverse_iterator rbegin() const
    {
        if (Empty())
            throw std::out_of_range("Array is empty");

        return const_reverse_iterator(data() + size - 1);
    }

    /**
     * @brief Get a const reverse iterator to the end of the reversed vector
     * @return Const reverse iterator to the end of the reversed vector
     * @throw std::out_of_range if the vector is empty
     */
    const_reverse_iterator rend() const
    {
        if (Empty())
            throw std::out_of_range("Array is empty");

        return const_reverse_iterator(data() - 1);
    }

    /**
     * @brief Addition operator for vectors
     * @param data The vector to add
     * @return New vector with the result of the addition
     */
    myVectorND<type, size> operator+(const myVectorND<type, size>& data)
    {
        myVectorND<type, size> result;
        for (size_t i = 0; i < m_data.Size(); ++i)
        {
            result[i] = data[i] + m_data[i];
        }
        return result;
    }

    /**
     * @brief Subtraction operator for vectors
     * @param data The vector to subtract
     * @return New vector with the result of the subtraction
     */
    myVectorND<type, size> operator-(const myVectorND<type, size>& data)
    {
        myVectorND<type, size> result;
        for (size_t i = 0; i < m_data.Size(); ++i)
        {
            result[i] = data[i] - m_data[i];
        }
        return result;
    }

    /**
     * @brief Multiplication operator for vector and scalar
     * @param idx The scalar to multiply
     * @return New vector with the result of the multiplication
     */
    myVectorND<type, size> operator*(const int& idx)
    {
        myVectorND<type, size> result;
        for (size_t i = 0; i < m_data.Size(); ++i)
        {
            result[i] = m_data[i] * idx;
        }
        return result;
    }

    /**
     * @brief Division operator for vector and scalar
     * @param idx The scalar to divide
     * @return New vector with the result of the division
     * @throw std::runtime_error if division by zero is attempted
     */
    myVectorND<type, size> operator/(const int& idx)
    {
        if (idx == 0)
            throw std::runtime_error("cannot divide by 0");
        myVectorND<type, size> result;
        for (size_t i = 0; i < m_data.Size(); ++i)
        {
            result[i] = m_data[i] / idx;
        }
        return result;
    }

    /**
     * @brief Equality comparison operator
     * @param data The vector to compare
     * @return true if vectors are equal, false otherwise
     */
    bool operator ==(const myVectorND<type, size>& data)
    {
        for (size_t i = 0; i < m_data.size(); ++i)
        {
            if (data[i] != m_data[i])
                return false;
        }
        return true;
    }

    /**
     * @brief Inequality comparison operator
     * @param data The vector to compare
     * @return true if vectors are not equal, false otherwise
     */
    bool operator !=(const myVectorND<type, size>& data)
    {
        bool result;
        for (size_t i = 0; i < m_data.size(); ++i)
        {
            if (data[i] == m_data[i])
                result = false;
            else
                result = true;
        }
        return result;
    }

    /**
     * @brief Addition operator for vectors (const version)
     * @param data The vector to add
     * @return New vector with the result of the addition
     */
    myVectorND<type, size> operator+(const myVectorND<type, size>& data) const
    {
        myVectorND<type, size> result;
        for (size_t i = 0; i < m_data.size(); ++i)
        {
            result[i] = data[i] + m_data[i];
        }
        return result;
    }

    /**
     * @brief Subtraction operator for vectors (const version)
     * @param data The vector to subtract
     * @return New vector with the result of the subtraction
     */
    myVectorND<type, size> operator-(const myVectorND<type, size>& data) const
    {
        myVectorND<type, size> result;
        for (size_t i = 0; i < m_data.size(); ++i)
        {
            result[i] = data[i] - m_data[i];
        }
        return result;
    }

    /**
     * @brief Multiplication operator for vector and scalar (const version)
     * @param idx The scalar to multiply
     * @return New vector with the result of the multiplication
     */
    myVectorND<type, size> operator*(const int& idx) const
    {
        myVectorND<type, size> result;
        for (size_t i = 0; i < m_data.size(); ++i)
        {
            result[i] = m_data[i] * idx;
        }
        return result;
    }

    /**
     * @brief Division operator for vector and scalar (const version)
     * @param idx The scalar to divide
     * @return New vector with the result of the division
     * @throw std::runtime_error if division by zero is attempted
     */
    myVectorND<type, size> operator/(const int& idx) const
    {
        if (idx == 0)
            throw std::runtime_error("cannot divide by 0");

        myVectorND<type, size> result;
        for (size_t i = 0; i < m_data.Size(); ++i)
        {
            result[i] = m_data[i] / idx;
        }

        return result;
    }

    /**
     * @brief Equality comparison operator (const version)
     * @param data The vector to compare
     * @return true if vectors are equal, false otherwise
     */
    bool operator ==(const myVectorND<type, size>& data) const
    {
        for (size_t i = 0; i < m_data.Size(); ++i)
        {
            if (data[i] != m_data[i])
                return false;
        }
        return true;
    }

    /**
     * @brief Inequality comparison operator (const version)
     * @param data The vector to compare
     * @return true if vectors are not equal, false otherwise
     */
    bool operator !=(const myVectorND<type, size>& data) const
    {
        bool result;
        for (size_t i = 0; i < m_data.Size(); ++i)
        {
            if (data[i] == m_data[i])
                result = false;
            else
                result = true;
        }
        return result;
    }

    template<typename T, size_t N>
    friend std::ostream& operator<<(std::ostream& os, const myVectorND<T, N>& vec);

    private:
    myArray<type, size> m_data; /**< Underlying data storage */
};

/**
 * @brief Stream insertion operator for myVectorND
 * @tparam T Type of elements stored in the vector
 * @tparam N Maximum capacity of the vector
 * @param os The output stream
 * @param vec The vector to be inserted into the stream
 * @return std::ostream& The output stream
 */
template<typename T, size_t N>
std::ostream& operator<<(std::ostream& os, const myVectorND<T, N>& vec)
    {
        if (vec.Size() == 0)
        {
            os << "Empty vector";
            return os;
        }

        os << "(";
        for (auto i = 0; i < vec.Size() - 1; ++i)
            os << vec.m_data[i] << ", ";

        os << vec.m_data[vec.Size() - 1] << ")";

        return os;
    }