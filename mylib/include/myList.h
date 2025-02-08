/**
 * @file myList.h
 * @brief Implementation of a list with iterators and utility functions.
 * @author Guillaume
 * @date 08/02/2025
 */

#pragma once
#include <iterator>
#include <stdexcept>

 /**
  * @struct myList
  * @brief Template struct representing a list with iterators.
  * @tparam T Type of elements stored in the array.
  */
template<typename T>
struct myList
{
    /** Structure representing a node in the doubly linked list. */
    struct Node
    {
        T data; /**< Data stored in the node. */
        Node* prev; /**< Pointer to the previous node. */
        Node* next; /**< Pointer to the next node. */

        /**
         * @brief Node constructor.
         *  @param value The value to store in the node.
         */
        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };

    /**
	* @class iterator
	 * @brief Random-access iterator for myList
	 */
    class iterator
	{
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        /**
         * @brief Iterator constructor.
         *  @param node The node the iterator points to.
         */
        iterator(Node* node) : m_node(node) {}

        /**
         * @brief Dereference the iterator to access the data.
         *  @return The data of the node the iterator points to.
         */
        reference operator*()
        {
	        return m_node->data;
        }
        /**
         * @brief Arrow operator to access the data through the iterator.
         *  @return Pointer to the data of the node the iterator points to.
         */
        pointer operator->()
        {
	        return &m_node->data;
        }

        /**
		 * @brief ++ operator to move the iterator to the next node.
		 * @return Iterator pointing to the next node.
         */
        iterator& operator++()
    	{
            m_node = m_node->next;
            return *this;
        }

        /**
		 * @brief ++ operator to move the iterator to the next node.
		 * @return Iterator pointing to the next node.
         */
        iterator operator++(int)
    	{
            iterator tmp = *this;
            m_node = m_node->next;
            return tmp;
        }

        /**
		 * @brief -- operator to move the iterator to the previous node.
		 * @return Iterator pointing to the previous node.
         */
        iterator& operator--()
        {
            if (m_node != nullptr)
            {
                m_node = m_node->prev;
            }
            return *this;
        }

        /**
         * @brief -- operator to move the iterator to the previous node.
         * @return Iterator pointing to the previous node.
         */
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

    /**
     * @brief Class for const iterator
	 * All the functions are the same as the iterator class, except that the operator* and operator-> return a const reference or pointer to the data.
     */
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

    /**
	 * @brief Default constructor for the myList
     */
    myList() : m_start(nullptr), m_end(nullptr), m_size(0) {}

    /**
	 * @brief Constructor with initializer list
     * @param init 
     */
    myList(std::initializer_list<T> init) : myList()
	{
        for (const auto& value : init) 
        {
            push_back(value);
        }
    }

    /**
	 * @brief Destructor for the myList
     */
    ~myList()
	{
        clear();
    }

    /**
	 * @brief Copy constructor for the myList
     * @param other 
     */
    myList(const myList& other) : myList()
	{
        for (Node* curr = other.m_start; curr != nullptr; curr = curr->next) 
        {
            push_back(curr->data);
        }
    }

    /**
	 * @brief Copy assignment operator for the myList
     * @param other 
     * @return 
     */
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

    /**
	 * @brief Push the value at the front of the list
     * @param value 
     */
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

    /**
	 * @brief Push the value at the back of the list
     * @param value 
     */
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

    /**
	 * @brief Delete the first element of the list
     */
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

    /**
     * @brief Delete the last element of the list
     */
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

    /**
	 * @brief Insert the value at the position
     * @param pos 
     * @param value 
	 * @return an iterator pointing to the inserted value
     */
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

    /**
	 * @brief Erase the element at the position
     * @param pos 
	 * @return an iterator pointing to the next element
     */
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

    /**
	 * @brief Clear the list
     */
    void clear()
	{
        while (!empty()) 
        {
            pop_front();
        }
    }

    /**
     * @brief Returns the first element of the list
	 * @return m_start->data
     */
    T& front()
	{
        if (empty()) 
            throw std::runtime_error("List is empty");

        return m_start->data;
    }

