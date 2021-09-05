#pragma once

#include <list>
#include <functional>
#include "Node.h"
#include <string>

using namespace std;

template <class T, class E = emptyClass>
class SortByNode : public Node<list<T>, E> {
private:

	function<bool(T&, T&)> sortData;

public:

	// constructor  bool sortAscRegion( Product& p1,  Product& p2)
	SortByNode(function<bool( T&, T&)>& func)
	{
		this->sortData = func;
	}


	// function of the node like sort group etc
	void process(list<T>& products) override
	{
		
		cout << "\nSortByNode:";
		float sizeBytes = sizeof(function<bool(T&, T&)>);
		cout << "\n\tSize" << " is " << sizeBytes << " bytes" << endl;
		chrono::time_point<chrono::high_resolution_clock> st = measureStartTime();
		products.sort(this->sortData);
		chrono::time_point<chrono::high_resolution_clock> end = measureEndTime();
		cout << "\tTime: " << measureCalculateTime(st, end) << endl;
		this->getNext()->process(products);
	}

};