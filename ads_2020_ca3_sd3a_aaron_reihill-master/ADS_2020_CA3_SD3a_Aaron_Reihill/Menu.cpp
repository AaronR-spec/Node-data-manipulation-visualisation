#pragma once

#include "Reports.cpp"

// Add this to products object
// Code adapted from: https://www.tutorialspoint.com/cplusplus/cpp_date_time.htm
// Accessed: 13/01/2021
inline int getYear(time_t date)
{
    tm ltm{};
    time_t now = date;
    // safe verison on localtime as windows flag error if you use localtime, so you need localtime_s
    localtime_s(&ltm, &now);
    // print various components of tm structure.
    return (1900 + ltm.tm_year);

}
// processing
inline void filterByYear(int year, list<Product>& products)
{
    list<Product> productsInYear;
    for (auto p : products)
    {
        if (getYear(p.getOrderDate()) == year)
        {
            productsInYear.push_back(p);
        }
    }
    products = productsInYear;
}

inline void writeToCsvFile(string& file, string& table)
{
    ofstream myfile;
    myfile.open(file);
    myfile << table;
    myfile.close();
}
inline void writeToHtmlFile(string& file, string& table)
{
    string html = "<!DOCTYPE html>\n<html>\n\t<head><meta http-equiv='Content-Type' content='text/html; charset=utf-8'/>\n\t<head>\n\t<body>";
    html += table;
    html += "\n\t</body>\n</html>";
    // Create and open a text file
    ofstream MyFile(file);

    // Write to the file
    MyFile << html;

    // Close the file
    MyFile.close();
}
inline Product mostPopularItem(list<Product>& products)
{
    Product popular;
    unordered_map<string, int> items;
    int maxQuantity = 0;
    for (auto p : products)
    {
        unordered_map<string, int>::iterator it = items.find(p.getProductName());
        // if value is currently in map we add quantity on it
        if (it != items.end())
        {
            //element found;
            it->second += p.getQuantity();
        }
        else
        {
            // adds it to map if not currently in the map 
            items.insert({ p.getProductName(), p.getQuantity() });
        }
        // checks if its in the map and if it is quantity is bigger then the current biggest quantity it replaces it.
        if (it != items.end() && it->second > maxQuantity)
        {
            maxQuantity = it->second;
            popular = p;
        }
    }

    return popular;
}

inline void processByRegion(unordered_map<string, list<Product>>& products)
{
    list<Product> listProducts;

    list<string> heading = { "Region", "TotalVolumeOfSales" , "TotalValueOfSales","TotalQuantityOfSales", "TotalVolumeOfSales" };
    vector<string> titles;
    list<list<int>> contents;

    for (auto const& x : products)
    {
        listProducts = x.second;

        titles.push_back(x.first);

        regionProductsCaluationList(contents, listProducts);
    }

    string file = "ByRegion.html";
    string table = createTable(heading, titles, contents);

    writeToHtmlFile(file, table);
}
inline void processByPopularity(unordered_map<string, list<Product>>& products)
{

    list<Product> listProducts;
    Product popular;

    string table;
    table += "\t\n<table style = 'width:100 % '>\n<tr>";
    list<string> heading = { "Country", "Popular Product Name" };
    createHeading(table, heading);
    table += "\t\n</tr>";
    for (auto const& x : products)
    {
        listProducts = x.second;

        popular = mostPopularItem(listProducts);
        table += "\t\n</tr>\t\n<td>" + x.first;
        table += "</td>";
        table += "\t\n<td>" + popular.getProductName();
        table += "</td>\n</tr>";
    }

    table += " \n</table>\n";
    string file = "ByPopularity.html";

    writeToHtmlFile(file, table);


}
inline void processByPopularityPrice(list<Product>& products)
{
    string table;
    createCsvFormat(table, products);
    string file = "ByPrice.csv";
    writeToCsvFile(file, table);

}

