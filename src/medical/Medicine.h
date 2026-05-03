#pragma once
#include <string>
#include <iostream>
using namespace std;

struct Medicine
{

    string medicineName;
    string formula;
    double price;

public:
    // Constructor
    Medicine(string name = "", string form = "", double p = 0.0);

    // Getter
    string getMedicineName() const;

    // Output operator
    friend ostream& operator<<(ostream& os, const Medicine& med);
};
