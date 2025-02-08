/**
 * @file myIntrusiveList.h
 * @brief Implementation of an intrusive list with iterators and utility functions.
 * @author Guillaume (and thank you Kroktur for your help)
 * @date 08/02/2025
 */

#pragma once 
#include <exception>
#include <initializer_list>
#include <sstream>

 /**
  * @namespace PLEASE
  * @brief Namespace containing the intrusive list implementation
  */
namespace PLEASE
{
	/**
	* @brief Node structure for the intrusive list
	* @tparam The type of data stored in the node
	*/
	template <typename type>
	struct Node
	{
		/**
		 * @brief Default constructor, initializes pointers to nullptr
		 */
		Node() :Next(nullptr), Previous(nullptr)
		{}

		/**
		 * @brief Parameterized constructor
		 * @param val Value to store in the node
		 */
		Node(type val) :data(val), Next(nullptr), Previous(nullptr)
		{}

		type data;              ///< Data stored in the node
		Node<type>* Next;       ///< Pointer to the next node in the list
		Node<type>* Previous;   ///< Pointer to the previous node in the list

		/**
		 * @brief Equality comparison operator
		 * @param other Node to compare with
		 * @return true if the data in both nodes is equal
		 */
		bool operator==(const Node& other) const
		{
			return data == other.data;
		}

		/**
		 * @brief Inequality comparison operator
		 * @param other Node to compare with
		 * @return true if the data in both nodes is not equal
		 */
		bool operator!=(const Node& other) const
		{
			return data != other.data;
		}

		/**
		 * @brief Less than comparison operator
		 * @param other Node to compare with
		 * @return true if this node's data is less than other's data
		 */
		bool operator<(const Node& other) const
		{
			return data < other.data;
		}

		/**
		* @brief Greater than comparison operator
		* @param other Node to compare with
		* @return false if other is nullptr, otherwise compares data
		*/
		bool operator>(const Node& other) const
		{
			if (&other == nullptr) 
				return false;

			return data > other.data;
		}

		/**
		 * @brief Less than or equal comparison operator
		 * @param other Node to compare with
		 * @return true if this node's data is less than or equal to other's data
		 */
		bool operator<=(const Node& other) const
		{
			return data <= other.data;
		}

		/**
		 * @brief Greater than or equal comparison operator
		 * @param other Node to compare with
		 * @return true if this node's data is greater than or equal to other's data
		 */
		bool operator>=(const Node& other) const
		{
			return data >= other.data;
		}

		/**
	   * @brief Assignment operator
	   * @param other Node to assign from
	   * @return The assigned value
	   */
		bool operator=(const Node& other)
		{
			return data = other.data;
		}
	};

	/**
	 * @brief Output stream operator for Node
	 * @param os Output stream
	 * @param node Node to output
	 * @return Reference to the output stream
	 */
	template <typename type>
	std::ostream& operator<<(std::ostream& os, const Node<type>& node)
	{
		return os << node.data;
	}

	/**
	 * @brief Intrusive doubly-linked list implementation
	 * @tparam type The type of data stored in the list
	 */
	template<typename type>
	struct myIntrusiveList
	{
	public:

		// Forward declarations and type aliases
		struct Node;
		struct iterator;
		struct const_iterator;
		struct reverse_iterator;
		struct const_reverse_iterator;
		using reverse_iterator = reverse_iterator;
		using const_reverse_iterator = const_reverse_iterator;
		using iterator = iterator;
		using const_iterator = const_iterator;
		using value_type = PLEASE::Node<type>;
		using pointer = PLEASE::Node<type>*;
		using const_pointer = const PLEASE::Node<type>*;
		using reference = PLEASE::Node<type>&;
		using const_reference = const PLEASE::Node<type>&;

		/**
		 * @brief Destructor, cleans up all nodes
		 */
		~myIntrusiveList() { clear(); }

