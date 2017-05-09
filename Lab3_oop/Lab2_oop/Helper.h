#pragma once
#include "stdafx.h"
#include "DataNode.h"

template <class T, class C>
class Converter {
public:
	static DataNode<C>* nodeListCopy(DataNode<T> *headNode) {
		DataNode<C> *newHead = new DataNode<C>(headNode->value);
		DataNode<C> *current = newHead, *prev = NULL;
		DataNode<T> *currentOld = headNode->next;

		while (current != NULL) {
			current->prev = prev;
			prev = current;
			current = new DataNode<C>(currentOld->value);
			currentOld = currentOld->next;
		}

		return newHead;
	};
};