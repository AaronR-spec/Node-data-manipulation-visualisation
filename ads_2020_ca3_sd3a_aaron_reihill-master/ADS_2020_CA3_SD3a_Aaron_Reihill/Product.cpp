#include "Product.h"


// Product Getters
string Product::getProductName() 
{
	return this->productName;
}
int Product::getUnitPrice() 
{
	return this->unitPrice;
}
int Product::getQuantity()
{
	return this->quantity;
}
string Product::getCountry() 
{
	return this->country;
}
string Product::getRegion() 
{
	return this->region;
}
string Product::getCurrency() 
{
	return this->currency;
}
time_t Product::getOrderDate()
{
	return this->orderDate;
}
time_t Product::getDeliveryDate() 
{
	return this->deliveryDate;
}

// Product Setters
void Product::setProductName(string name) 
{
	this->productName = name;
}
void Product::setUnitPrice(int price) 
{
	this->unitPrice = price;
}
void Product::setQuantity(int quantity) 
{
	this->quantity = quantity;
}
void Product::setCountry(string country) 
{
	this->country = country;
}
void Product::setRegion(string region) 
{
	this->region = region;
}
void Product::setCurrency(string currency) 
{
	this->currency = currency;
}
void Product::setOrderDate(time_t orderDate) 
{
	this->orderDate = orderDate;
}
void Product::setDeliveryDate(time_t deliveryDate) 
{
	this->deliveryDate = deliveryDate;
}

// Print products detatils
void Product::print() 
{
	cout << endl <<"Product: " << this->getProductName() << endl;
	cout << "Unit Price: " << this->getUnitPrice() << endl;
	cout << "Quantity: " << this->getQuantity() << endl;
	cout << "Country: " << this->getCountry() << endl;
	cout << "Region: " << this->getRegion() << endl;
	cout << "Currency: " << this->getCurrency() << endl;
	cout << "Order Date: " << this->convertTimeToString(this->getOrderDate()) << endl;
	cout << "Delivery Date: " << this->convertTimeToString(this->getDeliveryDate()) << endl;
}
// Code adapted from: https://www.tutorialspoint.com/cplusplus/cpp_date_time.htm
// Accessed: 13/01/2021
string Product::convertTimeToString(time_t date) 
{
	string dateString;
	tm ltm{};
	time_t now = date;
	// safe verison on localtime as windows flag error if you use localtime, so you need localtime_s
	localtime_s(&ltm, &now);
	// print various components of tm structure.
	dateString += to_string(ltm.tm_mday);
	dateString += "/" + to_string(1 + ltm.tm_mon);
	dateString += "/" + to_string(1900 + ltm.tm_year);
	return dateString;
}
