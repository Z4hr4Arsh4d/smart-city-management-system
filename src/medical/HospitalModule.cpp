#include "HospitalModule.h"

// -------------------- Helper: Resize list --------------------
void HospitalModule::resizeHospitalList()
{
    int newCap = hospitalCapacity * 2;
    Hospital** newList = new Hospital * [newCap];

    for (int i = 0; i < hospitalCount; i++)
        newList[i] = hospitals[i];

    delete[] hospitals;
    hospitals = newList;
    hospitalCapacity = newCap;
}

// -------------------- Helper: String to int --------------------
int HospitalModule::stringToInt(const string& str) const
{
    int result = 0;
    for (char c : str)
    {
        if (isdigit(c))
            result = result * 10 + (c - '0');
    }
    return result;
}

// -------------------- Helper: Clean CSV specialization --------------------
string HospitalModule::cleanSpecializations(const string& specs) const
{
    string cleaned = "";
    bool inQuotes = false;

    for (char c : specs)
    {
        if (c == '"')
            inQuotes = !inQuotes;
        else if (c == '\r')
            continue;
        else
            cleaned += c;
    }
    return cleaned;
}

// -------------------- Constructor --------------------
HospitalModule::HospitalModule()
    : hospitalCount(0), hospitalCapacity(200), bedHeap(100)
{
    hospitals = new Hospital * [hospitalCapacity];
    hospitalGraph = nullptr;
}

// -------------------- Destructor --------------------
HospitalModule::~HospitalModule()
{
    for (int i = 0; i < hospitalCount; i++)
        delete hospitals[i];
    delete[] hospitals;
    delete hospitalGraph;
}

// -------------------- Getters --------------------
int HospitalModule::getHospitalCount() const { return hospitalCount; }

Hospital* HospitalModule::getHospitalAt(int index) const
{
    if (index < 0 || index >= hospitalCount) return nullptr;
    return hospitals[index];
}

// -------------------- Load Hospitals from CSV --------------------
void HospitalModule::loadHospitalsFromCSV(const string& filename, Sector::Graph& sectorGraph)
{
    int rows, cols;
    string** data = UTIL::CSVParser(filename, rows, cols);

    if (!data)
    {
        cout << "Failed to load hospital CSV: " << filename << "\n";
        return;
    }

    cout << "Loading hospitals from CSV...\n";

    for (int i = 0; i < rows; i++)
    {
        if (data[i][0].empty()) continue;

        string hospitalID = data[i][0];
        string name = data[i][1];
        string sector = data[i][2];
        string bedStr = data[i][3];
        string specializations = cleanSpecializations(data[i][4]);

        if(hospitalID.empty() || name.empty() || sector.empty() || bedStr.empty() || specializations.empty())
        {
            cout << "Skipping invalid hospital entry at row " << (i + 1) << ".\n";
            continue;
        }

        if(UTIL::isNumeric(hospitalID) || UTIL::isNumeric(name) || UTIL::isNumeric(sector) || UTIL::isNumeric(specializations) || !UTIL::isNumeric(bedStr))
        {
            continue;
        }

        if(sectorGraph.getVertex(sector) == nullptr)
        {
            cout << "Sector '" << sector << "' for hospital '" << name << "' does not exist. Skipping.\n";
            continue;
        }



        int beds = stringToInt(bedStr);
        Hospital* h = new Hospital(hospitalID, name, sector, beds, specializations);
        addHospital(h);

        bedHeap.insert(stringToInt(hospitalID), name, beds);
    }

    UTIL::freeCSV(data, rows);
    cout << "Successfully loaded " << hospitalCount << " hospitals.\n";
}

// -------------------- Add Hospital --------------------
void HospitalModule::addHospital(Hospital* h)
{
    if (hospitalCount >= hospitalCapacity)
        resizeHospitalList();
    hospitals[hospitalCount++] = h;
}

// -------------------- Attach Hospitals to Sector Graph --------------------
void HospitalModule::attachHospitalsToSectors(Sector::Graph& graph)
{
    for (int i = 0; i < hospitalCount; i++)
    {
        Hospital* h = hospitals[i];
        graph.addFacility(
            h->getSector(),
            h->getHospitalID(),
            h->getName(),
            Facility::MEDICAL
        );
    }
}

// -------------------- Find Hospital by Name --------------------
Hospital* HospitalModule::findHospitalByName(const string& name)
{
    for (int i = 0; i < hospitalCount; i++)
        if (hospitals[i]->getName() == name)
            return hospitals[i];
    return nullptr;
}

Hospital* HospitalModule::findHospitalByName(const string& name) const
{
    for (int i = 0; i < hospitalCount; i++)
        if (hospitals[i]->getName() == name)
            return hospitals[i];
    return nullptr;
}

// -------------------- Find Hospital by ID --------------------
Hospital* HospitalModule::findHospitalByID(const string& id)
{
    for (int i = 0; i < hospitalCount; i++)
        if (hospitals[i]->getHospitalID() == id)
            return hospitals[i];
    return nullptr;
}

// -------------------- Register Doctor --------------------
void HospitalModule::registerDoctorToHospital(const string& hospitalName,
    const string& doctorID,
    const string& doctorName,
    const string& specialization)
{
    Hospital* h = findHospitalByName(hospitalName);
    if (!h)
    {
        cout << "Hospital not found.\n";
        return;
    }

    Doctor doc(doctorID, doctorName, specialization);
    h->addDoctor(doc);
    cout << "Doctor registered successfully.\n";
}

