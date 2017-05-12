#pragma once
#include "PushPopContainer.h"
#include "DataNode.h"
#include "JavaIterator.h"
#include "Helper.h"
#include <sstream>
#include <string>
using namespace std;

template <class T, class U>
class StackIterator : public JavaIterator<U> {
private:
	DataNode<T> *currentIter;
public:
	StackIterator(DataNode<T>*);
	~StackIterator();

	U next();
	bool hasNext() const;
};

template <typename T, typename U>
StackIterator<T, U>::StackIterator(DataNode<T> *initialNode) {
	currentIter = &(*initialNode);
}
template <typename T, typename U>
StackIterator<T, U>::~StackIterator() {

}

template <typename T, typename U>
bool StackIterator<T, U>::hasNext() const {
	return currentIter != NULL;
}
template <typename T, typename U>
U StackIterator<T, U>::next() {
	if (currentIter == NULL) throw "Empty iterator";
	
	U val = currentIter->value;

	currentIter = currentIter->next;

	return val;
}

template <class T>
class Stack: public PushPopContainer<T> {
private:
	DataNode<T> *head;
	int numberOfElements;

	void deleteElements();
public:
	Stack<T>& operator=(Stack<T> const&);

	int size() const;
	char* toString() const;
	JavaIterator<T&>* createIterator();
	JavaIterator<T const&>* createIterator() const;

	T peek() const;
	T& peek();
	T pop();
	bool push(T const&);

	Stack();
	Stack(Stack<T> const&);
	~Stack();
};

template <typename T>
Stack<T>::Stack()
{
	head = NULL;
	numberOfElements = 0;
}
template <typename T>
Stack<T>::Stack(Stack<T> const& copyFrom) {
	DataNode<T> *currentCopy = copyFrom.head;
	DataNode<T> *current = NULL, *prev = NULL;

	do {
		if (current == NULL) {
			head = new DataNode<T>(currentCopy->value);
			current = head;
		}
		else {
			prev = current;
			current = new DataNode<T>(currentCopy->value);

			prev->next = current;
			current->prev = prev;
		}
	} while ((currentCopy = currentCopy->next) != NULL);

	numberOfElements = copyFrom.numberOfElements;
}
template <typename T>
Stack<T>::~Stack()
{
	deleteElements();
}
template <typename T>
void Stack<T>::deleteElements() {
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
int Stack<T>::size() const {
	return numberOfElements;
}
template <typename T>
char* Stack<T>::toString() const {
	DataNode<T> *current = head;
	char *description = new char[256]{ NULL };

	strcat(description, "Stack\nHead ->");
	stringstream stream;
	do {
		if (current != head) {
			strcat(description, ", ");
		}
		char *val = new char[256]{ NULL };

		stream << current->value;
		stream >> val;

		strcat(description, val);

		stream.clear();

		current = current->next;

		delete val;
	} while (current != NULL);

	strcat(description, "<- Tail");

	delete current;

	return description;
}
template <typename T>
JavaIterator<T&>* Stack<T>::createIterator() {
	return new StackIterator<T, T&>(head);
}
template <typename T>
JavaIterator<T const&>* Stack<T>::createIterator() const {
	return new StackIterator<T, T const&>(head);
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
	DataNode<T> *newNode = new DataNode<T>(value);

	if (!isEmpty()) {
		newNode->next = head;
		head->prev = newNode;
	}

	head = newNode;

	numberOfElements += 1;

	return true;
}

template <typename T>
Stack<T>& Stack<T>::operator=(Stack<T> const& copyFrom) {
	deleteElements();

	Stack(copyFrom);

	return this;
}




