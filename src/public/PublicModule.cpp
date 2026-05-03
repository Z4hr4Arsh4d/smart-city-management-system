#include "PublicModule.h"

// ---------------- Constructor ----------------
PublicModule::PublicModule()
    : publicGraph(nullptr)
{
}

// ---------------- Destructor ----------------
PublicModule::~PublicModule()
{
    delete publicGraph;
}

// ---------------- Add Public Facility ----------------
void PublicModule::addPublicFacility(const string& name, const string& sectorName, PUBLIC_TYPE type)
{
    publicList.addPublicFacility(name, sectorName, type);
}

// ---------------- Print All Facilities ----------------
void PublicModule::printAll() const
{
    PublicFacility* curr = publicList.getHead();

    if (!curr)
    {
        cout << "No public facilities available." << endl;
        return;
    }

    while (curr != nullptr)
    {
        cout << "Name: " << curr->name
            << ", Sector: " << curr->sectorName
            << ", Type: ";

        switch (curr->type)
        {
        case MOSQUE:      cout << "Mosque";       break;
        case PARK:        cout << "Park";         break;
        case WATERCOOLER: cout << "Water Cooler"; break;
        }

        cout << endl;
        curr = curr->next;
    }
}

// ---------------- Print By Type ----------------
void PublicModule::printType(PUBLIC_TYPE type) const
{
    PublicFacility* curr = publicList.getHead();

    if (!curr)
    {
        cout << "No public facilities available." << endl;
        return;
    }

    while (curr != nullptr)
    {
        if (curr->type == type)
        {
            cout << "Name: " << curr->name
                << ", Sector: " << curr->sectorName
                << endl;
        }
        curr = curr->next;
    }
}

// ---------------- Search Facility by Name ----------------
bool PublicModule::searchFacility(const string& name) const
{
    return publicList.findFacilityByName(name) != nullptr;
}

// ---------------- Build Subgraph ----------------
void PublicModule::buildSubgraph(Sector::Graph& graph)
{
    if (publicGraph)
        delete publicGraph;

    publicGraph = graph.getSubgraph(Facility::PUBLIC);

    if (!publicGraph)
        cout << "No public facilities found in Sector Graph.\n";
    else
        cout << "Public Facility SubGraph created successfully.\n";
}

// ---------------- Find Nearest Public Facility ----------------
PublicFacility* PublicModule::nearestPublicFacility(const string& facilityName)
{
    if (!publicGraph)
    {
        cout << "Public Facility Graph not built.\n";
        return nullptr;
    }

    Facility::Vertex* startV = publicGraph->getVertex(facilityName);

    if (!startV)
    {
        cout << "Public Facility not found in subgraph.\n";
        return nullptr;
    }

    string nearestName = "";
    int bestDist = 20000000;

    Facility::Vertex* v = publicGraph->getHead();

    while (v)
    {
        if (v->name != facilityName)
        {
            string* path = nullptr;
            int pathLen = 0;
            int dist = -1;

            bool ok = publicGraph->shortestPath(facilityName, v->name, path, pathLen, dist);

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

    return publicList.findFacilityByName(nearestName);
}
