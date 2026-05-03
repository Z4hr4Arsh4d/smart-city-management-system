#pragma once
#include <string>
#include <iostream>
using namespace std;

class Product
{
private:
    string productName;
    string category;

public:
    Product();
    Product(const string& name, const string& cat);

    const string& getProductName() const;
    const string& getCategory() const;

    void setProductName(const string& name);
    void setCategory(const string& cat);

    friend ostream& operator<<(ostream& os, const Product& p);
};
