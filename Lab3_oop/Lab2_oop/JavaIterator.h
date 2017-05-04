#pragma once
#include "stdafx.h"

template <class T>
class JavaIterator {
public:
	virtual T next() = 0;
	virtual bool hasNext() const = 0;
	virtual ~JavaIterator() {};
};