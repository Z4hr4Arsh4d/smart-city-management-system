#include "TransportModule.h"
#include<fstream>
// =============================================================
// RESIZE HELPERS
// =============================================================

void TransportModule::resizeStopArray()
{
    int newCap = stopCapacity * 2;
    BusStop** arr = new BusStop * [newCap];
    for (int i = 0; i < stopCount; i++) arr[i] = stops[i];
    delete[] stops;
    stops = arr;
    stopCapacity = newCap;
}

void TransportModule::resizeBusArray()
{
    int newCap = busCapacity * 2;
    Bus** arr = new Bus * [newCap];
    for (int i = 0; i < busCount; i++) arr[i] = buses[i];
    delete[] buses;
    buses = arr;
    busCapacity = newCap;
}

void TransportModule::resizeCompanyArray()
{
    int newCap = companyCapacity * 2;
    string* arr = new string[newCap];
    for (int i = 0; i < companyCount; i++) arr[i] = companies[i];
    delete[] companies;
    companies = arr;
    companyCapacity = newCap;
}


// =============================================================
// CONSTRUCTOR
// =============================================================

TransportModule::TransportModule()
{
    cityGraph = nullptr;

    stopCapacity = 200;
    stopCount = 0;
    stops = new BusStop * [stopCapacity];

    busCapacity = 200;
    busCount = 0;
    buses = new Bus * [busCapacity];

    companyCapacity = 20;
    companyCount = 0;
    companies = new string[companyCapacity];

    busTable = new BusHashTable(100);
    transportGraph = nullptr;

    routeGraph = new BusRouteGraph();

}

void TransportModule::setCityGraph(Sector::Graph *graph)
{
    cityGraph = graph;
}


// =============================================================
// DESTRUCTOR
// =============================================================

TransportModule::~TransportModule()
{
    for (int i = 0; i < stopCount; i++) delete stops[i];
    delete[] stops;

    for (int i = 0; i < busCount; i++) delete buses[i];
    delete[] buses;

    delete[] companies;
    delete busTable;
    delete transportGraph;
    delete routeGraph;

}


// =============================================================
// MANUAL ADD
// =============================================================

void TransportModule::addStop(BusStop* stop)
{
    if (stopCount >= stopCapacity) resizeStopArray();
    stops[stopCount++] = stop;
}

void TransportModule::addBus(Bus* bus)
{
    if (busCount >= busCapacity) resizeBusArray();
    buses[busCount++] = bus;
    busTable->insert(bus);
}


// =============================================================
// REGISTER COMPANY
// =============================================================

void TransportModule::registerCompany(const string& name)
{
    for (int i = 0; i < companyCount; i++)
        if (companies[i] == name) return;

    if (companyCount >= companyCapacity) resizeCompanyArray();
    companies[companyCount++] = name;
}


// =============================================================
// LOAD STOPS FROM CSV
// =============================================================
void TransportModule::loadStopsCSV(const string& filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Failed to open stops CSV.\n";
        return;
    }

    string line;
    getline(file, line); // skip header

    while (getline(file, line))
    {
        if (line.empty()) continue;

        // remove CR
        if (!line.empty() && (line.back() == '\r' || line.back() == '\n'))
            line.pop_back();

        string col0 = "", col1 = "", col2 = "", col3 = "";
        int col = 0;

        for (int i = 0; i < line.size(); i++)
        {
            char ch = line[i];

            if (ch == ',') { col++; continue; }

            if (col == 0) col0 += ch;
            else if (col == 1) col1 += ch;
            else if (col == 2) col2 += ch;
            else if (col == 3) col3 += ch;
        }

        // Trim spaces
        auto trim = [&](string& s)
            {
                while (!s.empty() && (s[0] == ' ' || s[0] == '\t' || s[0] == '"'))
                    s.erase(0, 1);

                while (!s.empty() && (s.back() == ' ' || s.back() == '\t' || s.back() == '\r' || s.back() == '"'))
                    s.pop_back();
            };

        trim(col0); // id
        trim(col1); // name
        trim(col2); // lat
        trim(col3); // long

        if(col0.empty() || col1.empty() || col2.empty() || col3.empty())
            continue;
        
        // ensure id and name are non-numeric, lat and lon are numeric
        if(UTIL::isNumeric(col0) || UTIL::isNumeric(col1) ||
           !UTIL::isNumeric(col2) || !UTIL::isNumeric(col3))
            continue;

            {
                string sector = "";
                if (cityGraph)
                {
                    Sector::Vertex* v = cityGraph->getHead();
                    size_t bestLen = 0;
                    while (v)
                    {
                        size_t pos = col1.find(v->name);
                        if (pos != string::npos && v->name.length() > bestLen)
                        {
                            sector = v->name;
                            bestLen = v->name.length();
                        }
                        v = v->next;
                    }
                }

                if(cityGraph->getVertex(sector) == nullptr)
                    continue;
            }

        


        cout << "Parsed: ID=[" << col0 << "] Name=[" << col1
            << "] LAT=[" << col2 << "] LON=[" << col3 << "]" << endl;

        double lat = stod(col2);
        double lon = stod(col3);

        BusStop* st = new BusStop(col0, col1, lat, lon);
        addStop(st);

        // Resolve sector name by scanning existing city graph vertices to handle names like "G-10 Markaz"
        string sector = "";
        if (cityGraph)
        {
            Sector::Vertex* v = cityGraph->getHead();
            size_t bestLen = 0;
            while (v)
            {
                size_t pos = col1.find(v->name);
                if (pos != string::npos && v->name.length() > bestLen)
                {
                    sector = v->name;
                    bestLen = v->name.length();
                }
                v = v->next;
            }
        }

        

        cityGraph->addFacility(sector, col0, col1, Facility::TRANSPORT);
        Facility::Node* f = cityGraph->getFacilityTypeHead(sector, Facility::TRANSPORT);
        st->setFacilityPtr(f);
    }

    file.close();
    cout << "Stops successfully loaded!\n";
}





