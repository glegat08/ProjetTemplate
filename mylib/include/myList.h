//#pragma once
//#include <iterator>
//#include <stdexcept>
//#include "helper.h"
//
//template<typename T, size_t N>
//struct myList
//{
//    class iterator
//	{
//    public:
//        using iterator_category = std::bidirectional_iterator_tag;
//        using value_type = T;
//        using difference_type = std::ptrdiff_t;
//        using pointer = T*;
//        using reference = T&;
//
//        iterator(pointer ptr) : m_ptr(ptr) {}
//
//        reference operator*()
//        {
//            return *m_ptr;
//        }
//        pointer operator->()
//        {
//            return m_ptr;
//        }
//
//        // Random access operations
//        iterator& operator+=(difference_type n)
//        {
//            m_ptr += n;
//            return *this;
//        }
//
//        iterator operator+(difference_type n) const
//        {
//            iterator tmp = *this;
//            return tmp += n;
//        }
//
//        iterator& operator-=(difference_type n)
//        {
//            m_ptr -= n;
//            return *this;
//        }
//
//        iterator operator-(difference_type n) const
//        {
//            iterator tmp = *this;
//            return tmp -= n;
//        }
//
//        difference_type operator-(const iterator& other) const
//        {
//            return m_ptr - other.m_ptr;
//        }
//
//        reference operator[](difference_type n) const
//        {
//            return *(*this + n);
//        }
//
//        iterator& operator++()
//        {
//            ++m_ptr;
//            return *this;
//        }
//
//        iterator& operator--()
//        {
//            --m_ptr;
//            return *this;
//        }
//
//        iterator operator++(int)
//        {
//            iterator tmp = *this;
//            ++m_ptr;
//            return tmp;
//        }
//
//        iterator operator--(int)
//        {
//            iterator tmp = *this;
//            --m_ptr;
//            return tmp;
//        }
//
//        friend bool operator==(const iterator& lhs, const iterator& rhs)
//        {
//            return lhs.m_ptr == rhs.m_ptr;
//        }
//
//        friend bool operator!=(const iterator& lhs, const iterator& rhs)
//        {
//            return lhs.m_ptr != rhs.m_ptr;
//        }
//
//        friend bool operator<(const iterator& lhs, const iterator& rhs)
//        {
//            return lhs.m_ptr < rhs.m_ptr;
//        }
//
//        friend bool operator>(const iterator& lhs, const iterator& rhs)
//        {
//            return rhs < lhs;
//        }
//
//        friend bool operator<=(const iterator& lhs, const iterator& rhs)
//        {
//            return !(rhs < lhs);
//        }
//
//        friend bool operator>=(const iterator& lhs, const iterator& rhs)
//        {
//            return !(lhs < rhs);
//        }
//
//    private:
//        pointer m_ptr;
//    };
//
//    class const_iterator
//	{
//    public:
//        using iterator_category = std::bidirectional_iterator_tag;
//        using value_type = T;
//        using difference_type = std::ptrdiff_t;
//        using pointer = const T*;
//        using reference = const T&;
//
//        const_iterator(pointer ptr) : m_ptr(ptr) {}
//
//        reference operator*() const
//        {
//            return *m_ptr;
//        }
//
//        pointer operator->() const
//        {
//            return m_ptr;
//        }
//
//        // Random access operations
//        const_iterator& operator+=(difference_type n)
//        {
//            m_ptr += n;
//            return *this;
//        }
//
//        const_iterator operator+(difference_type n) const
//        {
//            const_iterator tmp = *this;
//            return tmp += n;
//        }
//
//        const_iterator& operator-=(difference_type n)
//        {
//            m_ptr -= n;
//            return *this;
//        }
//
//        const_iterator operator-(difference_type n) const
//        {
//            const_iterator tmp = *this;
//            return tmp -= n;
//        }
//
//        difference_type operator-(const const_iterator& other) const
//        {
//            return m_ptr - other.m_ptr;
//        }
//
//        reference operator[](difference_type n) const
//        {
//            return *(*this + n);
//        }
//
//        const_iterator& operator++()
//        {
//            ++m_ptr;
//            return *this;
//        }
//
//        const_iterator operator++(int)
//        {
//            const_iterator tmp = *this;
//            ++m_ptr;
//            return tmp;
//        }
//
//        const_iterator& operator--()
//        {
//            --m_ptr;
//            return *this;
//        }
//
//        const_iterator operator--(int)
//        {
//            const_iterator tmp = *this;
//            --m_ptr;
//            return tmp;
//        }
//
//        friend bool operator==(const const_iterator& lhs, const const_iterator& rhs)
//        {
//            return lhs.m_ptr == rhs.m_ptr;
//        }
//
//        friend bool operator!=(const const_iterator& lhs, const const_iterator& rhs)
//        {
//            return lhs.m_ptr != rhs.m_ptr;
//        }
//
//        friend bool operator<(const const_iterator& lhs, const const_iterator& rhs)
//        {
//            return lhs.m_ptr < rhs.m_ptr;
//        }
//
//        friend bool operator>(const const_iterator& lhs, const const_iterator& rhs)
//        {
//            return rhs < lhs;
//        }
//
//        friend bool operator<=(const const_iterator& lhs, const const_iterator& rhs)
//        {
//            return !(rhs < lhs);
//        }
//
//        friend bool operator>=(const const_iterator& lhs, const const_iterator& rhs)
//        {
//            return !(lhs < rhs);
//        }
//
//    private:
//        pointer m_ptr;
//    };
//
//
//    myList() : m_size(0) {}
//
//	myList(std::initializer_list <T> list) : m_size(list.size())
//	{
//		glg::copy(list.begin(), list.end(), m_data);
//	}
//
//    void push_front(const T& value)
//	{
//        if (m_size >= N)
//            throw std::runtime_error("List is full");
//
//        glg::move_backward(m_data, m_data + m_size, m_data + m_size + 1);
//        m_data[0] = value;
//        ++m_size;
//    }
//
//    void push_back(const T& value)
//	{
//        if (m_size <= N)
//            throw std::runtime_error("List is full");
//
//        m_data[++m_size] = value;
//    }
//
//    void pop_front()
//	{
//        if (m_size == 0)
//            throw std::runtime_error("List is empty");
//
//        glg::move(m_data + 1, m_data + m_size, m_data);
//        --m_size;
//    }
//
//    void pop_back()
//	{
//        if (m_size == 0)
//            throw std::runtime_error("List is empty");
//
//        --m_size;
//    }
//
//    reference front()
//	{
//        if (m_size == 0)
//            throw std::runtime_error("List is empty");
//
//        return m_data[0];
//    }
//
//    reference back()
//	{
//        if (m_size == 0)
//            throw std::runtime_error("List is empty");
//
//        return m_data[m_size - 1];
//    }
//
//    size_type size() const
//    {
//	    return m_size;
//    }
//
//    bool empty() const
//    {
//	    return m_size == 0;
//    }
//
//    bool full() const
//    {
//	    return m_size == N;
//    }
//
//    void clear()
//    {
//	    m_size = 0;
//    }
//
//    iterator begin()
//    {
//	    return iterator(m_data);
//    }
//    const_iterator begin() const
//    {
//	    return const_iterator(m_data);
//    }
//
//    iterator end()
//    {
//	    return iterator(m_data + m_size);
//    }
//    const_iterator end() const
//    {
//	    return const_iterator(m_data + m_size);
//    }
//
//    size_type max_size() const
//    {
//        return m_size;
//    }
//

