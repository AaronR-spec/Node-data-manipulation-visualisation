#pragma once
#include "Time.cpp"
using namespace std;

enum class NodeType {
	Input,
	Filter,
	Sort,
	Transform,
	Copy,
	Output
};
// acts as placeholder
class emptyClass
{

};

/// @brief Abstract parent class for a 1-to-1 Node object
/// @tparam T C++ or User-defined type (e.g. int, string, vector<float>, list<Student*>)
template <class T, class E = emptyClass>
class Node {
private:
	Node<T, E>* pNext = nullptr;
public:

	Node() {};
	~Node() {};

	Node<T, E>* setNext(Node<T, E>* pNext)
	{
		this->pNext = pNext;
		return this->pNext;
	}
	Node<T, E>* getNext() 
	{
		return this->pNext;
	}

	virtual void process(T& data) {};
	virtual void process(E& data) {};
};