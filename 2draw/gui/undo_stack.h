#pragma once
#include <string>
#include "action.h"

using namespace std;

template<typename T>
class UndoStack {
private:
	class Node {
	public:
		Node* pNext;
		Node* pPrev;
		T data;

		Node(T data = T(), Node* pNext = nullptr, Node* pPrev = nullptr) {
			this->data = data;
			this->pNext = pNext;
			this->pPrev = pPrev;
		}
	};
public:
	Node* head;
	Node* top;

	UndoStack();
	~UndoStack();

	void push_back(T);

	T undo();
	T redo();
	//удаление с текущего элемента и до конца
	void truncate(Node*);
};

template<typename T>
UndoStack<T>::UndoStack()
{
	head = nullptr;
	top = nullptr;
	push_back(T());
}

template<typename T>
UndoStack<T>::~UndoStack()
{
	truncate(head);
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
			truncate(top->pNext);
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
	T tmp = top->data;
	if (top->pPrev != nullptr)
		top = top->pPrev;
	return tmp;
}

template<typename T>
T UndoStack<T>::redo()
{
	if (top->pNext != nullptr)
	{
		top = top->pNext;
	}
	return top->data;
}