		/**
		 * @brief Default constructor
		 * @details Initializes an empty list with head and tail sentinels
		 */
		myIntrusiveList(): m_size(0) { Head.Next = &Tail;  Tail.Previous = &Head; }

		/**
		* @brief Copy constructor
		* @param tab List to copy from
		*/
		myIntrusiveList(const myIntrusiveList& tab): m_size(0)
		{
			Head.Next = &Tail;
			Tail.Previous = &Head;
			for (auto it = tab.begin(); it != tab.end(); ++it)
			{
				push_back(*it);
			}
		}

		/**
		 * @brief Initializer list constructor
		 * @param list Initializer list to construct from
		 */
		myIntrusiveList(const std::initializer_list<PLEASE::Node<type>>& list): m_size(0)
		{
			Head.Next = &Tail;  Tail.Previous = &Head;
			for (const auto& element : list)
			{
				push_back(element);
			}
		}

		/**
		* @brief Resizes the list
		* @param idx New size
		* @details If idx is smaller than current size, removes elements from the end
		*          If idx is larger than current size, adds default-constructed elements
		*/
		void resize(const size_t& idx)
		{
			if (idx < m_size)
			{
				for (size_t i = m_size; i > idx; --i)
				{
					pop_back();
				}

			}
			if (idx > m_size)
			{
				for (size_t i = m_size; i < idx; ++i)
				{
					push_back(type{});
				}
			}

		}

		/**
		 * @brief Swaps the contents of two lists
		 * @param Newlist List to swap with
		 */
		void swap(myIntrusiveList<type>& Newlist)
		{
			myIntrusiveList<type> tmp = *this;
			*this = Newlist;
			Newlist = tmp;
		}

		/**
		 * @brief Adds an element to the end of the list
		 * @param val Value to add
		 */
		void push_back(const value_type& val)
		{
			pointer NewVal = new PLEASE::Node(val.data);
			Tail.Previous->Next = NewVal;
			NewVal->Next = &Tail;
			NewVal->Previous = Tail.Previous;
			Tail.Previous = NewVal;
			++m_size;
		}

		/**
		 * @brief Removes the last element
		 * @throw std::out_of_range if the list is empty
		 */
		void pop_back()
		{
			if (Empty())
				throw std::out_of_range("List is Empty");
			auto todelete = Tail.Previous;
			Tail.Previous = todelete->Previous;
			todelete->Previous->Next = &Tail;

			todelete->Next = nullptr;
			todelete->Previous = nullptr;
			delete todelete;

			--m_size;
		}

		/**
		 * @brief Adds an element to the front of the list
		 * @param val Value to add
		 */
		void pushFront(const value_type& val)
		{
			pointer NewVal = new PLEASE::Node(val.data);
			Head.Next->Previous = NewVal;
			NewVal->Previous = &Head;
			NewVal->Next = Head.Next;
			Head.Next = NewVal;
			++m_size;
		}

		/**
		 * @brief Removes the first element
		 * @throw std::out_of_range if the list is empty
		 */
		void popFront()
		{
			if (Empty())
				throw std::out_of_range("List is Empty");
			auto todelete = Head.Next;
			Head.Next = todelete->Next;
			todelete->Next->Previous = &Head;

			todelete->Next = nullptr;
			todelete->Previous = nullptr;
			delete todelete;

			--m_size;
		}

		/**
		* @brief Access operator
		* @param idx Index of element to access
		* @return Reference to the element at position idx
		*/
		reference operator[](const size_t& idx)
		{
			auto it = begin();
			for (auto i = 0; i < idx; ++i)
			{
				++it;
			}
			return *it;

		}

		/**
		* @brief Const access operator
		* @param idx Index of element to access
		* @return Const reference to the element at position idx
		*/
		const_reference operator[](const size_t& idx) const
		{
			auto it = begin();
			for (auto i = 0; i < idx; ++i)
			{
				++it;
			}
			return *it;
		}

