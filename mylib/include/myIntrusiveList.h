#pragma once 
#include <exception>
#include <initializer_list>
#include <sstream>

namespace PLEASE
{
	template <typename type>
	struct Node
	{
		Node() :Next(nullptr), Previous(nullptr)
		{
		}
		Node(type val) :data(val), Next(nullptr), Previous(nullptr)
		{
		}
		type data;
		Node<type>* Next;
		Node<type>* Previous;

		bool operator==(const Node& other) const
		{
			return data == other.data;
		}
		bool operator!=(const Node& other) const
		{
			return data != other.data;
		}
		bool operator<(const Node& other) const
		{
			return data < other.data;
		}
		bool operator>(const Node& other) const
		{
			if (&other == nullptr) 
				return false;

			return data > other.data;
		}
		bool operator<=(const Node& other) const
		{
			return data <= other.data;
		}
		bool operator>=(const Node& other) const
		{
			return data >= other.data;
		}
	};

	template <typename type>
	std::ostream& operator<<(std::ostream& os, const Node<type>& node)
	{
		return os << node.data;
	}

	template<typename type>
	struct myIntrusiveList
	{
	public:

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
		~myIntrusiveList() { clear(); }
		myIntrusiveList(): m_size(0) { Head.Next = &Tail;  Tail.Previous = &Head; }
		myIntrusiveList(const myIntrusiveList& tab): m_size(0)
		{
			Head.Next = &Tail;
			Tail.Previous = &Head;
			for (auto it = tab.begin(); it != tab.end(); ++it)
			{
				push_back(*it);
			}
		}
		myIntrusiveList(const std::initializer_list<PLEASE::Node<type>>& list): m_size(0)
		{
			Head.Next = &Tail;  Tail.Previous = &Head;
			for (const auto& element : list)
			{
				push_back(element);
			}
		}
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
		void swap(myIntrusiveList<type>& Newlist)
		{
			myIntrusiveList<type> tmp = *this;
			*this = Newlist;
			Newlist = tmp;
		}
		void push_back(const value_type& val)
		{
			pointer NewVal = new PLEASE::Node(val.data);
			Tail.Previous->Next = NewVal;
			NewVal->Next = &Tail;
			NewVal->Previous = Tail.Previous;
			Tail.Previous = NewVal;
			++m_size;
		}
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
		void pushFront(const value_type& val)
		{
			pointer NewVal = new PLEASE::Node(val.data);
			Head.Next->Previous = NewVal;
			NewVal->Previous = &Head;
			NewVal->Next = Head.Next;
			Head.Next = NewVal;
			++m_size;
		}
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
		reference operator[](const size_t& idx)
		{
			auto it = begin();
			for (auto i = 0; i < idx; ++i)
			{
				++it;
			}
			return *it;

		}
		const_reference operator[](const size_t& idx) const
		{
			auto it = begin();
			for (auto i = 0; i < idx; ++i)
			{
				++it;
			}
			return *it;
		}
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
		bool Empty()
		{
			return m_size == 0;
		}
		bool Empty() const
		{
			return m_size == 0;
		}
		size_t size()
		{
			return m_size;
		}
		size_t size() const
		{
			return m_size;
		}
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
		iterator begin()
		{
			if (Empty())
				throw std::out_of_range("Array is empty");
			return iterator(Head.Next);
		}
		const_iterator begin() const
		{
			if (Empty())
				throw std::out_of_range("Array is empty");
			return const_iterator(Head.Next);
		}
		iterator end()
		{
			if (Empty())
				throw std::out_of_range("Array is empty");
			return iterator(&Tail);
		}
		const_iterator end() const
		{
			if (Empty())
				throw std::out_of_range("Array is empty");
			return const_iterator(&Tail);
		}
		reference front()
		{
			if (Empty())
				throw std::out_of_range("Array is empty");
			return *Head.Next;
		}
		const_reference front() const
		{
			if (Empty())
				throw std::out_of_range("Array is empty");
			return *Head.Next;
		}
		reference back()
		{
			if (Empty())
				throw std::out_of_range("Array is empty");
			return *Tail.Previous;
		}
		const_reference back() const
		{
			if (Empty())
				throw std::out_of_range("Array is empty");
			return *Tail.Previous;
		}
		void clear()
		{
			while (!Empty())
				popFront();
			resize(0);
		}
		myIntrusiveList& operator=(const myIntrusiveList& tab)
		{
			clear();
			for (auto it = tab.begin(); it != tab.end(); ++it)
			{
				push_back(*it);
			}
			return *this;
		}
		void assign(const iterator& begin, const iterator& end)
		{
			clear();
			for (auto it = begin; it != end; ++it)
			{
				push_back(*it);
			}
		}
		void assign(const size_t& sizeofvec, const value_type& data)
		{
			clear();
			for (size_t i = 0; i < sizeofvec; ++i)
			{
				push_back(data);
			}
		}
		void assign(const std::initializer_list<PLEASE::Node<type>>& list)
		{
			clear();
			for (const auto& element : list)
			{
				push_back(element);
			}
		}
		reverse_iterator rbegin()
		{
			if (Empty())
				throw std::out_of_range("Array is empty");
			return reverse_iterator(Tail.Previous);
		}
		const_reverse_iterator rbegin() const
		{
			if (Empty())
				throw std::out_of_range("Array is empty");
			return const_reverse_iterator(Tail.Previous);
		}
		reverse_iterator rend()
		{
			if (Empty())
				throw std::out_of_range("Array is empty");
			return reverse_iterator(&Head);
		}
		const_reverse_iterator rend() const
		{
			if (Empty())
				throw std::out_of_range("Array is empty");
			return const_reverse_iterator(&Head);
		}
		size_t max_size()
		{
			return std::numeric_limits<size_t>::max() / sizeof(type);
		}
		size_t max_size() const
		{
			return std::numeric_limits<size_t>::max() / sizeof(type);
		}
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
		iterator find(const iterator& ptr)
		{
			for (auto it = begin(); it != end(); ++it)
			{
				if (it == ptr)
					return it;
			}
			return end();
		}
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

