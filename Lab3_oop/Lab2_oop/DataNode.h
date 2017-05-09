#pragma once
template <class T>
class DataNode
{
public:
	T value;
	DataNode *prev;
	DataNode *next;

	DataNode(T);
};

template <typename T> DataNode<T>::DataNode(T val)
{
	value = val;
	next = NULL;
	prev = NULL;
}