		/**
		* @brief Safe element access with bounds checking
		* @param idx Index of element to access
		* @return Reference to the element at position idx
		* @throw std::out_of_range if idx is out of bounds or list is empty
		*/
		reference at(const size_t& idx)
		{
			if (Empty())
				throw std::out_of_range("vector is empty");
			if (idx >= m_size)
				throw std::out_of_range("idx out of vector range");
			auto it = begin();
			for (auto i = 0; i < idx; ++i)
			{
				++it;
			}
			return *it;
		}

		/**
		* @brief Safe const element access with bounds checking
		* @param idx Index of element to access
		* @return Const reference to the element at position idx
		* @throw std::out_of_range if idx is out of bounds or list is empty
		*/
		const_reference at(const size_t& idx) const
		{
			if (Empty())
				throw std::out_of_range("vector is empty");
			if (idx >= size)
				throw std::out_of_range("idx out of vector range");
			auto it = begin();
			for (auto i = 0; i < idx; ++i)
			{
				++it;
			}
			return *it;
		}

		/**
		 * @brief Checks if the list is empty
		 * @return true if the list is empty
		 */
		bool Empty()
		{
			return m_size == 0;
		}

		/**
		* @brief Const version of empty check
		* @return true if the list is empty
		*/
		bool Empty() const
		{
			return m_size == 0;
		}

		/**
		 * @brief Gets the current size of the list
		 * @return Number of elements in the list
		 */
		size_t size()
		{
			return m_size;
		}

		/**
		 * @brief Const version of size getter
		 * @return Number of elements in the list
		 */
		size_t size() const
		{
			return m_size;
		}

		/**
		 * @brief Removes element at iterator position
		 * @param it Iterator to element to remove
		 * @throw std::out_of_range if iterator is invalid
		 */
		void erase(const iterator& it)
		{
			if (find(it) == end())
				throw std::out_of_range("out of range");
			auto supr = it.m_node;
			supr->Previous->Next = supr->Next;
			supr->Next->Previous = supr->Previous;

			delete supr;

			--m_size;
		}

		/**
		 * @brief Gets iterator to first element
		 * @return Iterator to beginning
		 * @throw std::out_of_range if list is empty
		 */
		iterator begin()
		{
			if (Empty())
				throw std::out_of_range("Array is empty");
			return iterator(Head.Next);
		}

		/**
		 * @brief Gets const iterator to first element
		 * @return Const iterator to beginning
		 * @throw std::out_of_range if list is empty
		 */
		const_iterator begin() const
		{
			if (Empty())
				throw std::out_of_range("Array is empty");
			return const_iterator(Head.Next);
		}

		/**
		 * @brief Gets iterator to end
		 * @return Iterator to end
		 * @throw std::out_of_range if list is empty
		 */
		iterator end()
		{
			if (Empty())
				throw std::out_of_range("Array is empty");
			return iterator(&Tail);
		}

		/**
		* @brief Gets const iterator to end
		* @return Const iterator to end
		* @throw std::out_of_range if list is empty
		*/
		const_iterator end() const
		{
			if (Empty())
				throw std::out_of_range("Array is empty");
			return const_iterator(&Tail);
		}

		/**
		* @brief Access first element
		* @return Reference to first element
		* @throw std::out_of_range if list is empty
		*/
		reference front()
		{
			if (Empty())
				throw std::out_of_range("Array is empty");
			return *Head.Next;
		}

		/**
		 * @brief Const access to first element
		 * @return Const reference to first element
		 * @throw std::out_of_range if list is empty
		 */
		const_reference front() const
		{
			if (Empty())
				throw std::out_of_range("Array is empty");
			return *Head.Next;
		}

		/**
		 * @brief Access last element
		 * @return Reference to last element
		 * @throw std::out_of_range if list is empty
		 */
		reference back()
		{
			if (Empty())
				throw std::out_of_range("Array is empty");
			return *Tail.Previous;
		}

