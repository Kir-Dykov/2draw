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

	//delete every element above (including) given Node
	void truncate(Node*);

	// the last element we store
	Node* head;

	// the element we "looking" at
	Node* top;

public:
	
	UndoStack();
	~UndoStack();

	// add element after top
	void push_back(T);

	// read the top value, move top one step down
	T undo();

	// move top one step up, read the top value
	T redo();
	
	
};

template<typename T>
UndoStack<T>::UndoStack() {
	head = nullptr;
	top = nullptr;
}

template<typename T>
UndoStack<T>::~UndoStack() {
	truncate(head);
}

template<typename T>
void UndoStack<T>::truncate(Node* elem) {
	Node* cur = elem;
	if (cur != nullptr)
	{
		if (cur->pPrev != nullptr) {
			cur->pPrev->pNext = nullptr;
		}

		//delete everything to the end
		Node* tmp = cur;
		while (cur->pNext != nullptr)
		{
			cur = cur->pNext;
			delete tmp;
			tmp = cur;
		}
		delete cur;
		
	}
}

template<typename T>
void UndoStack<T>::push_back(T elem) {

	Node* tmp = new Node(elem);

	if (top != nullptr)
	{
		if (top->pNext != nullptr)
			truncate(top->pNext);
		tmp->pPrev = top;
		top->pNext = tmp;
	}

	head = tmp;
	top = tmp;

}

template<typename T>
T UndoStack<T>::undo() {
	T tmp = top->data;
	if (top->pPrev != nullptr)
		top = top->pPrev;
	return tmp;
}

template<typename T>
T UndoStack<T>::redo() {
	if (top->pNext != nullptr)
		top = top->pNext;
	return top->data;
}