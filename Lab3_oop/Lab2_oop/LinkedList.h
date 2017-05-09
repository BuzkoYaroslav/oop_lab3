#pragma once
#include "InsertableContainer.h"
#include "PushPopContainer.h"
#include "DataNode.h"
#include "Helper.h"
#include <string>

template <class T, class U>
class LinkedListIterator : public JavaIterator<U> {
private:
	DataNode<T> *currentIter;
public:
	LinkedListIterator(DataNode<T>*);
	~LinkedListIterator();

	U next();
	bool hasNext() const;
};

template <typename T, typename U>
LinkedListIterator<T, U>::LinkedListIterator(DataNode<T> *initialNode) {
	currentNode = initialNode;
}
template <typename T, typename U>
LinkedListIterator<T, U>::~LinkedListIterator() {

}

template <typename T, typename U>
U LinkedListIterator<T, U>::next() {
	T value = NULL; 

	if (currentIter == NULL) return value;
	
	value = currentIter->value;
	currentIter = current->next;

	return value;
}
template <typename T, typename U>
bool LinkedListIterator<T, U>::hasNext() const {
	return currentIter != NULL &&
		currentIter->next != NULL;
}

template <class T>
class LinkedList: public InsertableContainer<T>, public PushPopContainer<T>
{
private:
	const int emptyIntValue = -1;

	DataNode<T> *head;
	DataNode<T> *tail;

	int numberOfElements;

	bool checkIndex(int) const;

	DataNode<T>* elementAtIndex(int) const;
public:
	// Container
	int size() const;
	char* toString() const;
	JavaIterator<T&>* createIterator();
	JavaIterator<T const&>* createIterator() const;

	// PushPopContainer
	bool push(T const&);
	T peek() const;
	T& peek();
	T pop();

	// IndexedContainer
	T get(int) const;
	T& get(int);
	void set(int, T const&);

	// Deque
	bool pushFront(T const&);
	bool pushBack(T const&);
	T popFront();
	T popBack();
	T peekFront() const;
	T peekBack() const;
	T& peekFront();
	T& peekBack();

	// InsertableContainer
	bool insertAt(int, T const&);
	T removeAt(int);

	LinkedList();
	LinkedList(LinkedList<T> const&);
	~LinkedList();
};

template <typename T>
LinkedList<T>::LinkedList()
{
	head = NULL;
	tail = NULL;

	numberOfElements = 0;
}
template <typename T>
LinkedList<T>::LinkedList(LinkedList<T> const& copyFrom) {
	DataNode<T> *currentCopy = copyFrom->tail;

	do {
		push(currentCopy->value);
	} while ((currentCopy = currentCopy->prev) != NULL);
}
template <typename T>
LinkedList<T>::~LinkedList()
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

// Container
template <typename T>
int LinkedList<T>::size() const {
	return numberOfElements;
}
template <typename T>
char* LinkedList<T>::toString() const {
	DataNode<T> *current = head;
	char *description = new char[256]{ NULL };

	strcat(description, "Linked list\nHead ->");
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
JavaIterator<T&>* LinkedList<T>::createIterator() {
	return new LinkedListIterator<T, T&>(head);
}
template <typename T>
JavaIterator<T const&>* LinkedList<T>::createIterator() const {
	return new LinkedListIterator<T, T const&>(head);
}

// PushPopContainer
template <typename T>
T LinkedList<T>::peek() const {
	if (isEmpty()) return emptyIntValue;

	return tail->value;
}
template <typename T>
T& LinkedList<T>::peek() {
	if (isEmpty()) return emptyIntValue;

	return &(tail->value);
}
template <typename T>
T LinkedList<T>::pop() {
	if (isEmpty()) return emptyIntValue;

	DataNode<T> *popedElement = tail;
	T value = popedElement->value;
	tail->prev->next = NULL;
	tail = tail->prev;

	numberOfElements -= 1;

	if (isEmpty()) head = NULL;

	delete popedElement;

	return value;
}
template <typename T>
bool LinkedList<T>::push(T const& value) {
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

// Deque
template <typename T>
bool LinkedList<T>::pushFront(T const& value) {
	DataNode<T> *newNode = new DataNode<T>();

	newNode->value = value;

	if (isEmpty()) {
		head = newNode;
		tail = newNode;

		numberOfElements += 1;

		return true;
	}

	head->prev = newNode;
	newNode->next = head;
	head = newNode;

	numberOfElements += 1;

	return true;
}
template <typename T>
bool LinkedList<T>::pushBack(T const& value) {
	return push(value);
}
template <typename T>
T LinkedList<T>::popFront() {
	if (isEmpty()) return emptyIntValue;

	DataNode<T> *popedElement = head;
	T value = popedElement->value;
	head = head->next;

	delete popedElement;

	numberOfElements -= 1;

	if (isEmpty()) tail = NULL;
	else head->prev = NULL;

	return value;

}
template <typename T>
T LinkedList<T>::popBack() {
	return pop();
}
template <typename T>
T LinkedList<T>::peekFront() const {
	if (isEmpty()) return emptyIntValue;

	return head->value;
}
template <typename T>
T LinkedList<T>::peekBack() const {
	return peek();
}
template <typename T>
T& LinkedList<T>::peekFront() {
	if (isEmpty()) return emptyIntValue;

	return &(head->value);
}
template <typename T>
T& LinkedList<T>::peekBack() {
	return peek();
}

// IndexedContainer 
template <typename T>
T LinkedList<T>::get(int index) const {
	DataNode<T> *element = elementAtIndex(index);

	return element == NULL ? emptyIntValue : element->value;
}
template <typename T>
T& LinkedList<T>::get(int index) {
	DataNode<T> *element = elementAtIndex(index);

	return element == NULL ? &emptyIntValue : &(element->value);
}
template <typename T>
void LinkedList<T>::set(int index, T const& value) {
	if (index == size()) {
		push(value);
	}
	else {
		DataNode<T> *element = elementAtIndex(index);

		if (element == NULL) return;

		element->value = value;
	}
}

// InsertableContainer
template <typename T>
bool LinkedList<T>::insertAt(int index, T const& value) {
	if (index == size()) {
		return push(value);
	}
	else if (index == 0) {
		return pushFront(value);
	}
	else {
		DataNode<T> *element = elementAtIndex(index);

		if (element == NULL) return false;

		DataNode<T> *newNode = new DataNode<T>();
		newNode->value = value;

		newNode->prev = element->prev;
		element->prev->next = newNode;
		newNode->next = element;
		element->prev = newNode;

		numberOfElements += 1;

		return true;
	}
}
template <typename T>
T LinkedList<T>::removeAt(int index) {
	if (isEmpty()) return emptyIntValue;
	if (checkIndex(index)) return emptyIntValue;

	if (index == 0) {
		return popFront();
	}
	else if (index == size() - 1) {
		return pop();
	}
	else {
		DataNode<T> *element = elementAtIndex(index);

		element->prev->next = element->next;
		element->next->prev = element->prev;

		T value = element->value;

		numberOfElements -= 1;

		return value;
	}
}

template <typename T>
bool LinkedList<T>::checkIndex(int index) const {
	return (index < 0 ||
		index >= size());
}
template <typename T>
DataNode<T>* LinkedList<T>::elementAtIndex(int index) const {
	if (isEmpty()) return NULL;
	if (checkIndex(index)) return NULL;

	bool ltr = index < size() - 1 - index;
	int indexNew = ltr ? index : size() - 1 - index;

	DataNode<T> *current = ltr ? head : tail;

	for (int i = 0; i < indexNew; i++,
		ltr ? current = current->next : current = current->prev) {
	};

	return current;
}