		/**
		 * @brief Const access to last element
		 * @return Const reference to last element
		 * @throw std::out_of_range if list is empty
		 */
		const_reference back() const
		{
			if (Empty())
				throw std::out_of_range("Array is empty");
			return *Tail.Previous;
		}

		/**
		 * @brief Removes all elements from the list
		 */
		void clear()
		{
			while (!Empty())
				popFront();
			resize(0);
		}

		/**
		 * @brief Assignment operator
		 * @param tab List to copy from
		 * @return Reference to this list
		 */
		myIntrusiveList& operator=(const myIntrusiveList& tab)
		{
			clear();
			for (auto it = tab.begin(); it != tab.end(); ++it)
			{
				push_back(*it);
			}
			return *this;
		}

		/**
		 * @brief Assigns new contents to the list using iterator range
		 * @param begin Iterator to start of range
		 * @param end Iterator to end of range
		 */
		void assign(const iterator& begin, const iterator& end)
		{
			clear();
			for (auto it = begin; it != end; ++it)
			{
				push_back(*it);
			}
		}

		/**
		 * @brief Assigns new contents to the list with a given value repeated n times
		 * @param sizeofvec Number of elements to assign
		 * @param data Value to fill the list with
		 */
		void assign(const size_t& sizeofvec, const value_type& data)
		{
			clear();
			for (size_t i = 0; i < sizeofvec; ++i)
			{
				push_back(data);
			}
		}

		/**
		 * @brief Assigns new contents from an initializer list
		 * @param list Initializer list to assign from
		 */
		void assign(const std::initializer_list<PLEASE::Node<type>>& list)
		{
			clear();
			for (const auto& element : list)
			{
				push_back(element);
			}
		}

		/**
		 * @brief Gets reverse iterator to last element
		 * @return Reverse iterator to the reverse beginning
		 * @throw std::out_of_range if list is empty
		 */
		reverse_iterator rbegin()
		{
			if (Empty())
				throw std::out_of_range("Array is empty");
			return reverse_iterator(Tail.Previous);
		}

		/**
		 * @brief Gets const reverse iterator to last element
		 * @return Const reverse iterator to the reverse beginning
		 * @throw std::out_of_range if list is empty
		 */
		const_reverse_iterator rbegin() const
		{
			if (Empty())
				throw std::out_of_range("Array is empty");
			return const_reverse_iterator(Tail.Previous);
		}

		/**
		 * @brief Gets reverse iterator to theoretical element before first
		 * @return Reverse iterator to the reverse end
		 * @throw std::out_of_range if list is empty
		 */
		reverse_iterator rend()
		{
			if (Empty())
				throw std::out_of_range("Array is empty");
			return reverse_iterator(&Head);
		}

		/**
		 * @brief Gets const reverse iterator to theoretical element before first
		 * @return Const reverse iterator to the reverse end
		 * @throw std::out_of_range if list is empty
		 */
		const_reverse_iterator rend() const
		{
			if (Empty())
				throw std::out_of_range("Array is empty");
			return const_reverse_iterator(&Head);
		}

		/**
		 * @brief Gets the maximum possible size of the list
		 * @return Maximum number of elements that can be held
		 */
		size_t max_size()
		{
			return std::numeric_limits<size_t>::max() / sizeof(type);
		}

		/**
		* @brief Const version of max_size
		* @return Maximum number of elements that can be held
		*/
		size_t max_size() const
		{
			return std::numeric_limits<size_t>::max() / sizeof(type);
		}

		/**
		 * @brief Inserts an element at iterator position
		 * @param newit Iterator indicating the position to insert
		 * @param value Value to insert
		 * @throw std::out_of_range if iterator is invalid
		 */
		void insert(const iterator& newit, const value_type& value)
		{
			if (find(newit) == end())
				throw std::out_of_range("Out of range");
			auto oldnode = newit.m_node;
			pointer nodetoadd = new PLEASE::Node<type>(value.data);
			nodetoadd->Next = oldnode;
			nodetoadd->Previous = oldnode->Previous;
			oldnode->Previous->Next = nodetoadd;
			oldnode->Previous = nodetoadd;
			++m_size;
		}

