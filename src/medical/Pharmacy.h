#pragma once
#include <string>
#include <iostream>
using namespace std;

#include "Medicine.h"
#include "MedicineHashTable.h"   // Your HashTable class

class Pharmacy
{
private:
    string pharmacyID;
    string name;
    string sector;
    int graphNodeIndex;

    HashTable medicineByName;

public:
    Pharmacy(string id = "", string n = "", string sec = "", int nodeIdx = -1);

    // Getters
    string getPharmacyID() const;
    string getName() const;
    string getSector() const;
    int getGraphNodeIndex() const;

    // Medicine operations
    void addMedicine(const Medicine& med);
    bool searchMedicineByName(const string& name, Medicine& value);
    bool hasMedicine(const string& medicineName) const;
    void displayMedicines() const;

    bool searchMedicineByFormula(const string& formula, Medicine& value) const;
};
