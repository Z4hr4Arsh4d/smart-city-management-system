#include "PharmacyModule.h"

// -------------------- Resize --------------------
void PharmacyModule::resizePharmacyList()
{
    int newCap = pharmacyCapacity * 2;
    Pharmacy** newList = new Pharmacy * [newCap];

    for (int i = 0; i < pharmacyCount; ++i)
        newList[i] = pharmacies[i];

    delete[] pharmacies;
    pharmacies = newList;
    pharmacyCapacity = newCap;
}

// -------------------- String to Int --------------------
int PharmacyModule::stringToInt(const string& str) const
{
    int result = 0;
    for (char c : str)
        if (isdigit(c))
            result = result * 10 + (c - '0');
    return result;
}

// -------------------- Constructor --------------------
PharmacyModule::PharmacyModule()
    : pharmacyCount(0), pharmacyCapacity(200)
{
    pharmacies = new Pharmacy * [pharmacyCapacity];
    pharmacyGraph = nullptr;
}

// -------------------- Destructor --------------------
PharmacyModule::~PharmacyModule()
{
    for (int i = 0; i < pharmacyCount; ++i)
        delete pharmacies[i];

    delete[] pharmacies;
    delete pharmacyGraph;
}

// -------------------- Getters --------------------
int PharmacyModule::getPharmacyCount() const { return pharmacyCount; }

Pharmacy* PharmacyModule::getPharmacyAt(int index) const
{
    if (index < 0 || index >= pharmacyCount) return nullptr;
    return pharmacies[index];
}

// -------------------- Load Pharmacies From CSV --------------------
void PharmacyModule::loadPharmaciesFromCSV(const string& filename, Sector::Graph& sectorGraph)
{
    int rows, cols;
    string** data = UTIL::CSVParser(filename, rows, cols);

    if (!data)
    {
        cout << "Failed to load pharmacies CSV: " << filename << "\n";
        return;
    }

    cout << "Loading pharmacies from CSV...\n";

    for (int i = 0; i < rows; ++i)
    {
        if (data[i][0].empty()) continue;

        string pharmacyID = data[i][0];
        string name = data[i][1];
        string sector = data[i][2];
        string medName = data[i][3];
        string formula = data[i][4];
        string priceStr = data[i][5];
        double price = 0.0;

        if(pharmacyID.empty() || name.empty() || sector.empty() || medName.empty() || formula.empty() || priceStr.empty())
        {
            continue;
        }

        if(UTIL::isNumeric(pharmacyID) || UTIL::isNumeric(name) || UTIL::isNumeric(sector) || UTIL::isNumeric(medName) || UTIL::isNumeric(formula) || !UTIL::isNumeric(priceStr))
        {
            continue;
        }
        if(!sectorGraph.searchSector(sector))
        {
            cout << "Warning: Sector '" << sector << "' not found for Pharmacy '" << name << "'. Skipping entry.\n";
            continue;
        }



        if (cols > 5 && !data[i][5].empty())
            price = stod(data[i][5]);

        int idx = -1;

        // Check existing pharmacy
        for (int k = 0; k < pharmacyCount; ++k)
        {
            if (pharmacies[k]->getPharmacyID() == pharmacyID)
            {
                idx = k;
                break;
            }
        }

        // Create new pharmacy if not found
        if (idx == -1)
        {
            if (pharmacyCount >= pharmacyCapacity)
                resizePharmacyList();

            pharmacies[pharmacyCount] = new Pharmacy(pharmacyID, name, sector, -1);
            idx = pharmacyCount;
            pharmacyCount++;
        }

        // Add medicine
        Medicine m(medName, formula, price);
        pharmacies[idx]->addMedicine(m);
    }

    UTIL::freeCSV(data, rows);
    cout << "Successfully loaded " << pharmacyCount << " pharmacies.\n";
}

// -------------------- Add Pharmacy --------------------
void PharmacyModule::addPharmacy(Pharmacy* p)
{
    if (pharmacyCount >= pharmacyCapacity)
        resizePharmacyList();

    pharmacies[pharmacyCount++] = p;
}

// -------------------- Attach to Sector Graph --------------------
void PharmacyModule::attachPharmaciesToSectors(Sector::Graph& graph)
{
    for (int i = 0; i < pharmacyCount; ++i)
    {
        Pharmacy* p = pharmacies[i];
        graph.addFacility(
            p->getSector(),
            p->getPharmacyID(),
            p->getName(),
            Facility::PHARMACY
        );
    }
}

// -------------------- Build Pharmacy SubGraph --------------------
void PharmacyModule::buildPharmacyGraph(Sector::Graph& graph)
{
    if (pharmacyGraph)
        delete pharmacyGraph;

    pharmacyGraph = graph.getSubgraph(Facility::PHARMACY);

    if (!pharmacyGraph)
        cout << "No pharmacies found in Sector Graph.\n";
    else
        cout << "Pharmacy SubGraph created successfully.\n";
}

// -------------------- Find Pharmacy by Name --------------------
Pharmacy* PharmacyModule::findPharmacyByName(const string& name)
{
    for (int i = 0; i < pharmacyCount; ++i)
        if (pharmacies[i]->getName() == name)
            return pharmacies[i];

    return nullptr;
}

