#pragma once
#include "PushPopContainer.h"
#include "DataNode.h"
#include <string>

template <class T>
class Queue: public PushPopContainer<T> {
private:
	DataNode<T> *head;
	DataNode<T> *tail;

	int numberOfElements;
public:
	int size() const;
	bool isEmpty() const;
	char* toString() const;

	T pop();
	T peek() const;
	T& peek();
	bool push(T const&);

	Queue();
	~Queue();
};
template <typename T>
Queue<T>::Queue()
{
	head = NULL;
	tail = NULL;
	numberOfElements = 0;
}

template <typename T>
int Queue<T>::size() const {
	return numberOfElements;
}

template <typename T>
bool Queue<T>::isEmpty() const {
	return numberOfElements == 0;
}

template <typename T>
char* Queue<T>::toString() const {
	DataNode<T> *current = head;
	char *description = new char[256]{ NULL };

	strcat(description, "Queue\nHead ->");
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
T Queue<T>::pop() {
	if (isEmpty()) throw "Queue is empty!";

	T value = head->value;

	DataNode<T> *popedElement = head;
	head = head->next;

	delete popedElement;

	numberOfElements -= 1;

	if (isEmpty()) tail = NULL;
	else head->prev = NULL;

	return value;
}
template <typename T>
T Queue<T>::peek() const {
	if (isEmpty()) throw "Queue is empty!";
	return head->value;
}

template <typename T>
T& Queue<T>::peek() {
	if (isEmpty()) throw "Queue is empty!";
	return &(head->value);
}

template <typename T>
bool Queue<T>::push(T const& value) {
	DataNode<T> *newNode = new DataNode<T>();

	newNode->value = value;

	if (isEmpty()) {
		head = newNode;
		tail = newNode;

		numberOfElements += 1;

		return true;
	}

	newNode->prev = tail;
	tail->next = newNode;
	tail = newNode;

	numberOfElements += 1;

	return true;
}


template <typename T>
Queue<T>::~Queue()
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