//
//    pointer data()
//    {
//        return m_data;
//    }
//
//    const_pointer data() const
//    {
//        return m_data;
//    }
//
//
//	iterator insert(iterator pos, const T& value)
//    {
//		if (pos == end())
//		{
//			push_back(value);
//			return end() - 1;
//		}
//		else
//		{
//			iterator it = end();
//			while (it != pos)
//			{
//				*it = *(it - 1);
//				--it;
//			}
//			*pos = value;
//			++m_size;
//			return pos;
//		}
//    }
//
//    iterator erase(iterator pos)
//    {
//        if (pos == end())
//            return end();
//
//        iterator next = pos;
//        ++next;
//        while (next != end())
//        {
//            *pos = *next;
//            ++pos;
//            ++next;
//        }
//        --m_size;
//
//        return pos;
//    }
//

//
//    size_type getSize() const
//    {
//        return m_size;
//    }
//
//
//    template<typename T, size_t N>
//	friend std::ostream& operator<<(std::ostream& os, const myList<T, N>& vec);
//
//private:
//    T m_data[N];
//    size_t m_size;
//};
//
//template<typename T, size_t N>
//std::ostream& operator<<(std::ostream& os, const myList<T, N>& list)
//{
//    if (list.getSize() == 0)
//    {
//        os << "Empty list";
//        return os;
//    }
//
//    os << "(";
//    for (auto i = 0; i < list.getSize() - 1; ++i)
//        os << list.m_data[i] << ", ";
//
//    os << list.m_data[list.getSize() - 1] << ")";
//
//    return os;
//}