// Grouping functions
inline unordered_map<string, list<Product>> groupByRegion(list<Product>& products)
{
    unordered_map<string, list<Product>> regionItems;
    list<Product> regionList;
    for (auto p : products)
    {
        unordered_map<string, list<Product>>::iterator it = regionItems.find(p.getRegion());
        // if value is currently in map we add it to the regions list
        if (it != regionItems.end())
        {
            //element found;

            it->second.push_back(p);
        }
        else
        {
            // adds it to map if not currently in the map 
            regionList.push_back(p);
            regionItems.insert({ p.getRegion(), regionList });
            regionList.empty();
        }
        // checks if its in the map and if it is quantity is bigger then the current biggest quantity it replaces it.
    }

    return regionItems;

}
inline unordered_map<string, list<Product>> groupByCountry(list<Product>& products)
{
    Product popular;
    unordered_map<string, list<Product>> countryItems;
    list<Product> countryList;
    for (auto p : products)
    {
        unordered_map<string, list<Product>>::iterator it = countryItems.find(p.getCountry());
        // if value is currently in map we add it to the regions list
        if (it != countryItems.end())
        {
            //element found;
            it->second.push_back(p);
        }
        else
        {
            // adds it to map if not currently in the map 

            countryList.push_back(p);
            countryItems.insert({ p.getCountry(), countryList });
            countryList.empty();
        }
        // checks if its in the map and if it is quantity is bigger then the current biggest quantity it replaces it.
    }
    return countryItems;

}

