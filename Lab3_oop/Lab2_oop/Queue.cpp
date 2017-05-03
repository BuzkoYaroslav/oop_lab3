#include "stdafx.h"
#include "Queue.h"
#include <string>

Queue::Queue()
{
	head = NULL;
	tail = NULL;
	numberOfElements = 0;
}

int Queue::size() const {
	return numberOfElements;
}
bool Queue::isEmpty() const {
	return numberOfElements == 0;
}
char* Queue::toString() const {
	DataNode *current = head;
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

int Queue::pop() {
	if (isEmpty()) throw "Queue is empty!";

	int value = head->value;

	DataNode *popedElement = head;
	head = head->next;
	
	delete popedElement;

	numberOfElements -= 1;

	if (isEmpty()) tail = NULL;
	else head->prev = NULL;

	return value;
}
int Queue::peek() const {
	if (isEmpty()) throw "Queue is empty!";
	return head->value;
}
bool Queue::push(int value) {
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


Queue::~Queue()
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

