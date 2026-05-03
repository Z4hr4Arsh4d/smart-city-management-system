#pragma once
#include <iostream>
#include <string>
#include "../../core/Facility.h"
using namespace std;

class BusStop {
private:
    string stopID;
    string name;
    string sectorName;
    double latitude;
    double longitude;

    Facility::Node* facilityPtr;

public:
    BusStop();
    BusStop(const string& id,
        const string& n,
        double lat,
        double lon);

    void setSectorName(const string& s);
    void setStopID(const string& id);
    void setName(const string& nm);
    void setLatitude(double lat);
    void setLongitude(double lon);
    void setFacilityPtr(Facility::Node* ptr);

    string getStopID() const;
    string getName() const;
    double getLat() const;
    double getLon() const;
    string getSectorName() const;
    Facility::Node* getFacilityPtr() const;

    void display() const;
};
