#pragma once
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

class Product
{
public:
	// copy constructor
	string getProductName();
	int getUnitPrice();
	int getQuantity();
	string getCountry();
	string getRegion();
	string getCurrency();
	time_t getOrderDate();
	time_t getDeliveryDate();

	void setProductName(string name);
	void setUnitPrice(int price);
	void setQuantity(int quantity);
	void setCountry(string country);
	void setRegion(string region);
	void setCurrency(string currency);
	void setOrderDate(time_t orderDate);
	void setDeliveryDate(time_t deliveryDate);

	void print();
	string convertTimeToString(time_t date);


private:
	string productName;
	int unitPrice;
	int quantity;
	string country;
	string region;
	string currency;
	time_t orderDate;
	time_t deliveryDate;


};

