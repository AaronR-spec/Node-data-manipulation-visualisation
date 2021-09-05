#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <list>
#include "Product.h"
#include "Calculations.cpp"
using namespace std;

inline void regionProductsCaluationList(list<list<int>>& contents, list<Product>& products)
{
    list<int> calulations;
    calulations.push_back(products.size());
    calulations.push_back(totalValueOfSales(products));
    calulations.push_back(totalQuantityOfSales(products));
    calulations.push_back(averageValueOfSales(products));
    contents.push_back(calulations);
}

inline void populateTable(string& table, string& title, list<int>& data)
{
    table += "\t\n<td>" + title + "</td>";
    for (auto x : data)
    {
        table += "\t\n<td>" + to_string(x);
        table += "</td>";
    }
}

inline void createHeading(string& table, list<string>& heading)
{
    for (auto s : heading)
    {
        table += "\t\n<th>" + s + "</th>";
    }
}

inline string createTable(list<string>& heading, vector<string>& titles, list<list<int>>& contents)
{
    string table = "\t\n<table style = 'width:100 % '>\n<tr>";
    // heading
    createHeading(table, heading);

    table += "\t\n</tr>";
    int titleIndex = 0;

    for (auto i : contents)
    {
        table += "\t\n<tr>";
        populateTable(table, titles.at(titleIndex), i);
        table += "\t\n</tr>\n";

        titleIndex++;

    }
    // contents
    table += " \n</table>\n";
    return table;
}

