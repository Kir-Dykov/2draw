#include "undo_stack.h"

template<typename T>
UndoStack<T>::UndoStack()
{
	head = nullptr;
	top = nullptr;
}


template<typename T>
UndoStack<T>::~UndoStack()
{
	remove_cur2end(head);
}

template<typename T>
void UndoStack<T>::truncate(Node* elem)
{
	Node* cur = elem;
	if (cur != nullptr)
	{
		if (cur->pPrev == nullptr)
		{
			head = nullptr;
			top = nullptr;
		}
		else
		{
			cur->pPrev->pNext = nullptr;
			Node* tmp = cur;
			while (cur->pNext != nullptr)
			{
				cur = cur->pNext;
				delete tmp;
				tmp = cur;
			}
			cur = nullptr;
		}
	}
}

template<typename T>
void UndoStack<T>::push_back(T elem)
{
	Node* tmp = new Node(elem);
	if (top != nullptr)
	{
		if (top->pNext != nullptr)
			remove_cur2end(top->pNext);
		tmp->pPrev = top;
		top->pNext = tmp;
		top = tmp;
	}
	else
	{
		head = tmp;
		top = tmp;
	}
}

template<typename T>
T UndoStack<T>::undo()
{
	if (top != nullptr)
	{
		T tmp = top->data;
		if (top->pPrev != nullptr)
			top = top->pPrev;
		return tmp;
	}
	else throw "Empty";
}

template<typename T>
T UndoStack<T>::redo()
{
	if (top != nullptr)
	{
		if (top->pNext != nullptr)
		{
			top = top->pNext;
		}
		return top->data;
	}
	else throw "Empty";
}