#pragma once
#include <iterator>
#include <stdexcept>

template<typename T>
struct myList
{
    struct Node
    {
        T data;
        Node* prev;
        Node* next;

        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };

    class iterator
	{
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        iterator(Node* node) : m_node(node) {}

        reference operator*()
        {
	        return m_node->data;
        }
        pointer operator->()
        {
	        return &m_node->data;
        }

        iterator& operator++()
    	{
            m_node = m_node->next;
            return *this;
        }

        iterator operator++(int)
    	{
            iterator tmp = *this;
            m_node = m_node->next;
            return tmp;
        }

        iterator& operator--()
        {
            if (m_node != nullptr)
            {
                m_node = m_node->prev;
            }
            return *this;
        }

        iterator operator--(int)
    	{
            iterator tmp = *this;
            m_node = m_node->prev;
            return tmp;
        }

        friend bool operator==(const iterator& lhs, const iterator& rhs)
    	{
            return lhs.m_node == rhs.m_node;
        }

        friend bool operator!=(const iterator& lhs, const iterator& rhs)
    	{
            return !(lhs == rhs);
        }

        friend class myList;

    private:
        Node* m_node;
    };

    class const_iterator
    {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        const_iterator(Node* node) : m_node(node) {}

        reference operator*()
        {
	        return m_node->data;
        }
        pointer operator->()
        {
	        return &m_node->data;
        }

        const_iterator& operator++()
    	{
            m_node = m_node->next;
            return *this;
        }

        const_iterator operator++(int)
    	{
            const_iterator tmp = *this;
            m_node = m_node->next;
            return tmp;
        }

        const_iterator& operator--()
    	{
            m_node = m_node->prev;
            return *this;
        }

        const_iterator operator--(int)
    	{
            const_iterator tmp = *this;
            m_node = m_node->prev;
            return tmp;
        }

        friend bool operator==(const const_iterator& lhs, const const_iterator& rhs)
    	{
            return lhs.m_node == rhs.m_node;
        }

        friend bool operator!=(const const_iterator& lhs, const const_iterator& rhs)
    	{
            return !(lhs == rhs);
        }

        friend class myList;

    private:
        Node* m_node;
    };


	using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using iterator = iterator;
    using const_iterator = const_iterator;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using reverse_const_iterator = std::reverse_iterator<const_iterator>;

    myList() : m_start(nullptr), m_end(nullptr), m_size(0) {}

    myList(std::initializer_list<T> init) : myList()
	{
        for (const auto& value : init) 
        {
            push_back(value);
        }
    }

    ~myList()
	{
        clear();
    }

    myList(const myList& other) : myList()
	{
        for (Node* curr = other.m_start; curr != nullptr; curr = curr->next) 
        {
            push_back(curr->data);
        }
    }

    myList& operator=(const myList& other)
	{
        if (this != &other) 
        {
            clear();
            for (Node* curr = other.m_start; curr != nullptr; curr = curr->next)
            {
                push_back(curr->data);
            }
        }
        return *this;
    }

    void push_front(const T& value)
	{
        Node* new_node = new Node(value);
        if (empty())
            m_start = m_end = new_node;
        else 
        {
            new_node->next = m_start;
            m_start->prev = new_node;
            m_start = new_node;
        }
        ++m_size;
    }

    void push_back(const T& value)
	{
        Node* new_node = new Node(value);
        if (empty())
            m_start = m_end = new_node;
        else 
        {
            new_node->prev = m_end;
            m_end->next = new_node;
            m_end = new_node;
        }

        ++m_size;
    }

    void pop_front()
	{
        if (empty()) 
            throw std::runtime_error("List is empty");

        Node* old_head = m_start;
        m_start = m_start->next;

        if (m_start)
            m_start->prev = nullptr;
        else
            m_end = nullptr;

        delete old_head;
        --m_size;
    }

    void pop_back()
	{
        if (empty()) 
            throw std::runtime_error("List is empty");

        Node* old_tail = m_end;
        m_end = m_end->prev;

        if (m_end) 
            m_end->next = nullptr;
        else
            m_start = nullptr;

        delete old_tail;
        --m_size;
    }

