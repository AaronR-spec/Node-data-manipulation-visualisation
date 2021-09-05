#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "Product.h"
#include <list>
#include <regex>
#include <time.h>
using namespace std;

const int SecondsPerMinute = 60;
const int SecondsPerHour = 3600;
const int SecondsPerDay = 86400;
const int DaysOfMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

//Code Adapted From: https://stackoverflow.com/questions/12353011/how-to-convert-a-utc-date-time-to-a-time-t-in-c
// Accessed: 13/01/2021
inline bool IsLeapYear(short year)
{
    if (year % 4 != 0) return false;
    if (year % 100 != 0) return true;
    return (year % 400) == 0;
}

inline time_t mkgmtime(short year, short month, short day, short hour, short minute, short second)
{
    time_t secs = 0;
    for (short y = 1970; y < year; ++y)
        secs += (IsLeapYear(y) ? 366 : 365) * SecondsPerDay;
    for (short m = 1; m < month; ++m) {
        secs += DaysOfMonth[m - 1] * SecondsPerDay;
        if (m == 2 && IsLeapYear(year)) secs += SecondsPerDay;
    }
    secs += (day - 1) * SecondsPerDay;
    secs += hour * SecondsPerHour;
    secs += minute * SecondsPerMinute;
    secs += second;
    return secs;
}
inline vector<string> splitString(string line, string r)
{
    regex reg{ r }; // split on space and comma
    sregex_token_iterator it{ line.begin(), line.end(), reg, -1 };
    vector<string> words{ it, {} };
    return words;
}
inline time_t processDateSplitString(string dateString)
{
    vector<string> dateSplit = splitString(dateString, "/");
    short year = (short)stoi(dateSplit.at(2));
    short month = (short)stoi(dateSplit.at(1));
    short day = (short)stoi(dateSplit.at(0));
    short hour = 0;
    short minute = 0;
    short second = 0;
    time_t orderDate = mkgmtime(year, month, day, hour, minute, second);
    return orderDate;
}
// Code adapted from: https://stackoverflow.com/questions/9435385/split-a-string-using-c11
// Accessed: 12/01/2021
inline Product createProduct(const string& line)
{
    Product p;

    // passing -1 as the submatch index parameter performs splitting
    vector<string> words = splitString(line, ",");

    p.setProductName(words.at(0));
    p.setUnitPrice(stoi(words.at(1)));
    p.setQuantity(stoi(words.at(2)));
    p.setCountry(words.at(3));
    p.setRegion(words.at(4));
    p.setCurrency(words.at(5));

    p.setOrderDate(processDateSplitString(words.at(6)));
    p.setDeliveryDate(processDateSplitString(words.at(7)));

    return p;
}

inline void readTextFile(string file, list<Product>& products)
{
    string line;
    ifstream myfile(file);

    if (myfile.is_open())
    {

        while (getline(myfile, line)) {
            products.push_back(createProduct(line));
        }
        myfile.close();
    }

    else cout << "Unable to open file";
}
