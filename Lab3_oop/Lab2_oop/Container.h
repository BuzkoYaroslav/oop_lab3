#pragma once
#include "JavaIterator.h"
#include <sstream>
#include <string>
#include <memory>
using namespace std;

template <class T>
class Container {
public:
	bool operator==(Container<T> const& cont) const {
		auto iter = unique_ptr<JavaIterator<T const&>>(createIterator());
		auto iterCont = unique_ptr<JavaIterator<T const&>>(cont.createIterator());

		while (iter->hasNext() &&
			   iterCont->hasNext()) {
			if (iter->next() != iterCont->next())
				return false;
		}

		return !iter->hasNext() && !iterCont->hasNext();
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

		strcat(res, "Container\n");
		strcat(res, "Head ->");

		stringstream stream;
		while (iter->hasNext()) {
			char *line = new char[256]{ NULL };
			
			val = iter->next();

			stream << val;
			stream >> line;

			strcat(res, line);
			
			if (iter->hasNext())
				strcat(res, ", ");

			stream.clear();

			delete line;
		}

		delete iter;

		strcat(res, "<- Tail\n");

		return res;
	}
	virtual ~Container() = 0 {};

	virtual JavaIterator<T&>* createIterator() = 0;
	virtual JavaIterator<T const&>* createIterator() const = 0;

	virtual void sort() {
		JavaIterator<T&> *mainIterator = createIterator();

		int count = 0;

		while (mainIterator->hasNext()) {
			JavaIterator<T&> *iter = createIterator();

			for (int i = 0; i < count; i++)
				iter->next();

			T& min = iter->next();

			while (iter->hasNext()) {
				T& temp = iter->next();
				
				if (temp < min) {
					T tmp = min;

					min = temp;
					temp = tmp;
				}
			}

			mainIterator->next();

			count++;

			delete iter;
		}

		delete mainIterator;
	}

	template <typename C>
	static void sort(C &c) {
		typename C::iterator mainIterator = typename C::iterator(c);

		int count = 0;

		while (mainIterator.hasNext()) {
			typename C::iterator iter = typename C::iterator(c);

			for (int i = 0; i < count; i++)
				iter.next();

			T& min = iter.next();

			while (iter.hasNext()) {
				T& temp = iter.next();

				if (temp < min) {
					T tmp = min;

					min = temp;
					temp = tmp;
				}
			}

			mainIterator.next();

			count++;
		}
	}
};

template <typename T>
ostream& operator<<(ostream& os, Container<T> const& c) {
	os << c.toString();
	return os;
}