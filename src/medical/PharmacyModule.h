#pragma once
#include <string>
#include <iostream>
using namespace std;

#include "../../core/utility/utility.h"
#include "../../core/Sector.h"
#include "Pharmacy.h"
#include "MedicineHashTable.h"

class PharmacyModule
{
private:
    Pharmacy** pharmacies;
    int pharmacyCount;
    int pharmacyCapacity;

    Facility::SubGraph* pharmacyGraph;

    void resizePharmacyList();
    int stringToInt(const string& str) const;

public:
    PharmacyModule();
    ~PharmacyModule();

    int getPharmacyCount() const;
    Pharmacy* getPharmacyAt(int index) const;

    void loadPharmaciesFromCSV(const string& filename, Sector::Graph& sectorGraph);
    void addPharmacy(Pharmacy* p);

    void attachPharmaciesToSectors(Sector::Graph& graph);
    void buildPharmacyGraph(Sector::Graph& graph);

    Pharmacy* findPharmacyByName(const string& name);
    Pharmacy* findPharmacyByName(const string& name) const;

    Pharmacy* findPharmacyByID(const string& id);
    Pharmacy* findPharmacyByID(const string& id) const;

    void registerPharmacy(const string& id, const string& name, const string& sector);

    void addMedicineToPharmacy(const string& pharmacyID,
        const string& medName,
        const string& formula,
        double price);

    bool searchMedicineByName(const string& medicineName,
        string& pharmacyName,
        Medicine& result);

    bool searchMedicineByFormula(const string& formula,
        string& pharmacyName,
        Medicine& result);

    void displayAllPharmacies() const;
    void displayPharmacyDetails(const string& pharmacyName) const;

    Pharmacy* findNearestPharmacy(const string& fromPharmacyName);
};
