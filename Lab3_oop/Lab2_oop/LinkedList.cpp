#include "stdafx.h"
#include "LinkedList.h"
#include <string>


LinkedList::LinkedList()
{
	head = NULL;
	tail = NULL;

	numberOfElements = 0;
}

// Container
int LinkedList::size() const {
	return numberOfElements;
}
bool LinkedList::isEmpty() const {
	return numberOfElements == 0;
}
char* LinkedList::toString() const {
	DataNode *current = head;
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

// PushPopContainer
int LinkedList::peek() const {
	if (isEmpty()) return emptyIntValue;

	return tail->value;
}
int LinkedList::pop() {
	if (isEmpty()) return emptyIntValue;

	DataNode *popedElement = tail;
	int value = popedElement->value;
	tail->prev->next = NULL;
	tail = tail->prev;

	numberOfElements -= 1;

	if (isEmpty()) head = NULL;

	delete popedElement;

	return value;
}
bool LinkedList::push(int value) {
	DataNode *newNode = new DataNode();

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
bool LinkedList::pushFront(int value) {
	DataNode *newNode = new DataNode();

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
bool LinkedList::pushBack(int value) {
	return push(value);
}
int LinkedList::popFront() {
	if (isEmpty()) return emptyIntValue;

	DataNode *popedElement = head;
	int value = popedElement->value;
	head = head->next;

	delete popedElement;

	numberOfElements -= 1;

	if (isEmpty()) tail = NULL;
	else head->prev = NULL;

	return value;

}
int LinkedList::popBack() {
	return pop();
}
int LinkedList::peekFront() const {
	if (isEmpty()) return emptyIntValue;

	return head->value;
}
int LinkedList::peekBack() const {
	return peek();
}

// IndexedContainer 
int LinkedList::get(int index) const {
	DataNode *element = elementAtIndex(index);

	return element == NULL ? emptyIntValue : element->value;
}
void LinkedList::set(int index, int value) {
	if (index == size()) {
		push(value);
	}
	else {
		DataNode *element = elementAtIndex(index);
		
		if (element == NULL) return;

		element->value = value;
	}
}

// InsertableContainer
bool LinkedList::insertAt(int index, int value) {
	if (index == size()) {
		return push(value);
	}
	else if (index == 0) {
		return pushFront(value);
	}
	else {
		DataNode *element = elementAtIndex(index);

		if (element == NULL) return false;

		DataNode *newNode = new DataNode();
		newNode->value = value;

		newNode->prev = element->prev;
		element->prev->next = newNode;
		newNode->next = element;
		element->prev = newNode;

		numberOfElements += 1;

		return true;
	}
}
int LinkedList::removeAt(int index) {
	if (isEmpty()) return emptyIntValue;
	if (checkIndex(index)) return emptyIntValue;

	if (index == 0) {
		return popFront();
	}
	else if (index == size() - 1) {
		return pop();
	}
	else {
		DataNode *element = elementAtIndex(index);

		element->prev->next = element->next;
		element->next->prev = element->prev;

		int value = element->value;

		numberOfElements -= 1;

		return value;
	}
}

bool LinkedList::checkIndex(int index) const {
	return (index < 0 ||
		index >= size());
}

LinkedList::~LinkedList()
{
	DataNode *current;
	DataNode *next = head;

	while (next != NULL) {
		current = next;
		next = current->next;
		delete current;
	}

	delete next;
}

DataNode* LinkedList::elementAtIndex(int index) const {
	if (isEmpty()) return NULL;
	if (checkIndex(index)) return NULL;

	bool ltr = index < size() - 1 - index;
	int indexNew = ltr ? index : size() - 1 - index;

	DataNode *current = ltr ? head : tail;

	for (int i = 0; i < indexNew; i++,
		ltr ? current = current->next : current = current->prev) {
	};

	return current;
}