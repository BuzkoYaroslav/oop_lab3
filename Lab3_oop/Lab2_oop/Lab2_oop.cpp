// Lab2_oop.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Container.h"
#include "PushPopContainer.h"
#include "IndexedContainer.h"
#include "InsertableContainer.h"
#include "Deque.h"
#include "Stack.h"
#include "Queue.h"
#include "StaticArray.h"
#include "StaticDeque.h"
#include "StaticDeque.h"
#include "LinkedList.h"
#include <iostream>
#include <string>
#include <conio.h>
using namespace std;

const int countElements = 15;
const int countPopping = 5;
const int countPushFront = 5;

int main()
{
	/*PushPopContainer **arr1 = new PushPopContainer*[3];
	IndexedContainer **arr2 = new IndexedContainer*[2];
	Deque **arr3 = new Deque*[3];

	arr1[0] = new Stack();
	arr1[1] = new Queue();
	arr1[2] = new LinkedList();

	arr2[0] = new StaticArray(100);
	arr2[1] = new LinkedList();
	
	arr3[0] = new StaticDeque();
	arr3[1] = new LinkedList();

	for (int i = 1; i <= countElements; i++) {
		arr1[0]->push(i);
		arr1[1]->push(i);
		arr1[2]->push(i);
	}

	cout << arr1[0]->toString() << endl;
	cout << arr1[1]->toString() << endl;
	cout << arr1[2]->toString() << endl;

	cout << "Popping first n elements, n = " << countPopping << endl;
	
	for (int i = 0; i < countPopping; i++) {
		cout << "Stage " << i + 1 << endl;
		cout << "Popped from stack = " << arr1[0]->pop() << endl;
		cout << "Popped from queue = " << arr1[1]->pop() << endl;
		cout << "Popped from linked list = " << arr1[2]->pop() << endl;
	}

	cout << "After popping" << endl;

	cout << arr1[0]->toString() << endl;
	cout << arr1[1]->toString() << endl;
	cout << arr1[2]->toString() << endl;

	for (int i = 1; i <= countElements; i++) {
		arr2[0]->set(i - 1, i);
		arr2[1]->set(i - 1, i);
	}

	cout << arr2[0]->toString() << endl;
	cout << arr2[1]->toString() << endl;

	cout << "Input element index:" << endl;
	int index = 0;
	cin >> index;

	cout << "Element" << index << " from static array = " << arr2[0]->get(index) << endl;
	cout << "Element" << index << " from linked list = " << arr2[1]->get(index) << endl;

	for (int i = 0; i < countElements; i++) {
		arr3[0]->pushBack(i);
		arr3[1]->pushBack(i);
	}

	cout << arr3[0]->toString() << endl;
	cout << arr3[1]->toString() << endl;

	cout << "Front pushing: " << endl;

	for (int i = 0; i < countPushFront; i++) {
		arr3[0]->pushFront(countElements + i);
		arr3[1]->pushFront(countElements + i);
	}

	cout << "After pushing:" << endl;

	cout << arr3[0]->toString() << endl;
	cout << arr3[1]->toString() << endl;

	cout << "Back popping: " << endl;

	for (int i = 0; i < countPopping; i++) {
		cout << "Stage " << i + 1 << endl;
		cout << "Popped from static array = " << arr3[0]->popBack() << endl;
		cout << "Popped from linked list = " << arr3[1]->popBack() << endl;
	}

	cout << "After popping: " << endl;

	cout << arr3[0]->toString() << endl;
	cout << arr3[1]->toString() << endl;
*/

	Container<int> **cont = new Container<int>*[2];

	cont[0] = new StaticDeque<int>();
	cont[1] = new Stack<int>();

	PushPopContainer<int> *ppc;
	Deque<int> *d;

	for (int i = 0; i < 2; i++) {
		if (ppc = dynamic_cast<PushPopContainer<int>*>(cont[i])) {
			for (int j = 1; j < 10; j++)
			ppc->push(j);
		} 
		if (d = dynamic_cast<Deque<int>*>(cont[i])) {
			for (int j = 1; j < 10; j++) {
				d->pushFront(j);
				d->pushBack(-(j));
			}
		}
		cout << cont[i]->toString() << endl;
	}

	cout << *cont[0] << endl;
	cout << *cont[1] << endl;

	StaticDeque<int> stack = StaticDeque<int>();
	for (int i = 0; i < 10; i++)
		stack.pushFront(i);
	cout << stack << endl;

	Container<int>::sort<StaticDeque<int>>(stack);

	cout << stack << endl;

	//for (int i = 0; i < 2; i++) {
	//	while (!cont[i]->isEmpty())
	//	{
	//		int value;
	//		if (ppc = dynamic_cast<PushPopContainer<int>*>(cont[i])) {
	//			value = ppc->pop();
	//		}
	//		if (d = dynamic_cast<Deque<int>*>(cont[i])) {
	//			value = d->popBack();
	//		}

	//		cout << "Popped element from " << i << " container = " << value << endl;
	//	}
	//}

	//Stack<string> *a = new Stack<string>();
	//a->push("string");

	//Stack<string> a1 = *a, a2(*a);

	//cout << endl << *a << endl << a1 << endl << a2 << endl;

	//a1.push("string1");
	//a2.push("string2");

	//cout << endl << *a << endl << a1 << endl << a2 << endl;

	//cout << "a1 == a " << (a1 == *a);

	//Stack<string> a, b;

	//a.push("string");
	//a.push("1");

	//b.push("string");
	//b.push("1");
	//b.push("1");

	//cout << endl << "a == b " << (a == b) << endl;

	_getch();

    return 0;
}
