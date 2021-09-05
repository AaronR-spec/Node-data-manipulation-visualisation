#pragma once

#include <list>
#include <functional>
#include "Node.h"
#include <string>
#include <map>
#include <unordered_map> 

using namespace std;
// map<string, list<Product>> region = groupByCountry(products);
template <class T, class E = emptyClass>
class GroupByNode : public Node<T, E> {
private:
	function<E(T&)>  groupData;

public:

	// constructor   function<map<string, list<Product>>(list<Product>&)> func{ groupByRegion };
	GroupByNode(function<E(T&)>& func)
	{
		this->groupData = func;
	}
	// function of the node like sort group etc
	void process(T& products) override
	{
		cout << "\nGroupByNode: ";
		float sizeBytes = sizeof(function<E(T&)>);
		cout << "\n\tSize" << " is " << sizeBytes << " bytes";
		chrono::time_point<chrono::high_resolution_clock> st = measureStartTime();
		E mapData = groupData(products);
		chrono::time_point<chrono::high_resolution_clock> end = measureEndTime();
		cout << "\n\tTime: " << measureCalculateTime(st, end);
		this->getNext()->process(mapData);
	}

};