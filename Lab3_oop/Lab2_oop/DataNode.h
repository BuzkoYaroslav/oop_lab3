#pragma once
template <class T>
class DataNode
{
public:
	T value;
	DataNode *prev;
	DataNode *next;

	DataNode(T);
	DataNode(DataNode<T> const&);
};

template <typename T> DataNode<T>::DataNode(T val)
{
	value = val;
	next = NULL;
	prev = NULL;
}

template <typename T>
DataNode<T>::DataNode(DataNode<T> const& copyFrom) {
	value = copyFrom.value;
}


