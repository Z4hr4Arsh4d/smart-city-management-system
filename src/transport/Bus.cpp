#include "Bus.h"
#include <iostream>

using namespace std;

// ---------------------------------------------------------
// Constructor
// ---------------------------------------------------------
Bus::Bus(string no, string comp)
    : busNo(no), company(comp), schoolBus(false),
    passengers(30), history(100)
{
    currentStop = nullptr;
}

// ---------------------------------------------------------
// Destructor
// ---------------------------------------------------------
Bus::~Bus() {

}


// ---------------------------------------------------------
// Getters
// ---------------------------------------------------------
string Bus::getBusNo() const { return busNo; }
string Bus::getCompany() const { return company; }
bool Bus::isSchoolBus() const { return schoolBus; }
BusStop* Bus::getCurrentStop() const { return currentStop; }


// ---------------------------------------------------------
// Route operations
// ---------------------------------------------------------
void Bus::addStopToRoute(const string& stopID)
{
    route.addStop(stopID);
}

RouteNode* Bus::getNextStop() const
{
    return route.getFront();
}

void Bus::moveToNextStop()
{
    RouteNode* nextNode = route.getFront();
    if (!nextNode)
    {
        cout << "Bus " << busNo << " has completed its route.\n";
        return;
    }

    // Push current stop into history BEFORE moving
    if (currentStop)
        history.push(currentStop->getStopID());

    cout << "Bus " << busNo << " moving from "
        << (currentStop ? currentStop->getStopID() : "(none)")
        << " to " << nextNode->stopID << endl;

    // Remove next node from route
    route.popFront();
}



// ---------------------------------------------------------
// Passenger operations
// ---------------------------------------------------------
void Bus::boardPassenger(const string& name)
{
    passengers.enqueue(name);
}

void Bus::dropPassenger()
{
    string removed = "";
    passengers.dequeue(removed);
}

PassengerQueue& Bus::getPassengerQueue()
{
    return passengers;
}


// ---------------------------------------------------------
// Stop assignment
// ---------------------------------------------------------
void Bus::setCurrentStop(BusStop* stop)
{
    currentStop = stop;
}


// ---------------------------------------------------------
// Display Info
// ---------------------------------------------------------
void Bus::displayInfo() const
{
    cout << "-------------------------------\n";
    cout << "Bus No: " << busNo << endl;
    cout << "Company: " << company << endl;
    cout << "Type: " << (schoolBus ? "School Bus" : "Public Bus") << endl;

    if (currentStop)
        cout << "Current Stop: " << currentStop->getName() << endl;
    else
        cout << "Current Stop: (not assigned)\n";

    cout << "Route: ";
    route.printRoute();
    cout << "-------------------------------\n";
}

void Bus::addToHistory(const string& stopID)
{
    history.push(stopID);
}
void Bus::trackRoute() const
{
    cout << "\n=============== BUS ROUTE TRACKING ===============\n";
    cout << "Bus No       : " << busNo << endl;
    cout << "Company      : " << company << endl;

    if (currentStop)
        cout << "Current Stop : " << currentStop->getStopID() << endl;
    else
        cout << "Current Stop : (not assigned)\n";

    cout << "\n--- Past Stops (History Stack) ---\n";
    history.printHistory();

    cout << "\n--- Upcoming Route ---\n";
    route.printRoute();

    cout << "===================================================\n";
}


// ---------------------------------------------------------
// Travel History
// ---------------------------------------------------------
void Bus::printTravelHistory() const
{
    history.printHistory();
}
