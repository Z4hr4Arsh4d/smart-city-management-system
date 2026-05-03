#pragma once
#include <string>
#include <iostream>
using namespace std;

#include "ProductHashTable.h"

class ShoppingMall
{
private:
    string mallID;
    string name;
    string sector;
    int nodeIndex;

    ProductHashTable products;

public:
    ShoppingMall();
    ShoppingMall(const string& id, const string& n, const string& s, int nodeIdx = -1);

    const string& getMallID() const;
    const string& getName() const;
    const string& getSector() const;
    int getNodeIndex() const;
    void setNodeIndex(int idx);

    void addProduct(const Product& p);
    bool searchProductByName(const string& productName, Product& result);
    bool searchProductByCategory(const string& category, Product& result);

    void displayProducts() const;
};