    iterator insert(iterator pos, const T& value)
	{
        if (pos.m_node == m_start) 
        {
            push_front(value);
            return iterator(m_start);
        }

        Node* new_node = new Node(value);
        Node* curr = pos.m_node;

        new_node->prev = curr->prev;
        new_node->next = curr;
        curr->prev->next = new_node;
        curr->prev = new_node;

        ++m_size;
        return iterator(new_node);
    }

    iterator erase(iterator pos)
	{
        Node* curr = pos.m_node;
        Node* next = curr->next;

        if (curr == m_start) 
        {
            pop_front();
            return iterator(m_start);
        }
        if (curr == m_end) 
        {
            pop_back();
            return iterator(nullptr);
        }

        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        delete curr;
        --m_size;

        return iterator(next);
    }

    void clear()
	{
        while (!empty()) 
        {
            pop_front();
        }
    }

    T& front()
	{
        if (empty()) 
            throw std::runtime_error("List is empty");

        return m_start->data;
    }

    const T& front() const
	{
        if (empty()) 
            throw std::runtime_error("List is empty");

        return m_start->data;
    }

    T& back()
	{
        if (empty()) 
            throw std::runtime_error("List is empty");

        return m_end->data;
    }

    const T& back() const
	{
        if (empty()) throw std::runtime_error("List is empty");
        return m_end->data;
    }

    iterator begin()
    {
	    return iterator(m_start);
    }
    iterator end()
    {
	    return iterator(nullptr);
    }
    const_iterator begin() const
    {
        return const_iterator(m_start);
    }
    const_iterator end() const
    {
        return const_iterator(nullptr);
    }


    size_t size() const
    {
	    return m_size;
    }
    bool empty() const
    {
	    return m_size == 0;
    }

    friend std::ostream& operator<<(std::ostream& os, const myList& list)
	{
        if (list.empty()) 
        {
            os << "Empty list";
            return os;
        }

        os << "(";
        Node* curr = list.m_start;
        while (curr->next != nullptr) 
        {
            os << curr->data << ", ";
            curr = curr->next;
        }
        os << curr->data << ")";
        return os;
    }

    void resize(size_type count)
    {
        if (count == m_size)
            return;

        if (m_size > count)
        {
            while (m_size > count)
                pop_back();
        }
        else
        {
            while (m_size < count)
                push_back(T());
        }
    }

    size_type max_size() const
    {
        return m_size;
    }

    T& operator[](size_t index)
    {
        if (index >= m_size)
            throw std::out_of_range("Index out of range");

        Node* current = m_start;
        for (size_t i = 0; i < index; ++i)
        {
            current = current->next;
        }
        return current->data;
    }

    const T& operator[](size_t index) const
    {
        if (index >= m_size)
            throw std::out_of_range("Index out of range");

        Node* current = m_start;
        for (size_t i = 0; i < index; ++i)
        {
            current = current->next;
        }
        return current->data;
    }

    reverse_iterator rbegin()
    {
        return reverse_iterator(iterator(m_end));
    }

    reverse_iterator rend()
    {
        return reverse_iterator(iterator(m_start));
    }

    reverse_const_iterator rbegin() const
    {
        return reverse_const_iterator(const_iterator(m_end));
    }

    reverse_const_iterator rend() const
    {
        return reverse_const_iterator(const_iterator(m_start));
    }


    void assign(size_t count, const T& value)
    {
        clear();
        for (size_t i = 0; i < count; ++i)
        {
            push_back(value);
        }
    }

    void assign(std::initializer_list<T> iList)
    {
        clear();
        for (const auto& elem : iList)
        {
            push_back(elem);
        }
    }

    template<class Input>
    typename std::enable_if<!std::is_integral<Input>::value>::type
	assign(Input first, Input last)
    {
        clear();
        while (first != last)
        {
            push_back(*first);
            ++first;
        }
    }

    reference at(size_type index)
    {
        if (index >= m_size)
            throw std::out_of_range("Index out of range");

        Node* current = m_start;
        for (size_t i = 0; i < index; ++i)
        {
            current = current->next;
        }
        return current->data;
    }

    const_reference at(size_type index) const
    {
        if (index >= m_size)
            throw std::out_of_range("Index out of range");

        Node* current = m_start;
        for (size_t i = 0; i < index; ++i)
        {
            current = current->next;
        }
        return current->data;
    }

private:
	Node* m_start;
	Node* m_end;
	size_t m_size;
};