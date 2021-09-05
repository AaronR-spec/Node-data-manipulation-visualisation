#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <list>
#include "Product.h"
using namespace std;

inline void createCsvFormat(string& table, list<Product>& products)
{
    // heading columns
    table += "Product name ,Unit Price, Region, Order Date ";
    for (auto p : products)
    {
        table += "\n" + p.getProductName() + ",";
        table += to_string(p.getUnitPrice()) + ",";
        table += p.getRegion() + ",";
        table += p.convertTimeToString(p.getOrderDate()) + ",";
    }
}