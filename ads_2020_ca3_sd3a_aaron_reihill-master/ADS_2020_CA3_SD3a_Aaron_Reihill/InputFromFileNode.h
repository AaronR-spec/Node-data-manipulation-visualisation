#pragma once

#include <list>
#include <functional>
#include "Node.h"
#include <string>

using namespace std;

template <class T, class E = emptyClass>
class InputFromFileNode : public Node<T, E> {
private:
	string file;
	function<void(string, T&)> readData;

public:

	// constructor 
	InputFromFileNode(string &file, function<void(string, T&)> &func)
	{
		this->readData = func;
		this->file = file;
	}
	// function of the node like sort group etc
	void process(T& products) override
	{
		cout << "\nInputFromFileNode: " << endl;
		float sizeBytes = sizeof(string) + sizeof(function<void(string, T&)>);
		cout << "\tSize" << " is " << sizeBytes << " bytes" << endl;
		chrono::time_point<chrono::high_resolution_clock> st = measureStartTime();
		readData(this->file, products);
		chrono::time_point<chrono::high_resolution_clock> end = measureEndTime();
		cout <<"\tTime: " << measureCalculateTime(st, end) << endl;
		this->getNext()->process(products);
	}

};