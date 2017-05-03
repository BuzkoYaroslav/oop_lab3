#include "stdafx.h"
#include "StaticDeque.h"
#include <string>

StaticDeque::StaticDeque()
{
	head = NULL;
	tail = NULL;
	numberOfElements = 0;
}
StaticDeque::~StaticDeque()
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

int StaticDeque::size() const {
	return numberOfElements;
}
bool StaticDeque::isEmpty() const {
	return numberOfElements == 0;
}
char* StaticDeque::toString() const {
	DataNode *current = head;
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

bool StaticDeque::pushBack(int value) {
	DataNode *newNode = new DataNode();

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
bool StaticDeque::pushFront(int value) {
	DataNode *newNode = new DataNode();

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

int StaticDeque::peekBack() const {
	if (isEmpty()) return emptyIntValue;

	return tail->value;
}
int StaticDeque::peekFront() const {
	if (isEmpty()) return emptyIntValue;

	return head->value;
}

int StaticDeque::popBack() {
	if (isEmpty()) return emptyIntValue;

	int value = tail->value;
	if (size() == 1) {
		delete tail;

		tail = NULL;
		head = NULL;
	}
	else {
		DataNode *popedElement = tail;
		tail = tail->prev;
		tail->next = NULL;

		delete popedElement;
	}

	numberOfElements -= 1;

	return value;
}
int StaticDeque::popFront() {
	if (isEmpty()) return emptyIntValue;

	int value = tail->value;
	if (size() == 1) {
		delete tail;

		tail = NULL;
		head = NULL;
	}
	else {
		DataNode *popedElement = head;
		head = head->next;
		head->prev = NULL;

		delete popedElement;
	}

	numberOfElements -= 1;

	return value;
}