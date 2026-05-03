#pragma once
#include <string>
#include <iostream>

using namespace std;

#include "BusRouteList.h"
#include "TravelHistoryStack.h"
#include "PassengerQueue.h"
#include "BusStop.h"

class Bus
{
protected:
    string busNo;
    string company;
    bool schoolBus;

    BusRouteList route;
    TravelHistoryStack history;
    PassengerQueue passengers;

    BusStop* currentStop;

public:
    // Constructor & Destructor
    Bus(string no = "", string comp = "");
    virtual ~Bus();

    // Getters
    string getBusNo() const;
    string getCompany() const;
    bool isSchoolBus() const;
    BusStop* getCurrentStop() const;

    // Route
    void addStopToRoute(const string& stopID);
    RouteNode* getNextStop() const;
    virtual void moveToNextStop();

    // Passengers
    void boardPassenger(const string& name);
    void dropPassenger();
    PassengerQueue& getPassengerQueue();

    // Stop assignment
    void setCurrentStop(BusStop* stop);
    void trackRoute() const;

    // Display
    virtual void displayInfo() const;
    void addToHistory(const string& stopID);

    // Travel history
    void printTravelHistory() const;
};
