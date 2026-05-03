#include "BusStop.h"

// Default Constructor
BusStop::BusStop() {
    stopID = "";
    name = "";
    latitude = 0.0;
    longitude = 0.0;
    facilityPtr = nullptr;
    sectorName = "";
}

// Parameterized Constructor
BusStop::BusStop(const string& id,
    const string& n,
    double lat,
    double lon)
    : stopID(id),
    name(n),
    latitude(lat),
    longitude(lon),
    sectorName(""),
    facilityPtr(nullptr)
{
}

// ------------------ Setters ------------------

void BusStop::setSectorName(const string& s) { sectorName = s; }
void BusStop::setStopID(const string& id) { stopID = id; }
void BusStop::setName(const string& nm) { name = nm; }
void BusStop::setLatitude(double lat) { latitude = lat; }
void BusStop::setLongitude(double lon) { longitude = lon; }
void BusStop::setFacilityPtr(Facility::Node* ptr) { facilityPtr = ptr; }

// ------------------ Getters ------------------

string BusStop::getStopID() const { return stopID; }
string BusStop::getName() const { return name; }
double BusStop::getLat() const { return latitude; }
double BusStop::getLon() const { return longitude; }
string BusStop::getSectorName() const { return sectorName; }

Facility::Node* BusStop::getFacilityPtr() const { return facilityPtr; }

// ------------------ Display ------------------

void BusStop::display() const
{
    cout << "Stop ID: " << stopID << "\n";
    cout << "Name: " << name << "\n";
    cout << "Sector     : " << sectorName << endl;
    cout << "Coordinates: (" << latitude << ", " << longitude << ")\n";

    if (facilityPtr)
        cout << "Linked Facility Node: " << facilityPtr->name << "\n";
    else
        cout << "Facility Node: NOT LINKED\n";

    cout << "------------------------------------\n";
}
