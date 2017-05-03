#include "stdafx.h"
#include "Stack.h"
#include <string>


Stack::Stack()
{
	head = NULL;
	numberOfElements = 0;
}

int Stack::size() const {
	return numberOfElements;
}
bool Stack::isEmpty() const {
	return numberOfElements == 0;
}
char* Stack::toString() const {
	DataNode *current = head;
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

int Stack::pop() {
	if (isEmpty()) throw "Stack is empty!";

	int value = head->value;

	DataNode *popedElement = head;
	head = head->next;
	
	delete popedElement;

	numberOfElements -= 1;

	if (!isEmpty()) head->prev = NULL;

	return value;
}
int Stack::peek() const {
	if (isEmpty()) throw "Stack is empty!";

	return head->value;
}
bool Stack::push(int value) {
	DataNode *newNode = new DataNode();

	newNode->value = value;

	if (!isEmpty()) {
		newNode->next = head;
		head->prev = newNode;
	}

	head = newNode;

	numberOfElements += 1;

	return true;
}


Stack::~Stack()
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