// =============================================================
// LOAD BUSES FROM CSV WITH SCHOOL INTEGRATION
// CSV FORMAT:  BusNo , Company , CurrentStop , Route
// =============================================================

void TransportModule::loadBusesCSV(const string& filename, EducationModule* edu)
{
    int rows, cols;
    string** data = UTIL::CSVParser(filename, rows, cols);
    if (!data) return;

    for (int i = 0; i < rows; i++)
    {
        string busNo = data[i][0];
        string company = data[i][1];
        string currentStop = data[i][2];
        string routeStr = data[i][3];

        if(busNo.empty() || company.empty() ||
           currentStop.empty() || routeStr.empty())
            continue;

        if(UTIL::isNumeric(busNo) || UTIL::isNumeric(company) || UTIL::isNumeric(currentStop) || UTIL::isNumeric(routeStr))
            continue;

        registerCompany(company);

        // Check if company is actually a SCHOOL NAME
        School* schoolPtr = nullptr;
        if (edu)
            schoolPtr = edu->findSchoolByName(company);

        Bus* bus = nullptr;
        if (schoolPtr)
            bus = new SchoolBus(busNo, schoolPtr);
        else
            bus = new Bus(busNo, company);

        // ---------------------------------------------------------
        //           PARSE ROUTE  "Stop1 > Stop2 > Stop3"
        // ---------------------------------------------------------
        int count = 1;
        for (int j = 0; j < routeStr.size(); j++)
            if (routeStr[j] == '>') count++;

        string* parsed = new string[count];
        string temp = "";
        int idx = 0;

        for (int j = 0; j < routeStr.size(); j++)
        {
            char c = routeStr[j];

            if (c == '>')
            {
                // trim leading/trailing spaces
                while (temp.size() > 0 && temp[0] == ' ') temp.erase(0, 1);
                while (temp.size() > 0 && temp[temp.size() - 1] == ' ')
                    temp.pop_back();

                parsed[idx++] = temp;
                temp = "";
            }
            else temp += c;
        }

        // last segment
        while (temp.size() > 0 && temp[0] == ' ') temp.erase(0, 1);
        while (temp.size() > 0 && temp[temp.size() - 1] == ' ')
            temp.pop_back();
        parsed[idx] = temp;

        // ---------------------------------------------------------
        //       ADD ROUTE TO BUS + BUILD ROUTE GRAPH
        // ---------------------------------------------------------
        for (int k = 0; k < count; k++)
            bus->addStopToRoute(parsed[k]);

        // Build edges in routeGraph to allow Dijkstra to run correctly
        for (int k = 0; k < count - 1; k++)
        {
            routeGraph->addEdge(parsed[k], parsed[k + 1], 1);  // undirected weight=1
        }

        delete[] parsed;

        // ---------------------------------------------------------
        //          SET CURRENT STOP POINTER
        // ---------------------------------------------------------
        bus->setCurrentStop(getStopByID(currentStop));

        // Add bus to system
        addBus(bus);
    }

    UTIL::freeCSV(data, rows);
}


// =============================================================
// BUILD TRANSPORT SUBGRAPH
// =============================================================

void TransportModule::buildTransportSubGraph()
{
    if (transportGraph) delete transportGraph;
    transportGraph = cityGraph->getSubgraph(Facility::TRANSPORT);
}


// =============================================================
// LOOKUPS
// =============================================================

BusStop* TransportModule::getStopByID(const string& id)
{
    for (int i = 0; i < stopCount; i++)
        if (stops[i]->getStopID() == id) return stops[i];
    return nullptr;
}

Bus* TransportModule::getBusByID(const string& busNo)
{
    return busTable->search(busNo);
}


// =============================================================
// SHORTEST PATH
// =============================================================

bool TransportModule::shortestPath(const string& A, const string& B)
{
    if (!transportGraph) return false;

    BusStop* sA = getStopByID(A);
    BusStop* sB = getStopByID(B);
    if (!sA || !sB) return false;

    string* path = nullptr;
    int len = 0, dist = 0;

    bool ok = transportGraph->shortestPath(
        sA->getName(), sB->getName(), path, len, dist);

    if (ok)
    {
        cout << "Shortest Path (" << dist << "): ";
        for (int i = 0; i < len; i++)
            cout << path[i] << (i < len - 1 ? " -> " : "");
        cout << endl;
    }

    delete[] path;
    return ok;
}


