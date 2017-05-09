#pragma once
#include "PushPopContainer.h"
#include "DataNode.h"
#include "JavaIterator.h"
#include <string>

template <class T, class U>
class QueueIterator : public JavaIterator<U> {
private: 
	DataNode<T> currentIter;
public:
	QueueIterator(DataNode<T>*);
	~QueueIterator();

	U next();
	bool hasNext() const;
};

template <typename T, typename U>
QueueIterator<T, U>::QueueIterator(DataNode<T> *initialNode) {
	currentNode = initialNode;
}
template <typename T, typename U>
QueueIterator<T, U>::~QueueIterator() {

}

template <typename T, typename U>
U QueueIterator<T, U>::next() {
	T value = NULL;

	if (currentIter == NULL) return value;
	
	value = currentIter->value;
	currentIter = currentIter->next;

	return value;
}
template <typename T, typename U>
bool QueueIterator<T, U>::hasNext() const {
	return currentIter != NULL &&
		currentIter->next != NULL;
}

template <class T>
class Queue: public PushPopContainer<T> {
private:
	DataNode<T> *head;
	DataNode<T> *tail;

	int numberOfElements;

	void deleteElements();
public:
	Queue<T>& operator=(Queue<T> const&);

	int size() const;
	char* toString() const;
	JavaIterator<T&>* createIterator();
	JavaIterator<T const&>* createIterator() const;

	T pop();
	T peek() const;
	T& peek();
	bool push(T const&);

	Queue();
	Queue(Queue<T> const&);
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
Queue<T>::Queue(Queue<T> const& copyFrom) {
	DataNode<T> *currentCopy = copyFrom->tail;

	do {
		push(currentCopy->value);
	} while ((currentCopy = currentCopy->prev) != NULL);
}
template <typename T>
Queue<T>::~Queue()
{
	deleteElements();
}
template <typename T>
void Queue<T>::deleteElements() {
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
int Queue<T>::size() const {
	return numberOfElements;
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
JavaIterator<T&>* Queue<T>::createIterator() {
	return new QueueIterator<T, T&>(head);
}
template <typename T>
JavaIterator<T const&>* Queue<T>::createIterator() const {
	return new QueueIterator<T, T const&>(head);
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
Queue<T>& Queue<T>::operator=(Queue<T> const& copyFrom) {
	deleteElements();

	Queue(copyFrom);

	return this;
}



