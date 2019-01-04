#pragma once
#include "Deque.h"
#include "DataNode.h"
#include "JavaIterator.h"
#include "Helper.h"
#include <string>

template <class T> class StaticDeque;

template <class T, class U>
class StaticDequeIterator : public JavaIterator<U> {
private:
	DataNode<T> *currentIter;
public:
	StaticDequeIterator(DataNode<T>*);
	StaticDequeIterator(StaticDeque<T> const&);
	~StaticDequeIterator();

	U next();
	bool hasNext() const;
};

template <typename T, typename U>
StaticDequeIterator<T, U>::StaticDequeIterator(DataNode<T> *initialNode) {
	currentIter = &(*initialNode);
}
template <typename T, typename U>
StaticDequeIterator<T, U>::StaticDequeIterator(StaticDeque<T> const& container): StaticDequeIterator(container.head) {
}
template <typename T, typename U>
StaticDequeIterator<T, U>::~StaticDequeIterator() {

}

template <typename T, typename U>
U StaticDequeIterator<T, U>::next() {
	if (currentIter == NULL) throw "Empty iterator!";

	U value = currentIter->value;
	currentIter = currentIter->next;

	return value;
}
template <typename T, typename U>
bool StaticDequeIterator<T, U>::hasNext() const {
	return currentIter != NULL;
}

template <class T>
class StaticDeque: public Deque<T> {
private:
    int emptyIntValue = -1;

	DataNode<T> *head;
	DataNode<T> *tail;

	int numberOfElements;

	void deleteElements();
public:
	typedef StaticDequeIterator<T, T&> iterator;

	friend class StaticDequeIterator<T, T&>;
	friend class StaticDequeIterator<T, T const&>;

	StaticDeque<T>& operator=(StaticDeque<T> const&);

	int size() const;
	char* toString() const;
	JavaIterator<T&>* createIterator();
	JavaIterator<T const&>* createIterator() const;

	bool pushBack(T const&);
	bool pushFront(T const&);
	T popBack();
	T popFront();
	T peekBack() const;
	T peekFront() const;
	T& peekBack();
	T& peekFront();

	StaticDeque();
	StaticDeque(StaticDeque<T> const&);
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
StaticDeque<T>::StaticDeque(StaticDeque<T> const& copyFrom) {
	DataNode<T> *currentCopy = copyFrom->tail;

	do {
		pushBack(currentCopy->value);
	} while ((currentCopy = currentCopy->prev) != NULL);
}
template <typename T>
StaticDeque<T>::~StaticDeque()
{
	deleteElements();
}
template <typename T>
void StaticDeque<T>::deleteElements() {
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
char* StaticDeque<T>::toString() const {
	DataNode<T> *current = head;
	char *description = new char[256]{ NULL };

	strcat(description, "StaticDeque\nHead ->");
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
JavaIterator<T&>* StaticDeque<T>::createIterator() {
	return new StaticDequeIterator<T, T&>(head);
}
template <typename T>
JavaIterator<T const&>* StaticDeque<T>::createIterator() const {
	return new StaticDequeIterator<T, T const&>(head);
}

template <typename T>
bool StaticDeque<T>::pushBack(T const& value) {
	DataNode<T> *newNode = new DataNode<T>(value);

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
	DataNode<T> *newNode = new DataNode<T>(value);

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

template <typename T>
StaticDeque<T>& StaticDeque<T>::operator=(StaticDeque<T> const& copyFrom) {
	deleteElements();

	StaticDeque(copyFrom);

	return this;
}