#include "Pharmacy.h"

// ---------------- Constructor ----------------
Pharmacy::Pharmacy(string id, string n, string sec, int nodeIdx)
    : pharmacyID(id), name(n), sector(sec), graphNodeIndex(nodeIdx)
{
}

// ---------------- Getters ----------------
string Pharmacy::getPharmacyID() const { return pharmacyID; }
string Pharmacy::getName() const { return name; }
string Pharmacy::getSector() const { return sector; }
int Pharmacy::getGraphNodeIndex() const { return graphNodeIndex; }

// ---------------- Add Medicine ----------------
void Pharmacy::addMedicine(const Medicine& med)
{
    medicineByName.insert(med.getMedicineName(), med);
}

// ---------------- Search by Name ----------------
bool Pharmacy::searchMedicineByName(const string& medName, Medicine& value)
{
    return medicineByName.searchByName(medName, value);
}

// ---------------- Contains ----------------
bool Pharmacy::hasMedicine(const string& medicineName) const
{
    Medicine dummy;
    return const_cast<HashTable&>(medicineByName).searchByName(medicineName, dummy);
}

// ---------------- Display Medicines ----------------
void Pharmacy::displayMedicines() const
{
    cout << "\n=== Pharmacy: " << name << " (" << sector << ") ===\n";
    cout << "Medicines:\n";
    medicineByName.display();
}

// ---------------- Search by Formula ----------------
bool Pharmacy::searchMedicineByFormula(const string& formula, Medicine& value) const
{
    for (int i = 0; i < 100; ++i)
    {
        HashNode* chain = medicineByName.getChain(i);
        HashNode* current = chain;

        while (current != nullptr)
        {
            if (current->med.formula == formula)
            {
                value = current->med;
                return true;
            }
            current = current->next;
        }
    }
    return false;
}
