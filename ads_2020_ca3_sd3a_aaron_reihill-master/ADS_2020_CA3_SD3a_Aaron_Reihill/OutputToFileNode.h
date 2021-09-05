#pragma once

#include <list>
#include <functional>
#include "Node.h"
#include <string>
#include <map>

using namespace std;

template <class T, class E = emptyClass>
class OutputToFileNode : public Node<T, E> {
private:
	function<void(E&)>  outputData;
	function<void(T&)>  outputListData;
public:

	OutputToFileNode(function<void(E&)> func)
	{
		this->outputData = func;
	}
	OutputToFileNode(function<void(T&)> func)
	{
		this->outputListData = func;
	}
	void process(T& products) override
	{
		cout << endl << "OutputToFileNode: \n";
		float sizeBytes = sizeof(function<void(T&)>);
		cout << "\nSize" << " is " << sizeBytes << " bytes" << endl;
		cout << measureTime(outputListData, products) << endl;
	}
	void process(E& products) 
	{
		cout << endl << "\nOutputToFileNode:";
		float sizeBytes = sizeof(function<void(E&)>);
		cout << "\n\tSize" << " is " << sizeBytes << " bytes" << endl;
		cout << "\tTime : "<<measureTime(outputData, products) << endl << endl;
	}
};