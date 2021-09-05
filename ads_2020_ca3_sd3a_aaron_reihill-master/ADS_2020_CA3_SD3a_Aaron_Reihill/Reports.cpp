#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <regex>
#include <time.h>
#include "InputFromFileNode.h"
#include "ReadFile.cpp"
#include "FilterNode.h"
#include "SortByNode.h"
#include "GroupByNode.h"
#include "OutputToFileNode.h"
#include "Comparitor.cpp"
#include "Calculations.cpp"
#include "HtmlGenerate.cpp"
#include "GenerateCSV.cpp"
#include "Node.h"
#include <ctime>
#include <map>
#include <unordered_map> 
#include <chrono>
#include <memory> 

/*
	moved functions with reports out into the file they were getting called from and they work.
	must be somthing with having the pointer and the call in a sepertate file.
*/