		struct iterator
		{
			//this iterator compatible with stl
			using iterator_category = std::random_access_iterator_tag;
			using value_type = PLEASE::Node<type>;
			using difference_type = std::ptrdiff_t;
			using pointer = PLEASE::Node<type>*;
			using reference = PLEASE::Node<type>&;
			friend myIntrusiveList;
			iterator(pointer ptr) : m_node(ptr) {}
			reference operator*()
			{
				return *m_node;
			}
			const reference  operator*() const
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
			iterator& operator++()
			{
				if (m_node != nullptr) 
				{
					m_node = m_node->Next;
				}
				return *this;
			}
			iterator& operator--()
			{
				m_node = m_node->Previous;
				return *this;
			}
			iterator operator+(difference_type n) const
			{
				auto curentnode = m_node;
				for (size_t i = 0; i < n; ++i)
				{
					curentnode = curentnode->Next;
				}
				return iterator(curentnode);
			}
			iterator operator-(difference_type n) const
			{
				auto curentnode = m_node;
				for (size_t i = 0; i < n; ++i)
				{
					curentnode = curentnode->Previous;
				}
				return iterator(curentnode);
			}
			iterator operator+=(difference_type n)
			{
				auto currentnode = m_node;
				for (size_t i = 0; i < n; ++i)
				{
					currentnode = currentnode->Next;
				}
				return iterator(currentnode);
			}
			difference_type operator-(const iterator& other) const
			{
				difference_type diff = 0;
				for (auto it = *this; it != other; --it)
				{
					++diff;
				}
				return diff;
			}
			difference_type operator+(const iterator& other) const
			{
				difference_type diff = 0;
				for (auto it = *this; it != other; ++it)
				{
					++diff;
				}
				return diff;
			}
			bool operator==(const iterator& other) const
			{
				return m_node == other.m_node;
			}
			bool operator!=(const iterator& other) const
			{
				return m_node != other.m_node;
			}
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
			pointer m_node;
		};
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
		PLEASE::Node<type> Head;
		PLEASE::Node<type> Tail;
		size_t m_size;
	};

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