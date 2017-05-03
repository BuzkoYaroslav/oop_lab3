#pragma once

class Container {
public:
	virtual int size() const = 0;
	virtual bool isEmpty() const = 0;
	virtual char* toString() const = 0;
	virtual ~Container() = 0 {};
};