#pragma once
#include "PushPopContainer.h"
#include "DataNode.h"
#include <string>

template <class T>
class Stack: public PushPopContainer<T> {
private:
	DataNode<T> *head;
	int numberOfElements;
public:
	int size() const;
	bool isEmpty() const;
	char* toString() const;

	T peek() const;
	T& peek();
	T pop();
	bool push(T const&);

	Stack();
	~Stack();
};

template <typename T>
Stack<T>::Stack()
{
	head = NULL;
	numberOfElements = 0;
}

template <typename T>
int Stack<T>::size() const {
	return numberOfElements;
}

template <typename T>
bool Stack<T>::isEmpty() const {
	return numberOfElements == 0;
}

template <typename T>
char* Stack<T>::toString() const {
	DataNode<T> *current = head;
	char *description = new char[256]{ NULL };

	strcat(description, "Stack\nHead ->");
	do {
		if (current != head) {
			strcat(description, ", ");
		}
		char *val = new char[256]{ NULL };
		itoa(current->value, val, 10);

		strcat(description, val);
		current = current->next;

		delete val;
	} while (current != NULL);

	strcat(description, "<- Tail");

	delete current;

	return description;
}

template <typename T>
T Stack<T>::pop() {
	if (isEmpty()) throw "Stack is empty!";

	T value = head->value;

	DataNode<T> *popedElement = head;
	head = head->next;

	delete popedElement;

	numberOfElements -= 1;

	if (!isEmpty()) head->prev = NULL;

	return value;
}

template <typename T>
T Stack<T>::peek() const {
	if (isEmpty()) throw "Stack is empty!";

	return head->value;
}

template <typename T>
T& Stack<T>::peek() {
	if (isEmpty()) throw "Stack is empty!";

	return head->value;
}

template <typename T>
bool Stack<T>::push(T const& value) {
	DataNode<T> *newNode = new DataNode<T>();

	newNode->value = value;

	if (!isEmpty()) {
		newNode->next = head;
		head->prev = newNode;
	}

	head = newNode;

	numberOfElements += 1;

	return true;
}


template <typename T>
Stack<T>::~Stack()
{
	DataNode<T> *current;
	DataNode<T> *next = head;

	while (next != NULL) {
		current = next;
		next = current->next;
		delete current;
	}

	delete next;
}
