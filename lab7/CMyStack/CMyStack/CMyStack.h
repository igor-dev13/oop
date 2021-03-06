#pragma once

template <typename T>
class CMyStack
{
public:
	CMyStack()
		: m_top(nullptr)
		, m_size(0)
	{
	};

	CMyStack(CMyStack<T> const &other)
	{
		*this = other;
	}

	CMyStack(CMyStack<T> &&other)
	{
		*this = std::move(other);
	}

	~CMyStack()
	{
		Clear();
	}

	bool IsStackEmpty()const
	{
		return(m_size == 0);
	}

	size_t GetSize()const
	{
		return(m_size);
	}

	void Push(T const &element)
	{
		auto newNode = std::make_shared<Node>();
		newNode->value = element;

		if (m_top != nullptr)
		{
			newNode->next = m_top;
		}

		m_top = newNode;
		m_size++;
	}

	void Pop()
	{
		if (IsStackEmpty())
		{
			throw std::logic_error("Can't pop from empty stack.");
		}

		m_top = m_top->next;
		m_size--;
	}

	void Clear()
	{
		while (!IsStackEmpty())
		{
			Pop();
		}
	}

	T GetLastElement()const
	{
		if (IsStackEmpty())
		{
			throw std::logic_error("Can't get element from empty stack.");
		}
		return(m_top->value);
	}	

	CMyStack &operator = (CMyStack<T> const &stack)
	{
		if (this != std::addressof(stack))
		{
			CMyStack<T> tempStack;		
			auto node = stack.m_top;

			while (node != nullptr)
			{
				tempStack.Push(node->value);
				node = node->next;
			}
					
			if (tempStack.GetSize() == stack.GetSize())
			{
				Clear();
				auto node2 = tempStack.m_top;

				while (node2 != nullptr)
				{
					Push(node2->value);
					node2 = node2->next;
				}
			}			
		}	

		return *this;
	}

	CMyStack &operator = (CMyStack<T> &&stack)
	{
		if (this != std::addressof(stack))
		{
			Clear();
			m_top = stack.m_top;
			m_size = stack.GetSize();

			stack.m_top = nullptr;
			stack.m_size = 0;
		}

		return *this;
	}

	bool CMyStack<T>::operator == (CMyStack const &stack)const
	{
		if (this != std::addressof(stack))
		{
			auto node1 = m_top;
			auto node2 = stack.m_top;

			if (GetSize() != stack.GetSize())
			{
				return false;
			}

			while (node1 != nullptr)
			{
				if (node1->value != node2->value)
				{
					return false;
				}

				node1 = node1->next;
				node2 = node2->next;
			}
		}

		return true;
	}

	bool CMyStack<T>::operator != (CMyStack const &stack)const
	{
		return !(*this == stack);
	}

private:
	struct Node
	{
		T value;
		std::shared_ptr<Node> next = nullptr;
	};

	std::shared_ptr<Node> m_top = nullptr;
	size_t m_size = 0;
};