    /**
     * @brief Const version of front()
     * @return 
     */
    const T& front() const
	{
        if (empty()) 
            throw std::runtime_error("List is empty");

        return m_start->data;
    }

    /**
     * @brief Returns the last element of the list
     * @return m_end->data
     */
    T& back()
	{
        if (empty()) 
            throw std::runtime_error("List is empty");

        return m_end->data;
    }

    /**
     * @brief Const version of back()
     * @return 
     */
    const T& back() const
	{
        if (empty()) throw std::runtime_error("List is empty");
        return m_end->data;
    }

    /**
	 * @brief Returns an iterator to the first element of the list
	 * @return iterator to m_start
     */
    iterator begin()
    {
	    return iterator(m_start);
    }
    /**
	 * @brief Returns an iterator to the last element of the list
     * @return iterator to nullptr
     */
    iterator end()
    {
	    return iterator(nullptr);
    }
    /**
     * @brief Const version of begin()
     * @return 
     */
    const_iterator begin() const
    {
        return const_iterator(m_start);
    }

    /**
     * @brief Const version of end()
     * @return 
     */
    const_iterator end() const
    {
        return const_iterator(nullptr);
    }


    /**
     * @brief Returns the size of the list
     * @return m_size
     */
    size_t size() const
    {
	    return m_size;
    }

    /**
	 * @brief Returns true if the list is empty
	 * @return m_size == 0
     */
    bool empty() const
    {
	    return m_size == 0;
    }

    /**
     * @brief Overloaded stream output operator for myList
     * @param os Output Stream
	 * @param list List to be printed
	 * @return modified output stream
     */
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

    /**
	 * @brief Resize the list
     * @param count 
     */
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

    /**
     * @brief Returns the maximum size of the list
     * @return m_size
     */
    size_type max_size() const
    {
        return m_size;
    }

    /**
     * @brief Access element at specified index without bounds checking.
     * @param index Position of the element.
     * @return Reference to the element.
     */
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

    /**
	* @brief Const version of operator[].
	* @param index Position of the element.
	* @return Const reference to the element.
	*/
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

    /**
     * @brief Gets reverse iterator to last element
     * @return Reverse iterator to the reverse beginning
     */
    reverse_iterator rbegin()
    {
        return reverse_iterator(iterator(m_end));
    }

    /**
	 * @brief Gets reverse iterator to theoretical element before first
	 * @return Reverse iterator to the reverse end
	 */
    reverse_iterator rend()
    {
        return reverse_iterator(iterator(m_start));
    }

    /**
	* @brief Gets const reverse iterator to last element
	* @return Const reverse iterator to the reverse beginning
	*/
    reverse_const_iterator rbegin() const
    {
        return reverse_const_iterator(const_iterator(m_end));
    }

    /**
	* @brief Gets const reverse iterator to theoretical element before first
	* @return Const reverse iterator to the reverse end
	*/
    reverse_const_iterator rend() const
    {
        return reverse_const_iterator(const_iterator(m_start));
    }


    /**
	 * @brief Assigns new contents to the list, replacing its current contents, and modifying its size accordingly.
     * @param count 
     * @param value 
     */
    void assign(size_t count, const T& value)
    {
        clear();
        for (size_t i = 0; i < count; ++i)
        {
            push_back(value);
        }
    }

    /**
	 * @brief Assigns new contents to the list, replacing its current contents, and modifying its size accordingly.
     * @param iList 
     */
    void assign(std::initializer_list<T> iList)
    {
        clear();
        for (const auto& elem : iList)
        {
            push_back(elem);
        }
    }

    /**
	 * @brief Assigns new contents to the list, replacing its current contents, and modifying its size accordingly.
     * @tparam Input 
     * @param first 
     * @param last 
     * @return 
     */
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

    /**
	 * @brief Returns a reference to the element at specified location pos, with bounds checking.
     * @param index 
     * @return current->data
     */
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

    /**
     * @brief Const version of at()
     * @param index 
     * @return a const reference of current->data
     */
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