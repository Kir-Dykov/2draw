#pragma once

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