inline void byRegion(string file)
{
    list<Product> products;
    // input node
    function<void(string, list<Product>&)> func{ readTextFile };
    //string &file, function<void(string, list<T>&)> &func)
    unique_ptr<InputFromFileNode<list<Product>, unordered_map<string, list<Product>>>> ptrInputFileNode(new InputFromFileNode<list<Product>, unordered_map<string, list<Product>>>(file, func));

    // filter node              // input            parama            
    int target = 2020;
    int target2 = 2021;
    auto funcFilter = [target, target2](Product product) {return getYear(product.getDeliveryDate()) > target && getYear(product.getDeliveryDate()) < target2; };
    //FilterNode(function<bool(T)> & func)
    unique_ptr<FilterNode<Product, unordered_map<string, list<Product>>>> ptrFilterNode(new FilterNode<Product, unordered_map<string, list<Product>>>(funcFilter));
    // SortByNode
    function<bool(Product& p1, Product& p2)> funcSort{ sortDescRegion };
    unique_ptr<SortByNode<Product, unordered_map<string, list<Product>>>> ptrSortNode(new SortByNode<Product, unordered_map<string, list<Product>>>(funcSort));

    // Group by node
    function<unordered_map<string, list<Product>>(list<Product>&)> funcRegion{ groupByRegion };
    unique_ptr<GroupByNode<list<Product>, unordered_map<string, list<Product>>>> ptrGroupNode(new GroupByNode<list<Product>, unordered_map<string, list<Product>>>(funcRegion));

    function<void(unordered_map<string, list<Product>>&)> funcOutput{ processByRegion };
    // OutputNode problem with group being map and having to pass that to output process so i need to add template for map so im able to pass this through to output
    // this is not a good option but i tried everything and it works
    unique_ptr<OutputToFileNode<list<Product>, unordered_map<string, list<Product>>>> ptrOutNode(new OutputToFileNode<list<Product>, unordered_map<string, list<Product>>>(funcOutput));

    // connects graph 
    ptrInputFileNode->setNext(ptrFilterNode.get())->setNext(ptrSortNode.get())->setNext(ptrGroupNode.get())->setNext(ptrOutNode.get());

    // initates the process 
    ptrInputFileNode->process(products);
}
inline void byPopularity(string file)
{
    list<Product> products;
    // input node
    function<void(string, list<Product>&)> func{ readTextFile };
    //string &file, function<void(string, list<T>&)> &func)
    unique_ptr < InputFromFileNode<list<Product>, unordered_map<string, list<Product>>>> ptrInputFileNode(new InputFromFileNode<list<Product>, unordered_map<string, list<Product>>>(file, func));

    // filter node              // input            parama            
    int target = 2020;
    auto funcFilter = [target](Product product) {return getYear(product.getDeliveryDate()) != target; };
    //FilterNode(function<bool(T)> & func)
    unique_ptr < FilterNode<Product, unordered_map<string, list<Product>>>> ptrFilterNode(new FilterNode<Product, unordered_map<string, list<Product>>>(funcFilter));

    // SortByNode
    function<bool(Product& p1, Product& p2)> funcSort{ sortAscRegion };
    unique_ptr < SortByNode<Product, unordered_map<string, list<Product>>>> ptrSortNode(new SortByNode<Product, unordered_map<string, list<Product>>>(funcSort));

    // SortByNode
    function<bool(Product& p1, Product& p2)> funcSortCountry{ sortAscCountry };
    unique_ptr < SortByNode<Product, unordered_map<string, list<Product>>>> ptrSortCountryNode(new SortByNode<Product, unordered_map<string, list<Product>>>(funcSortCountry));


    // Group by node
    function<unordered_map<string, list<Product>>(list<Product>&)> funcRegion{ groupByCountry };
    unique_ptr<GroupByNode<list<Product>, unordered_map<string, list<Product>>>> ptrGroupNode(new GroupByNode<list<Product>, unordered_map<string, list<Product>>>(funcRegion));

    function<void(unordered_map<string, list<Product>>&)> funcOutput{ processByPopularity };
    // OutputNode problem with group being map and having to pass that to output process so i need to add template for map so im able to pass this through to output
    // this is not a good option but i tried everything and it works
    unique_ptr <OutputToFileNode<list<Product>, unordered_map<string, list<Product>>>> ptrOutNode(new OutputToFileNode<list<Product>, unordered_map<string, list<Product>>>(funcOutput));

    // connects graph 
    ptrInputFileNode->setNext(ptrFilterNode.get())->setNext(ptrSortNode.get())->setNext(ptrSortCountryNode.get())->setNext(ptrGroupNode.get())->setNext(ptrOutNode.get());

    // initates the process 
    ptrInputFileNode->process(products);
}
inline void byPrice(string file)
{
    list<Product> products;
    // input node
    function<void(string, list<Product>&)> func{ readTextFile };
    //string &file, function<void(string, list<T>&)> &func)
    unique_ptr<InputFromFileNode<list<Product>, unordered_map<string, list<Product>>>> ptrInputFileNode(new InputFromFileNode<list<Product>, unordered_map<string, list<Product>>>(file, func));


    // SortByNode
    function<bool(Product&, Product&)> funcSort{ sortAescPrice };
    unique_ptr < SortByNode<Product, unordered_map<string, list<Product>>>> ptrSortNode(new SortByNode<Product, unordered_map<string, list<Product>>>(funcSort));


    function<void(list<Product>&)> funcOutput{ processByPopularityPrice };
    // OutputNode problem with group being map and having to pass that to output process so i need to add template for map so im able to pass this through to output
    // this is not a good option but i tried everything and it works
    unique_ptr < OutputToFileNode<list<Product>, unordered_map<string, list<Product>>>> ptrOutNode(new OutputToFileNode<list<Product>, unordered_map<string, list<Product>>>(funcOutput));

    // connects graph 
    ptrInputFileNode->setNext(ptrSortNode.get())->setNext(ptrOutNode.get());

    // initates the process 
    ptrInputFileNode->process(products);

}


inline int printMenu()
{
    cout << "\n1. byRegion\n2. byPopularity\n3. byPrice\n4. Change File\n5. Exit\nOption: ";
    int userInput;
    cin >> userInput;
    return userInput;
}
inline void startMenu()
{
    string file;
    int userInput;
    function<void(string)> funcRegion{ byRegion };
    function<void(string)> funcPop{ byPopularity };
    function<void(string)> funcPrice{ byPrice };

    cout << "\nName of chosen file: ";
    cin >> file;

    while (true)
    {
        cout << endl;
        userInput = printMenu();
        switch (userInput)
        {
        case 1:
            cout << "Total Time: " << measureTime(funcRegion, file) << endl;
            cout << "Process Finished...";
            break;
        case 2:
            cout << "Total Time: " << measureTime(funcPop, file) << endl;
            cout << "Process Finished...";
            break;
        case 3:
            cout << "Total Time: " << measureTime(funcPrice, file) << endl;
            cout << "Process Finished...";
            break;
        case 4:
            cout << "\nName of chosen file: ";
            cin >> file;
            break;
        case 5:
            cout << endl << "GoodBye..." << endl;
            return;
            break;
        default:
            cout << endl << "Invalid Input (1-4)" << endl;
        }
    }
}
