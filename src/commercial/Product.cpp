#include "Product.h"

// ---------------- Constructor ----------------
Product::Product() : productName(""), category("") {}

Product::Product(const string& name, const string& cat)
    : productName(name), category(cat)
{
}

// ---------------- Getters ----------------
const string& Product::getProductName() const
{
    return productName;
}

const string& Product::getCategory() const
{
    return category;
}

// ---------------- Setters ----------------
void Product::setProductName(const string& name)
{
    productName = name;
}

void Product::setCategory(const string& cat)
{
    category = cat;
}

// ---------------- Operator Overload ----------------
ostream& operator<<(ostream& os, const Product& p)
{
    os << "Product: " << p.productName
        << " | Category: " << p.category;
    return os;
}
