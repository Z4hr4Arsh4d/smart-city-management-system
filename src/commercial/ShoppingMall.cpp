#include "ShoppingMall.h"

// ----------------------- Constructors -----------------------
ShoppingMall::ShoppingMall()
    : mallID(""), name(""), sector(""), nodeIndex(-1), products(20)
{
}

ShoppingMall::ShoppingMall(const string& id, const string& n, const string& s, int nodeIdx)
    : mallID(id), name(n), sector(s), nodeIndex(nodeIdx), products(20)
{
}

// ----------------------- Getters -----------------------
const string& ShoppingMall::getMallID() const { return mallID; }
const string& ShoppingMall::getName() const { return name; }
const string& ShoppingMall::getSector() const { return sector; }
int ShoppingMall::getNodeIndex() const { return nodeIndex; }

// ----------------------- Setter -----------------------
void ShoppingMall::setNodeIndex(int idx)
{
    nodeIndex = idx;
}

// ----------------------- Product Operations -----------------------
void ShoppingMall::addProduct(const Product& p)
{
    products.insert(p.getProductName(), p);
}

bool ShoppingMall::searchProductByName(const string& productName, Product& result)
{
    return products.search(productName, result);
}

bool ShoppingMall::searchProductByCategory(const string& category, Product& result)
{
    return products.searchByCategory(category, result);
}

void ShoppingMall::displayProducts() const
{
    products.display();
}