// -------------------- Add Patient --------------------
void HospitalModule::addPatientToHospital(const string& hospitalName, const Patient& patient)
{
    Hospital* h = findHospitalByName(hospitalName);
    if (!h)
    {
        cout << "Hospital not found.\n";
        return;
    }

    h->addPatient(patient);
    cout << "Patient added to hospital queue.\n";
}

// -------------------- Update Bed Count --------------------
void HospitalModule::updateHospitalBeds(const string& hospitalName, int newBedCount)
{
    Hospital* h = findHospitalByName(hospitalName);
    if (!h)
    {
        cout << "Hospital not found.\n";
        return;
    }

    h->setEmergencyBeds(newBedCount);
    bedHeap.updateBeds(stringToInt(h->getHospitalID()), newBedCount);
    cout << "Hospital bed availability updated.\n";
}

// -------------------- Bed Statistics --------------------
BedHeapElement HospitalModule::getHospitalWithMostBeds() const
{
    return bedHeap.getMax();
}

Hospital* HospitalModule::getHospitalWithLeastBeds() const
{
    int minBeds = INT_MAX;
    Hospital* result = nullptr;

    for (int i = 0; i < hospitalCount; i++)
    {
        if (hospitals[i]->getEmergencyBeds() < minBeds)
        {
            minBeds = hospitals[i]->getEmergencyBeds();
            result = hospitals[i];
        }
    }

    return result;
}

// -------------------- Search by Specialization --------------------
void HospitalModule::searchBySpecialization(const string& specialization)
{
    cout << "\nHospitals with '" << specialization << "' specialization:\n";

    for (int i = 0; i < hospitalCount; i++)
    {
        string specs = hospitals[i]->getSpecializations();
        if (specs.find(specialization) != string::npos)
            cout << "  - " << hospitals[i]->getName()
            << " (" << hospitals[i]->getSector() << ")\n";
    }
    cout << endl;
}

// -------------------- Build Hospital SubGraph --------------------
void HospitalModule::buildHospitalGraph(Sector::Graph& graph)
{
    if (hospitalGraph)
        delete hospitalGraph;

    hospitalGraph = graph.getSubgraph(Facility::MEDICAL);

    if (!hospitalGraph)
        cout << "No hospitals found in Sector Graph.\n";
    else
        cout << "Hospital SubGraph created successfully.\n";
}

// -------------------- Find Nearest Hospital --------------------
Hospital* HospitalModule::findNearestHospital(const string& fromHospitalName)
{
    if (!hospitalGraph)
    {
        cout << "HospitalGraph not built.\n";
        return nullptr;
    }

    Facility::Vertex* startV = hospitalGraph->getVertex(fromHospitalName);
    if (!startV)
    {
        cout << "Hospital not found in subgraph.\n";
        return nullptr;
    }

    string nearestName = "";
    int bestDist = INT_MAX;

    Facility::Vertex* v = hospitalGraph->getHead();
    while (v)
    {
        if (v->name != fromHospitalName)
        {
            string* path = nullptr;
            int pathLen = 0;
            int dist = -1;

            bool ok = hospitalGraph->shortestPath(fromHospitalName, v->name, path, pathLen, dist);

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

    for (int i = 0; i < hospitalCount; i++)
        if (hospitals[i]->getName() == nearestName)
            return hospitals[i];

    return nullptr;
}

// -------------------- Display All Hospitals --------------------
void HospitalModule::displayAllHospitals() const
{
    cout << "\n=== All Hospitals ===\n";
    for (int i = 0; i < hospitalCount; i++)
    {
        cout << "ID: " << hospitals[i]->getHospitalID()
            << " | Name: " << hospitals[i]->getName()
            << " | Sector: " << hospitals[i]->getSector()
            << " | Beds: " << hospitals[i]->getEmergencyBeds()
            << " | Specializations: " << hospitals[i]->getSpecializations() << "\n";
    }
    cout << endl;
}

// -------------------- Display Hospital Details --------------------
void HospitalModule::displayHospitalDetails(const string& hospitalName) const
{
    Hospital* h = findHospitalByName(hospitalName);
    if (!h)
    {
        cout << "Hospital not found.\n";
        return;
    }

    cout << "\n=== Hospital Details ===\n";
    cout << "ID: " << h->getHospitalID() << "\n";
    cout << "Name: " << h->getName() << "\n";
    cout << "Sector: " << h->getSector() << "\n";
    cout << "Emergency Beds: " << h->getEmergencyBeds() << "\n";
    cout << "Specializations: " << h->getSpecializations() << "\n";

    h->displayDoctors();
    h->displayPatients();
}

// -------------------- Display Bed Status --------------------
void HospitalModule::displayEmergencyBedStatus() const
{
    cout << "\n=== Emergency Bed Status (Max-Heap Order) ===\n";
    bedHeap.displayHospitalsByBedAvailability();
}

// -------------------- Bed Statistics --------------------
int HospitalModule::getTotalBeds() const
{
    int total = 0;
    for (int i = 0; i < hospitalCount; i++)
        total += hospitals[i]->getEmergencyBeds();
    return total;
}

int HospitalModule::getAverageBeds() const
{
    if (hospitalCount == 0) return 0;
    return getTotalBeds() / hospitalCount;
}
