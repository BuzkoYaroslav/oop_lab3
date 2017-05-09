#pragma once
#include "JavaIterator.h"
#include <sstream>
#include <string>
using namespace std;

template <class T>
class Container {
public:
	bool operator==(Container<T> const& cont) const {
		JavaIterator<T const&> *iter = createIterator();
		JavaIterator<T const&> *iterCont = cont.createIterator();
		T val1, val2;

		while ((val1 = iter->next()) != NULL &&
			   (val2 = iterCont->next()) != NULL) {
			if (val1 != val2)
				return false;

			val1 = NULL;
			val2 = NULL;
		}

		return val1 == val2;
	}
	bool operator!=(Container<T> const& cont) const {
		return !(this == cont);
	}

	virtual int size() const = 0;
	virtual bool isEmpty() const {
		return size() == 0;
	}
	virtual char* toString() const {
		JavaIterator<T const&> *iter = createIterator();

		char *res = new char[256]{ NULL };
		T val;

		stringstream stream;
		while ((val = iter->next()) != NULL) {
			char *line = new char[256]{ NULL };

			stream << val;
			stream >> line;

			strcat(res, line);

			delete line;
		}

		return res;
	}
	virtual ~Container() = 0 {};

	virtual JavaIterator<T&>* createIterator() = 0;
	virtual JavaIterator<T const&>* createIterator() const = 0;
};

template <typename T>
ostream& operator<<(ostream& os, Container<T> const& c) {
	os << c->toString();
	return os;
}