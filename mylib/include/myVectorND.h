#pragma once
#include <exception>
#include <initializer_list>
#include <sstream>
#include "myArray.h"
#include "helper.h"

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

    myVectorND(std::initializer_list<type> list)
    {
        if (list.size() > size)
            throw std::runtime_error("Out of Range");

        glg::copy(list.begin(), list.end(), m_data.data());
    	glg::fill((m_data.begin() + list.size()), m_data.end(), type());
    }
    myVectorND()
    {
        glg::fill(m_data.begin(), m_data.end(), type());
    }
    myVectorND(const myVectorND& tab)
    {
        if (tab.m_data.size() != size)
            throw std::runtime_error("size must be equal");

        glg::copy(tab.m_data.begin(), tab.m_data.end(), m_data.data());
    }
    myVectorND& operator=(const myVectorND& tab)
    {
        if (m_data.size() != tab.m_data.size())
            throw std::out_of_range("size must be equal");

        if (this != &tab)
            std::copy(tab.m_data.begin(), tab.m_data.end(), m_data.data());

        return *this;
    }
    reference operator[](const size_t& idx)
    {
        return m_data[idx];
    }
    const_reference operator[](const size_t& idx) const
    {
        return m_data[idx];
    }
    reference at(const size_t& idx)
    {
        if (idx >= size)
            throw std::out_of_range("Out of Range");

        return m_data[idx];
    }
    const_reference at(const size_t& idx) const
    {
        if (idx >= size)
            throw std::out_of_range("Out of Range");

        return m_data[idx];
    }
    size_t Size()
    {
        return m_data.Size();
    }
    const size_t Size() const
    {
        return m_data.size();
    }
    bool Empty()
    {
        return m_data.Empty();
    }
    bool Empty() const
    {
        return  m_data.Empty();
    }
    pointer data()
    {
        return m_data.data();
    }
    const_pointer data() const
    {
        return m_data.data();
    }
    iterator begin()
    {
        if (Empty())
            throw std::out_of_range("Array is empty");

        return iterator(data());
    }
    iterator end()
    {
        if (Empty())
            throw std::out_of_range("Array is empty");

        return iterator(data() + size);
    }
    const_iterator begin() const
    {
        if (Empty())
            throw std::out_of_range("Array is empty");

        return const_iterator(data());
    }
    const_iterator end() const
    {
        if (Empty())
            throw std::out_of_range("Array is empty");

        return const_iterator(data() + size);
    }

    reverse_iterator rbegin()
    {
        if (Empty())
            throw std::out_of_range("Array is empty");

        return reverse_iterator(data() + size - 1);
    }
    reverse_iterator rend()
    {
        if (Empty())
            throw std::out_of_range("Array is empty");

        return reverse_iterator(data() - 1);
    }
    const_reverse_iterator rbegin() const
    {
        if (Empty())
            throw std::out_of_range("Array is empty");

        return const_reverse_iterator(data() + size - 1);
    }
    const_reverse_iterator rend() const
    {
        if (Empty())
            throw std::out_of_range("Array is empty");

        return const_reverse_iterator(data() - 1);
    }

    myVectorND<type, size> operator+(const myVectorND<type, size>& data)
    {
        myVectorND<type, size> result;
        for (size_t i = 0; i < m_data.Size(); ++i)
        {
            result[i] = data[i] + m_data[i];
        }
        return result;
    }
    myVectorND<type, size> operator-(const myVectorND<type, size>& data)
    {
        myVectorND<type, size> result;
        for (size_t i = 0; i < m_data.Size(); ++i)
        {
            result[i] = data[i] - m_data[i];
        }
        return result;
    }
    myVectorND<type, size> operator*(const int& idx)
    {
        myVectorND<type, size> result;
        for (size_t i = 0; i < m_data.Size(); ++i)
        {
            result[i] = m_data[i] * idx;
        }
        return result;
    }
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
    bool operator ==(const myVectorND<type, size>& data)
    {
        for (size_t i = 0; i < m_data.size(); ++i)
        {
            if (data[i] != m_data[i])
                return false;
        }
        return true;
    }
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
    myVectorND<type, size> operator+(const myVectorND<type, size>& data) const
    {
        myVectorND<type, size> result;
        for (size_t i = 0; i < m_data.size(); ++i)
        {
            result[i] = data[i] + m_data[i];
        }
        return result;
    }
    myVectorND<type, size> operator-(const myVectorND<type, size>& data) const
    {
        myVectorND<type, size> result;
        for (size_t i = 0; i < m_data.size(); ++i)
        {
            result[i] = data[i] - m_data[i];
        }
        return result;
    }
    myVectorND<type, size> operator*(const int& idx) const
    {
        myVectorND<type, size> result;
        for (size_t i = 0; i < m_data.size(); ++i)
        {
            result[i] = m_data[i] * idx;
        }
        return result;
    }
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
    bool operator ==(const myVectorND<type, size>& data) const
    {
        for (size_t i = 0; i < m_data.Size(); ++i)
        {
            if (data[i] != m_data[i])
                return false;
        }
        return true;
    }
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
    myArray<type, size> m_data;
};

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