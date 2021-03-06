#pragma once
#include "Container.h"

template <class T>
class IndexedContainer : public virtual Container<T> {
public:
	T& operator[](int index) {
		return get(index);
	}

	virtual T get(int index) const = 0;
	virtual T& get(int index) = 0;

	virtual void set(int index, T const& value) = 0;

	virtual ~IndexedContainer() = 0 {};
};