// =============================================================
// NEAREST STOP TO SCHOOL
// =============================================================

BusStop* TransportModule::nearestStopToSchool(School* s)
{
    if (!s) return nullptr;

    // Find stop in same sector (simple integration)
    for (int i = 0; i < stopCount; i++)
        if (stops[i]->getSectorName() == s->getSector())
            return stops[i];

    return nullptr;
}

Bus* TransportModule::nearestBusToStop(const string& stopID)
{
    BusStop* target = getStopByID(stopID);
    if (!target)
    {
        cout << "Stop not found.\n";
        return nullptr;
    }

    double bestDist = 1e30;
    Bus* bestBus = nullptr;

    for (int i = 0; i < busCount; i++)
    {
        Bus* b = buses[i];
        BusStop* cs = b->getCurrentStop();

        if (!cs) continue;

        double dx = cs->getLat() - target->getLat();
        double dy = cs->getLon() - target->getLon();
        double dist = dx * dx + dy * dy;

        if (dist < bestDist)
        {
            bestDist = dist;
            bestBus = b;
        }
    }

    return bestBus;
}

// =============================================================
// REGISTER SCHOOL BUS MANUALLY
// =============================================================

SchoolBus* TransportModule::registerSchoolBusInteractive(EducationModule* edu)
{
    string busNo;
    cout << "Enter Bus No: ";
    cin >> busNo;

    cin.ignore();
    string schoolName;
    cout << "Enter School Name: ";
    getline(cin, schoolName);

    School* schoolPtr = edu->findSchoolByName(schoolName);
    if (!schoolPtr)
    {
        cout << "School not found.\n";
        return nullptr;
    }

    // Create bus
    SchoolBus* sb = new SchoolBus(busNo, schoolPtr);

    // Ask user for starting stop
    string startStop;
    cout << "Enter Current Stop ID for this School Bus: ";
    cin >> startStop;

    BusStop* st = getStopByID(startStop);
    if (!st)
    {
        cout << "Invalid stop ID.\n";
        delete sb;
        return nullptr;
    }
    sb->setCurrentStop(st);

    sb->addToHistory(startStop);

    cin.ignore();
    string routeStr;
    cout << "Enter Bus Route (format: Stop1 > Stop2 > Stop3): ";
    getline(cin, routeStr);

    string temp = "";
    for (char c : routeStr)
    {
        if (c == '>')
        {
            // clean spaces
            if (temp[0] == ' ') temp.erase(0, 1);
            if (temp.back() == ' ') temp.pop_back();

            sb->addStopToRoute(temp);
            temp = "";
        }
        else
            temp += c;
    }
    if (!temp.empty())
    {
        if (temp[0] == ' ') temp.erase(0, 1);
        if (temp.back() == ' ') temp.pop_back();
        sb->addStopToRoute(temp);
    }

    addBus(sb);
    sb->autoLoadStudents();
    cout << "School Bus Registered Successfully!\n";

    return sb;
}


// =============================================================
// SIMULATION
// =============================================================

void TransportModule::simulateBusMovement(const string& busNo)
{
    Bus* b = getBusByID(busNo);
    if (!b) return;

    RouteNode* nextNode = b->getNextStop();
    if (!nextNode) {
        cout << "No more stops.\n";
        return;
    }

    b->moveToNextStop();

    BusStop* newStop = getStopByID(nextNode->stopID);
    if (newStop)
        b->setCurrentStop(newStop);
}


void TransportModule::updateAllBuses()
{
    for (int i = 0; i < busCount; i++)
        simulateBusMovement(buses[i]->getBusNo());
}


// =============================================================
// EMERGENCY ROUTING
// =============================================================

bool TransportModule::emergencyRoute(const string& busNo, const string& destStopID)
{
    Bus* b = getBusByID(busNo);
    if (!b) return false;

    BusStop* cur = b->getCurrentStop();
    if (!cur) return false;

    string* path = nullptr;
    int len = 0, dist = 0;

    bool ok = routeGraph->shortestPath(cur->getStopID(), destStopID,
        path, len, dist);

    if (!ok) {
        cout << "NO EMERGENCY ROUTE FOUND.\n";
        return false;
    }

    cout << "\n*** EMERGENCY ROUTE FOUND ***\n";
    for (int i = 0; i < len; i++)
        cout << "  -> " << path[i] << "\n";

    cout << "Total Distance: " << dist << "\n";

    delete[] path;
    return true;
}


// =============================================================
// DISPLAY
// =============================================================

void TransportModule::displayBus(const string& busNo)
{
    Bus* b = getBusByID(busNo);
    if (!b) cout << "Bus Not Found\n";
    else b->displayInfo();
}

void TransportModule::printCompanies()
{
    cout << "\n--- Transport Companies ---\n";
    for (int i = 0; i < companyCount; i++)
        cout << " - " << companies[i] << endl;
    cout << "---------------------------\n";
}