		/**
		 * @brief Finds an element in the list
		 * @param ptr Iterator to search for
		 * @return Iterator to found element or end() if not found
		 */
		iterator find(const iterator& ptr)
		{
			for (auto it = begin(); it != end(); ++it)
			{
				if (it == ptr)
					return it;
			}
			return end();
		}

		/**
		 * @brief Const version of find
		 * @param ptr Iterator to search for
		 * @return Const iterator to found element or end() if not found
		 */
		const_iterator find(const iterator& ptr) const
		{
			for (auto it = begin(); it != end(); ++it)
			{
				if (it == ptr)
					return it;
			}
			return end();
		}
	private:

		/**
		* @brief Iterator class for myIntrusiveList
		* @details Provides STL-compatible random access iterator functionality
		*/
		struct iterator
		{
			//this iterator compatible with stl
			using iterator_category = std::random_access_iterator_tag;
			using value_type = PLEASE::Node<type>;
			using difference_type = std::ptrdiff_t;
			using pointer = PLEASE::Node<type>*;
			using reference = PLEASE::Node<type>&;
			friend myIntrusiveList;

			/**
			 * @brief Constructor
			 * @param ptr Pointer to node
			 */
			iterator(pointer ptr) : m_node(ptr) {}

			/**
			 * @brief Dereference operator
			 * @return Reference to the node
			 */
			reference operator*()
			{
				return *m_node;
			}

			/**
			 * @brief Const dereference operator
			 * @return Const reference to the node
			 */
			const reference  operator*() const
			{
				return *m_node;
			}

			/**
			 * @brief Arrow operator
			 * @return Pointer to the node
			 */
			pointer operator->()
			{
				return m_node;
			}

			/**
			 * @brief Const arrow operator
			 * @return Const pointer to the node
			 */
			const pointer operator->() const
			{
				return m_node;
			}

			/**
			 * @brief Pre-increment operator
			 * @return Reference to incremented iterator
			 */
			iterator& operator++()
			{
				if (m_node != nullptr) 
				{
					m_node = m_node->Next;
				}
				return *this;
			}

			/**
			 * @brief Pre-decrement operator
			 * @return Reference to decremented iterator
			 */
			iterator& operator--()
			{
				m_node = m_node->Previous;
				return *this;
			}

			/**
			* @brief Addition operator
			* @param n Number of positions to advance
			* @return New iterator n positions forward
			*/
			iterator operator+(difference_type n) const
			{
				auto curentnode = m_node;
				for (size_t i = 0; i < n; ++i)
				{
					curentnode = curentnode->Next;
				}
				return iterator(curentnode);
			}

			/**
			 * @brief Subtraction operator
			 * @param n Number of positions to move backward
			 * @return New iterator n positions backward
			 */
			iterator operator-(difference_type n) const
			{
				auto curentnode = m_node;
				for (size_t i = 0; i < n; ++i)
				{
					curentnode = curentnode->Previous;
				}
				return iterator(curentnode);
			}

			/**
			 * @brief Compound addition operator
			 * @param n Number of positions to advance
			 * @return Iterator advanced by n positions
			 */
			iterator operator+=(difference_type n)
			{
				auto currentnode = m_node;
				for (size_t i = 0; i < n; ++i)
				{
					currentnode = currentnode->Next;
				}
				return iterator(currentnode);
			}

			/**
			 * @brief Iterator subtraction operator
			 * @param other Iterator to subtract from this one
			 * @return Distance between iterators
			 */
			difference_type operator-(const iterator& other) const
			{
				difference_type diff = 0;
				for (auto it = *this; it != other; --it)
				{
					++diff;
				}
				return diff;
			}

