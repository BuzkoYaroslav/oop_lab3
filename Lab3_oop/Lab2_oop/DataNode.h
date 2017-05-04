#pragma once
template <class T>
class DataNode
{
public:
	T value;
	DataNode *prev;
	DataNode *next;

	DataNode();
};

template <typename T> DataNode<T>::DataNode()
{
	value = T();
	next = NULL;
	prev = NULL;
}

