#pragma once
#include "Deque.h"
#include "DataNode.h"
#include <string>

template <class T>
class StaticDeque: public Deque<T> {
private:
    int emptyIntValue = -1;

	DataNode<T> *head;
	DataNode<T> *tail;

	int numberOfElements;
public:
	int size() const;
	bool isEmpty() const;
	char* toString() const;

	bool pushBack(T const&);
	bool pushFront(T const&);
	T popBack();
	T popFront();
	T peekBack() const;
	T peekFront() const;
	T& peekBack();
	T& peekFront();

	StaticDeque();
	~StaticDeque();
};

template <typename T>
StaticDeque<T>::StaticDeque()
{
	head = NULL;
	tail = NULL;
	numberOfElements = 0;
}

template <typename T>
StaticDeque<T>::~StaticDeque()
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

template <typename T>
int StaticDeque<T>::size() const {
	return numberOfElements;
}

template <typename T>
bool StaticDeque<T>::isEmpty() const {
	return numberOfElements == 0;
}

template <typename T>
char* StaticDeque<T>::toString() const {
	DataNode<T> *current = head;
	char *description = new char[256]{ NULL };

	strcat(description, "StaticDeque\nHead ->");
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
bool StaticDeque<T>::pushBack(T const& value) {
	DataNode<T> *newNode = new DataNode<T>();

	newNode->value = value;

	if (isEmpty()) {
		head = newNode;
		tail = newNode;
	}
	else {
		newNode->prev = tail;
		tail->next = newNode;
		tail = newNode;
	}

	numberOfElements += 1;

	return true;
}

template <typename T>
bool StaticDeque<T>::pushFront(T const& value) {
	DataNode<T> *newNode = new DataNode<T>();

	newNode->value = value;

	if (isEmpty()) {
		head = newNode;
		tail = newNode;
	}
	else {
		head->prev = newNode;
		newNode->next = head;
		head = newNode;
	}

	numberOfElements += 1;

	return true;
}

template <typename T>
T StaticDeque<T>::peekBack() const {
	if (isEmpty()) return emptyIntValue;

	return tail->value;
}

template <typename T>
T StaticDeque<T>::peekFront() const {
	if (isEmpty()) return emptyIntValue;

	return head->value;
}

template <typename T>
T& StaticDeque<T>::peekBack() {
	if (isEmpty()) return emptyIntValue;

	return tail->value;
}

template <typename T>
T& StaticDeque<T>::peekFront() {
	if (isEmpty()) return emptyIntValue;

	return head->value;
}

template <typename T>
T StaticDeque<T>::popBack() {
	if (isEmpty()) return NULL;

	T value = tail->value;
	if (size() == 1) {
		delete tail;

		tail = NULL;
		head = NULL;
	}
	else {
		DataNode<T> *popedElement = tail;
		tail = tail->prev;
		tail->next = NULL;

		delete popedElement;
	}

	numberOfElements -= 1;

	return value;
}

template <typename T>
T StaticDeque<T>::popFront() {
	if (isEmpty()) return NULL;

	T value = tail->value;
	if (size() == 1) {
		delete tail;

		tail = NULL;
		head = NULL;
	}
	else {
		DataNode<T> *popedElement = head;
		head = head->next;
		head->prev = NULL;

		delete popedElement;
	}

	numberOfElements -= 1;

	return value;
}