			/**
			 * @brief Iterator addition operator
			 * @param other Iterator to add to this one
			 * @return Sum of distances
			 */
			difference_type operator+(const iterator& other) const
			{
				difference_type diff = 0;
				for (auto it = *this; it != other; ++it)
				{
					++diff;
				}
				return diff;
			}

			/**
			* @brief Equality comparison operator
			* @param other Iterator to compare with
			* @return true if iterators point to same node
			*/
			bool operator==(const iterator& other) const
			{
				return m_node == other.m_node;
			}

			/**
			 * @brief Inequality comparison operator
			 * @param other Iterator to compare with
			 * @return true if iterators point to different nodes
			 */
			bool operator!=(const iterator& other) const
			{
				return m_node != other.m_node;
			}

			/**
			 * @brief Less than comparison operator
			 * @param other Iterator to compare with
			 * @return true if this iterator comes before other in sequence
			 */
			bool operator<(const iterator& other) const
			{
				auto curent = m_node;
				while (curent != nullptr)
				{
					curent = curent->Next;
					if (curent == other.m_node)
						return true;

				}
				return false;
			}

			/**
			 * @brief Greater than comparison operator
			 * @param other Iterator to compare with
			 * @return true if this iterator comes after other in sequence
			 */
			bool operator>(const iterator& other) const
			{
				auto curent = m_node;
				while (curent != nullptr)
				{
					curent = curent->Previous;
					if (curent == other.m_node)
						return true;

				}
				return false;
			}

			/**
			 * @brief Less than or equal comparison operator
			 * @param other Iterator to compare with
			 * @return true if this iterator comes before or points to same node as other
			 */
			bool operator<=(const iterator& other) const
			{
				auto curent = m_node;
				while (curent != nullptr)
				{
					if (curent == other.m_node)
						return true;
					curent = curent->Next;
				}
				return false;
			}

			/**
			* @brief Greater than or equal comparison operator
			* @param other Iterator to compare with
			* @return true if this iterator comes after or points to same node as other
			*/
			bool operator>=(const iterator& other) const
			{
				auto curent = m_node;
				while (curent != nullptr)
				{
					if (curent == other.m_node)
						return true;
					curent = curent->Previous;
				}
				return false;
			}
		private:
			pointer m_node;  ///< Pointer to current node
		};

		/// SAME THING AS ITERATOR CLASS
		struct const_iterator
		{
			//this iterator compatible with stl
			using iterator_category = std::random_access_iterator_tag;
			using value_type = const PLEASE::Node<type>;
			using difference_type = std::ptrdiff_t;
			using pointer = const PLEASE::Node<type>*;
			using reference = const PLEASE::Node<type>&;
			friend myIntrusiveList;
			const_iterator(pointer ptr) : m_node(ptr) {}
			reference operator*()
			{
				return *m_node;
			}
			reference operator*() const
			{
				return *m_node;
			}
			pointer operator->()
			{
				return m_node;
			}
			pointer operator->() const
			{
				return m_node;
			}
			const_iterator& operator++()
			{
				m_node = m_node->Next;
				return *this;
			}
			const_iterator& operator--()
			{
				m_node = m_node->Previous;
				return *this;
			}
			const_iterator operator+(difference_type n) const
			{
				auto curentnode = m_node;
				for (size_t i = 0; i < n; ++i)
				{
					curentnode = curentnode->Next;
				}
				return const_iterator(curentnode);
			}
			const_iterator operator-(difference_type n) const
			{
				auto curentnode = m_node;
				for (size_t i = 0; i < n; ++i)
				{
					curentnode = curentnode->Previous;
				}
				return const_iterator(curentnode);
			}
			const_iterator& operator+=(difference_type n)
			{
				for (size_t i = 0; i < n; ++i)
				{
					m_node = m_node->Next;
				}
				return *this;
			}
			difference_type operator-(const const_iterator& other) const
			{
				difference_type diff = 0;
				for (auto it = *this; it != other; --it)
				{
					++diff;
				}
				return diff;
			}
			difference_type operator+(const const_iterator& other) const
			{
				difference_type diff = 0;
				for (auto it = *this; it != other; ++it)
				{
					++diff;
				}
				return diff;
			}
			bool operator==(const const_iterator& other) const
			{
				return m_node == other.m_node;
			}
			bool operator!=(const const_iterator& other) const
			{
				return m_node != other.m_node;
			}
			bool operator<(const const_iterator& other) const
			{
				auto curent = m_node;
				while (curent != nullptr)
				{
					curent = curent->Next;
					if (curent == other.m_node)
						return true;

				}
				return false;
			}
			bool operator>(const const_iterator& other) const
			{
				auto curent = m_node;
				while (curent != nullptr)
				{
					curent = curent->Previous;
					if (curent == other.m_node)
						return true;

				}
				return false;
			}
			bool operator<=(const const_iterator& other) const
			{
				auto curent = m_node;
				while (curent != nullptr)
				{
					if (curent == other.m_node)
						return true;
					curent = curent->Next;
				}
				return false;
			}
			bool operator>=(const const_iterator& other) const
			{
				auto curent = m_node;
				while (curent != nullptr)
				{
					if (curent == other.m_node)
						return true;
					curent = curent->Previous;
				}
				return false;
			}
		private:
			pointer m_node;
		};

