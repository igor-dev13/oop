#include "stdafx.h"
#include "../CMyStack/CMyStack.h"

struct EmptyStack
{
	CMyStack<int> intStack;
	CMyStack<std::string> stringStack;	
};

void FillCMyStackByInt(CMyStack<int> & other, size_t to)
{	
	for (size_t i = 0; i < to; i++)
	{
		other.Push((int)i);
	}	
};

void FillCMyStackByString(CMyStack<std::string> & other, size_t to)
{
	for (size_t i = 0; i < to; ++i)
	{
		other.Push(std::to_string(i));
	}
};

BOOST_FIXTURE_TEST_SUITE(Stack, EmptyStack)
	BOOST_AUTO_TEST_SUITE(Stack)
		BOOST_AUTO_TEST_CASE(empty_by_default)
		{
			BOOST_CHECK(intStack.IsStackEmpty());
			BOOST_CHECK(stringStack.IsStackEmpty());
		}

	BOOST_AUTO_TEST_CASE(can_push_elements)
	{
		intStack.Push(10);
		BOOST_CHECK(!intStack.IsStackEmpty());

		stringStack.Push("10");
		BOOST_CHECK(!stringStack.IsStackEmpty());
	}

	BOOST_AUTO_TEST_CASE(can_pop_elements)
	{
		intStack.Push(10);
		BOOST_CHECK(!intStack.IsStackEmpty());

		intStack.Pop();
		BOOST_CHECK(intStack.IsStackEmpty());

		stringStack.Push("10");
		BOOST_CHECK(!stringStack.IsStackEmpty());

		stringStack.Pop();
		BOOST_CHECK(stringStack.IsStackEmpty());
	}	

	BOOST_AUTO_TEST_CASE(can_get_last_element)
	{
		intStack.Push(10);
		BOOST_CHECK_EQUAL(intStack.GetLastElement(), 10);

		stringStack.Push("10");
		BOOST_CHECK_EQUAL(stringStack.GetLastElement(), "10");
	}

	BOOST_AUTO_TEST_CASE(can_get_size_of_stack)
	{
		intStack.Push(10);
		BOOST_CHECK_EQUAL(intStack.GetSize(), 1);

		stringStack.Push("10");
		BOOST_CHECK_EQUAL(stringStack.GetSize(), 1);
	}

	BOOST_AUTO_TEST_CASE(can_delete_all_elements_in_stack)
	{
		size_t currentSize = 10;
		size_t expectedSize = 0;

		FillCMyStackByInt(intStack, currentSize);
		BOOST_CHECK_EQUAL(intStack.GetSize(), currentSize);

		intStack.Clear();
		BOOST_CHECK_EQUAL(intStack.GetSize(), expectedSize);

		FillCMyStackByString(stringStack, currentSize);
		BOOST_CHECK_EQUAL(stringStack.GetSize(), currentSize);

		stringStack.Clear();
		BOOST_CHECK_EQUAL(stringStack.GetSize(), expectedSize);
	}

	BOOST_AUTO_TEST_CASE(can_be_created_by_copy_constructor)
	{
		intStack.Push(10);
		CMyStack<int> secondStack(intStack);
		BOOST_CHECK_EQUAL(secondStack.GetSize(), intStack.GetSize());
		BOOST_CHECK_EQUAL(secondStack.GetLastElement(), intStack.GetLastElement());
	}

	BOOST_AUTO_TEST_CASE(can_be_created_by_copy_assign_operator)
	{
		CMyStack<int> newIntStack1;
		CMyStack<std::string> newStringStack1;

		FillCMyStackByString(stringStack, 10);
		FillCMyStackByInt(intStack, 10);

		FillCMyStackByInt(newIntStack1, 20);
		FillCMyStackByString(newStringStack1, 20);

		BOOST_CHECK_EQUAL(newIntStack1.GetSize(), 20);	
		BOOST_CHECK_EQUAL(newStringStack1.GetSize(), 20);

		newIntStack1 = intStack;
		newStringStack1 = stringStack;

		BOOST_CHECK_EQUAL(newIntStack1.GetSize(), intStack.GetSize());
		BOOST_CHECK(newIntStack1 == intStack);

		BOOST_CHECK_EQUAL(newStringStack1.GetSize(), stringStack.GetSize());
		BOOST_CHECK(newStringStack1 == stringStack);
	}

	BOOST_AUTO_TEST_CASE(can_be_compared)
	{
		CMyStack<int> comparedIntStack;

		comparedIntStack.Push(10);
		intStack.Push(10);
		BOOST_CHECK(intStack == comparedIntStack);
		BOOST_CHECK_EQUAL(intStack != comparedIntStack, false);

		intStack.Push(22);
		comparedIntStack.Push(47);

		BOOST_CHECK(intStack != comparedIntStack);		
		BOOST_CHECK_EQUAL(intStack != comparedIntStack, true);

		CMyStack<std::string> comparedStringStack;

		comparedStringStack.Push("brown lazy fox");
		stringStack.Push("brown lazy fox");

		BOOST_CHECK(comparedStringStack == stringStack);

		stringStack.Push("This is a additional string list");
		BOOST_CHECK(comparedStringStack != stringStack);
	}

	BOOST_AUTO_TEST_CASE(can_not_be_assigned_by_the_same_object)
	{
		size_t currentSize = 10;
		FillCMyStackByString(stringStack, currentSize);
		FillCMyStackByInt(intStack, currentSize);

		CMyStack<int> prevIntStackState = intStack;
		BOOST_CHECK(prevIntStackState == intStack);

		BOOST_CHECK_EQUAL(intStack.GetSize(), 10);

		intStack = intStack;

		BOOST_CHECK_EQUAL(intStack.GetSize(), 10);
		BOOST_CHECK(intStack == prevIntStackState);

		CMyStack<std::string> prevStringStackState = stringStack;
		BOOST_CHECK(prevStringStackState == stringStack);

		BOOST_CHECK_EQUAL(stringStack.GetSize(), 10);

		stringStack = stringStack;

		BOOST_CHECK_EQUAL(stringStack.GetSize(), 10);
		BOOST_CHECK(stringStack == prevStringStackState);
	}

	BOOST_AUTO_TEST_CASE(can_be_created_by_moved_constructor)
	{
		size_t currentSize = 10;
		FillCMyStackByString(stringStack, currentSize);
		FillCMyStackByInt(intStack, currentSize);

		CMyStack<int> prevIntStackState = intStack;
		CMyStack<std::string> prevStringStackState = stringStack;

		CMyStack<int> newIntStack1(std::move(intStack));
		BOOST_CHECK(intStack.IsStackEmpty());
		BOOST_CHECK(newIntStack1 == prevIntStackState);

		CMyStack<std::string> newStringStack(std::move(stringStack));
		BOOST_CHECK(stringStack.IsStackEmpty());
		BOOST_CHECK(newStringStack == prevStringStackState);
	}

	BOOST_AUTO_TEST_CASE(can_not_be_moved_by_the_same_object)
	{
		size_t currentSize = 10;
		FillCMyStackByString(stringStack, currentSize);
		FillCMyStackByInt(intStack, currentSize);

		CMyStack<int> prevIntStackState = intStack;
		CMyStack<std::string> prevStringStackState = stringStack;

		intStack = std::move(intStack);
		BOOST_CHECK(intStack == prevIntStackState);
		BOOST_CHECK_EQUAL(intStack.GetSize(), 10);

		stringStack = std::move(stringStack);
		BOOST_CHECK(stringStack == prevStringStackState);
		BOOST_CHECK_EQUAL(stringStack.GetSize(), 10);
	}

	BOOST_AUTO_TEST_CASE(can_be_created_by_moved_assign_operator)
	{
		size_t currentSize = 10;
		FillCMyStackByString(stringStack, currentSize);
		FillCMyStackByInt(intStack, currentSize);

		CMyStack<int> prevIntStackState = intStack;
		CMyStack<std::string> prevStringStackState = stringStack;

		CMyStack<int> newIntStack = std::move(intStack);
		BOOST_CHECK(intStack.IsStackEmpty());
		BOOST_CHECK(newIntStack == prevIntStackState);

		CMyStack<std::string> newStringStack = std::move(stringStack);
		BOOST_CHECK(stringStack.IsStackEmpty());
		BOOST_CHECK(newStringStack == prevStringStackState);
	}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(throw_exception_if)

		BOOST_AUTO_TEST_CASE(pop_element_when_stack_is_empty)
		{
			BOOST_CHECK_THROW(intStack.Pop(), std::logic_error);
			BOOST_CHECK_THROW(stringStack.Pop(), std::logic_error);
		}

		BOOST_AUTO_TEST_CASE(getElement_from_empty_stack)
		{
			BOOST_CHECK_THROW(intStack.GetLastElement(), std::logic_error);
			BOOST_CHECK_THROW(stringStack.GetLastElement(), std::logic_error);
		}

	BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(can_be_destroyed)

		BOOST_AUTO_TEST_CASE(without_stack_overflow_exception)
		{
			CMyStack<int> intStack;
			FillCMyStackByInt(intStack, 200000);

			BOOST_CHECK_NO_THROW(intStack.~CMyStack());
		}

	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()