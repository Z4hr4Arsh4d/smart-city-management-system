#pragma once
#include <string>
#include <iostream>
#include <climits>
using namespace std;

#include "../../core/utility/utility.h"
#include "../../core/Sector.h"
#include "ShoppingMall.h"
#include "ProductHashTable.h"
#include "Product.h"

class CommercialModule
{
private:
    ShoppingMall** malls;
    int mallCount;
    int mallCapacity;

    Facility::SubGraph* mallGraph;

    void resizeMallList();

public:
    CommercialModule();
    ~CommercialModule();

    int getMallCount() const;
    ShoppingMall* getMallAt(int index) const;

    void addMall(ShoppingMall* m);
    void attachMallsToSectors(Sector::Graph& graph);
    void buildMallGraph(Sector::Graph& graph);

    ShoppingMall* findMallByName(const string& name);
    ShoppingMall* findMallByID(const string& id);

    void registerMall(const string& id, const string& name, const string& sector);
    void addProductToMall(const string& mallID, const string& productName, const string& category);

    void deleteMallByID(const string& id);

    bool searchProductByName(const string& productName, string& mallName, Product& result);
    bool searchProductByCategory(const string& category, string& mallName, Product& result);

    void displayAllMalls() const;
    void displayMallDetails(const string& mallName) const;

    ShoppingMall* findNearestMall(const string& fromMallName);
};