		/// SAME THING AS ITERATOR CLASS
		struct reverse_iterator
		{
			using iterator_category = std::random_access_iterator_tag;
			using value_type = PLEASE::Node<type>;
			using difference_type = std::ptrdiff_t;
			using pointer = PLEASE::Node<type>*;
			using reference = PLEASE::Node<type>&;
			friend myIntrusiveList;
			reverse_iterator(pointer ptr) : m_node(ptr) {}
			type& operator*()
			{
				return m_node->data;
			}
			const reference operator*() const
			{
				return *m_node;
			}
			pointer operator->()
			{
				return m_node;
			}
			const pointer operator->() const
			{
				return m_node;
			}
			reverse_iterator& operator++()
			{
				m_node = m_node->Previous;
				return *this;
			}
			reverse_iterator& operator--()
			{
				m_node = m_node->Next;
				return *this;
			}
			reverse_iterator operator+(difference_type n) const
			{
				auto curentnode = m_node;
				for (size_t i = 0; i < n; ++i)
				{
					curentnode = curentnode->Previous;
				}
				return reverse_iterator(curentnode);
			}
			reverse_iterator operator-(difference_type n) const
			{
				auto curentnode = m_node;
				for (size_t i = 0; i < n; ++i)
				{
					curentnode = curentnode->Next;
				}
				return reverse_iterator(curentnode);
			}
			difference_type operator-(const reverse_iterator& other) const
			{
				difference_type diff = 0;
				for (auto it = *this; it != other; --it)
				{
					++diff;
				}
				return diff;
			}
			difference_type operator+(const reverse_iterator& other) const
			{
				difference_type diff = 0;
				for (auto it = *this; it != other; ++it)
				{
					++diff;
				}
				return diff;
			}
			bool operator==(const reverse_iterator& other) const
			{
				return m_node == other.m_node;
			}
			bool operator!=(const reverse_iterator& other) const
			{
				return m_node != other.m_node;
			}
			bool operator<(const reverse_iterator& other) const
			{
				auto curent = m_node;
				while (curent != nullptr)
				{
					curent = curent->Next;
					if (curent == other.m_node)
						return true;

				}
				return false;
			}
			bool operator>(const reverse_iterator& other) const
			{
				auto curent = m_node;
				while (curent != nullptr)
				{
					curent = curent->Previous;
					if (curent == other.m_node)
						return true;

				}
				return false;
			}
			bool operator<=(const reverse_iterator& other) const
			{
				auto curent = m_node;
				while (curent != nullptr)
				{
					if (curent == other.m_node)
						return true;
					curent = curent->Next;
				}
				return false;
			}
			bool operator>=(const reverse_iterator& other) const
			{
				auto curent = m_node;
				while (curent != nullptr)
				{
					if (curent == other.m_node)
						return true;
					curent = curent->Previous;
				}
				return false;
			}
		private:
			pointer m_node;
		};

