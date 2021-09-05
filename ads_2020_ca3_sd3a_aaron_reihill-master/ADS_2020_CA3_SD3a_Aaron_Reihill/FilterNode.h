#pragma once

#include <list>
#include <functional>
#include "Node.h"
#include <string>

using namespace std;

template <class T, class E = emptyClass>
class FilterNode : public Node<list<T>, E> {
private:
	
	function<bool(T&)> filterData;

public:

	// constructor 
	FilterNode(function<bool(T&)> func)
	{
		this->filterData = func;
	}
	// function of the node like sort group etc
	void process(list<T>& products) override
	{
		cout << "\nFilterNode:";
		float sizeBytes = sizeof(function<bool(T&)>);
		cout << "\n\tSize" << " is " << sizeBytes << " bytes" << endl;
		chrono::time_point<chrono::high_resolution_clock> st = measureStartTime();
		products.erase(std::remove_if(products.begin(), products.end(), filterData), products.end());
		chrono::time_point<chrono::high_resolution_clock> end = measureEndTime();
		cout << "\tTime: " << measureCalculateTime(st, end) << endl;
		this->getNext()->process(products);
	}

};