Pharmacy* PharmacyModule::findPharmacyByName(const string& name) const
{
    for (int i = 0; i < pharmacyCount; ++i)
        if (pharmacies[i]->getName() == name)
            return pharmacies[i];

    return nullptr;
}

// -------------------- Find Pharmacy by ID --------------------
Pharmacy* PharmacyModule::findPharmacyByID(const string& id)
{
    for (int i = 0; i < pharmacyCount; ++i)
        if (pharmacies[i]->getPharmacyID() == id)
            return pharmacies[i];

    return nullptr;
}

Pharmacy* PharmacyModule::findPharmacyByID(const string& id) const
{
    for (int i = 0; i < pharmacyCount; ++i)
        if (pharmacies[i]->getPharmacyID() == id)
            return pharmacies[i];

    return nullptr;
}

// -------------------- Register Pharmacy --------------------
void PharmacyModule::registerPharmacy(const string& id,
    const string& name,
    const string& sector)
{
    if (pharmacyCount >= pharmacyCapacity)
    {
        cerr << "Cannot register pharmacy: capacity reached\n";
        return;
    }

    pharmacies[pharmacyCount] =
        new Pharmacy(id, name, sector, -1);

    pharmacyCount++;
    cout << "Pharmacy registered successfully\n";
}

// -------------------- Add Medicine to Pharmacy --------------------
void PharmacyModule::addMedicineToPharmacy(const string& pharmacyID,
    const string& medName,
    const string& formula,
    double price)
{
    for (int i = 0; i < pharmacyCount; ++i)
    {
        if (pharmacies[i]->getPharmacyID() == pharmacyID)
        {
            Medicine m(medName, formula, price);
            pharmacies[i]->addMedicine(m);
            cout << "Medicine added to pharmacy successfully\n";
            return;
        }
    }
    cerr << "Pharmacy not found\n";
}

// -------------------- Search Medicine by Name --------------------
bool PharmacyModule::searchMedicineByName(const string& medicineName,
    string& pharmacyName,
    Medicine& result)
{
    for (int i = 0; i < pharmacyCount; ++i)
    {
        if (pharmacies[i]->searchMedicineByName(medicineName, result))
        {
            pharmacyName = pharmacies[i]->getName();
            return true;
        }
    }
    return false;
}

// -------------------- Search Medicine by Formula --------------------
bool PharmacyModule::searchMedicineByFormula(const string& formula,
    string& pharmacyName,
    Medicine& result)
{
    for (int i = 0; i < pharmacyCount; ++i)
    {
        if (pharmacies[i]->searchMedicineByFormula(formula, result))
        {
            pharmacyName = pharmacies[i]->getName();
            return true;
        }
    }
    return false;
}

// -------------------- Display All Pharmacies --------------------
void PharmacyModule::displayAllPharmacies() const
{
    cout << "\n=== All Pharmacies ===\n";
    for (int i = 0; i < pharmacyCount; ++i)
    {
        cout << "ID: " << pharmacies[i]->getPharmacyID()
            << " | Name: " << pharmacies[i]->getName()
            << " | Sector: " << pharmacies[i]->getSector() << "\n";
    }
    cout << endl;
}

// -------------------- Display Pharmacy Details --------------------
void PharmacyModule::displayPharmacyDetails(const string& pharmacyName) const
{
    Pharmacy* p = findPharmacyByName(pharmacyName);

    if (!p)
    {
        cout << "Pharmacy not found.\n";
        return;
    }

    cout << "\n=== Pharmacy Details ===\n";
    cout << "ID: " << p->getPharmacyID() << "\n";
    cout << "Name: " << p->getName() << "\n";
    cout << "Sector: " << p->getSector() << "\n";
    p->displayMedicines();
}

// -------------------- Find Nearest Pharmacy --------------------
Pharmacy* PharmacyModule::findNearestPharmacy(const string& fromPharmacyName)
{
    if (!pharmacyGraph)
    {
        cout << "PharmacyGraph not built.\n";
        return nullptr;
    }

    Facility::Vertex* startV = pharmacyGraph->getVertex(fromPharmacyName);

    if (!startV)
    {
        cout << "Pharmacy not found in subgraph.\n";
        return nullptr;
    }

    string nearestName = "";
    int bestDist = INT_MAX;

    Facility::Vertex* v = pharmacyGraph->getHead();

    while (v)
    {
        if (v->name != fromPharmacyName)
        {
            string* path = nullptr;
            int pathLen = 0;
            int dist = -1;

            bool ok = pharmacyGraph->shortestPath(
                fromPharmacyName, v->name, path, pathLen, dist
            );

            if (ok && dist >= 0 && dist < bestDist)
            {
                bestDist = dist;
                nearestName = v->name;
            }

            delete[] path;
        }

        v = v->next;
    }

    if (nearestName == "")
        return nullptr;

    for (int i = 0; i < pharmacyCount; ++i)
        if (pharmacies[i]->getName() == nearestName)
            return pharmacies[i];

    return nullptr;
}