		/// SAME THING AS ITERATOR CLASS
		struct const_reverse_iterator
		{
			using iterator_category = std::random_access_iterator_tag;
			using value_type = const PLEASE::Node<type>;
			using difference_type = std::ptrdiff_t;
			using pointer = const PLEASE::Node<type>*;
			using reference = const PLEASE::Node<type>&;
			friend myIntrusiveList;
			const_reverse_iterator(pointer ptr) : m_node(ptr) {}
			reference operator*()
			{
				return *m_node;
			}
			const reference operator*() const
			{
				return *m_node;
			}
			pointer operator->()
			{
				return m_node;
			}
			pointer operator->() const
			{
				return m_node;
			}
			const_reverse_iterator& operator++()
			{
				m_node = m_node->Previous;
				return *this;
			}
			const_reverse_iterator& operator--()
			{
				m_node = m_node->Next;
				return *this;
			}
			const_reverse_iterator operator+(difference_type n) const
			{
				auto curentnode = m_node;
				for (size_t i = 0; i < n; ++i)
				{
					curentnode = curentnode->Previous;
				}
				return const_reverse_iterator(curentnode);
			}
			const_reverse_iterator operator-(difference_type n) const
			{
				auto curentnode = m_node;
				for (size_t i = 0; i < n; ++i)
				{
					curentnode = curentnode->Next;
				}
				return const_reverse_iterator(curentnode);
			}
			difference_type operator-(const const_reverse_iterator& other) const
			{
				difference_type diff = 0;
				for (auto it = *this; it != other; --it)
				{
					++diff;
				}
				return diff;
			}
			difference_type operator+(const const_reverse_iterator& other) const
			{
				difference_type diff = 0;
				for (auto it = *this; it != other; ++it)
				{
					++diff;
				}
				return diff;
			}
			bool operator==(const const_reverse_iterator& other) const
			{
				return m_node == other.m_node;
			}
			bool operator!=(const const_reverse_iterator& other) const
			{
				return m_node != other.m_node;
			}
			bool operator<(const const_reverse_iterator& other) const
			{
				auto curent = m_node;
				while (curent != nullptr)
				{
					curent = curent->Next;
					if (curent == other.m_node)
						return true;

				}
				return false;
			}
			bool operator>(const const_reverse_iterator& other) const
			{
				auto curent = m_node;
				while (curent != nullptr)
				{
					curent = curent->Previous;
					if (curent == other.m_node)
						return true;

				}
				return false;
			}
			bool operator<=(const const_reverse_iterator& other) const
			{
				auto curent = m_node;
				while (curent != nullptr)
				{
					if (curent == other.m_node)
						return true;
					curent = curent->Next;
				}
				return false;
			}
			bool operator>=(const const_reverse_iterator& other) const
			{
				auto curent = m_node;
				while (curent != nullptr)
				{
					if (curent == other.m_node)
						return true;
					curent = curent->Previous;
				}
				return false;
			}

		private:
			pointer m_node;
		};
		PLEASE::Node<type> Head;    ///< Head sentinel node
		PLEASE::Node<type> Tail;    ///< Tail sentinel node
		size_t m_size;              ///< Current size of the list
	};

	/**
	 * @brief Output stream operator for myIntrusiveList
	 * @param os Output stream
	 * @param tab List to output
	 * @return Reference to output stream
	 */
	template< typename type>
	std::ostream& operator<<(std::ostream& os, const myIntrusiveList<type>& tab)
	{
		if (tab.Empty())
			return os;
		os << "(";
		for (auto i = 0; i < tab.size() - 1; ++i)
			os << tab[i] << ", ";
		os << tab[tab.size() - 1] << ")";
		return os;
	}

}