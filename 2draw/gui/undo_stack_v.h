#pragma once
#include <string>
#include "action.h"
#include <vector>

using namespace std;

template<typename T>
class UndoStack_V {
public:
	vector <T> stack;
	int top = -1;

	void push_back(T);

	T undo();
	T redo();

	void truncate(int); //Удаление элемента в данной позиции
};

template<typename T>
void UndoStack_V<T>::truncate(int pos)
{
	vector<T>::iterator it = stack.begin() + pos;
	stack.erase(it);
}

template<typename T>
void UndoStack_V<T>::push_back(T elem)
{
	while (top != stack.size() - 1) {
		stack.erase(stack.end());
	}
	stack.push_back(elem);
	top++;
}

template<typename T>
T UndoStack_V<T>::undo()
{
	if (stack.size != 0) {
		if (top != 0)
			top--;
		return stack[top];
	}
	else
		return T();
}

template<typename T>
T UndoStack_V<T>::redo()
{
	if (stack.size() != 0) {
		if (top != stack.size() - 1) {
			top++;
		}
		return stack[top];
	}
	else
		return T();
}