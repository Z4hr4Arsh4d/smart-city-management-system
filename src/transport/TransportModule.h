#pragma once
#include <iostream>
#include <string>
using namespace std;

#include "SchoolBus.h"
#include "BusHashTable.h"
#include "../education/EducationModule.h"
#include "BusRouteGraph.h"

class TransportModule
{
private:
    BusStop** stops;
    int stopCount, stopCapacity;

    Bus** buses;
    int busCount, busCapacity;

    string* companies;
    int companyCount, companyCapacity;

    BusHashTable* busTable;

    Sector::Graph* cityGraph;
    Facility::SubGraph* transportGraph;
    BusRouteGraph* routeGraph;

    void resizeStopArray();
    void resizeBusArray();
    void resizeCompanyArray();

public:

    TransportModule();
    ~TransportModule();

    // CSV Loaders
    void loadStopsCSV(const string& filename);
    void loadBusesCSV(const string& filename, EducationModule* edu = nullptr);

    void setCityGraph(Sector::Graph *graph);

    // Add manually
    void addStop(BusStop* stop);
    void addBus(Bus* bus);

    // Register companies
    void registerCompany(const string& name);

    // Build transport-only subgraph
    void buildTransportSubGraph();

    // Lookup
    BusStop* getStopByID(const string& id);
    Bus* getBusByID(const string& busNo);

    // Routing
    bool shortestPath(const string& stopA, const string& stopB);
    Bus* nearestBusToStop(const string& stopID);

    // Integration helpers
    BusStop* nearestStopToSchool(School* s);
    SchoolBus* registerSchoolBusInteractive(EducationModule* edu);

    // Simulation
    void simulateBusMovement(const string& busNo);
    void updateAllBuses();

    // Emergency
    bool emergencyRoute(const string& busNo, const string& destStopID);

    // Display
    void displayBus(const string& busNo);
    void printCompanies();
};
