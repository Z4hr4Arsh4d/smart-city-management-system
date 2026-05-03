#pragma once
#include <iostream>
#include <string>
using namespace std;

enum PUBLIC_TYPE { MOSQUE, PARK, WATERCOOLER };

struct PublicFacility
{
    string name;
    string sectorName;
    PUBLIC_TYPE type;

    PublicFacility* next;

    PublicFacility(const string& n, const string& s, PUBLIC_TYPE t);
};

class PublicList
{
private:
    PublicFacility* head;

public:
    PublicList();
    ~PublicList();

    void addPublicFacility(const string& name, const string& sectorName, PUBLIC_TYPE type);

    PublicFacility* getHead() const;
    PublicFacility* findFacilityByName(const string& name) const;

    int getFacilityCount() const;
};

// Operator overload for printing PUBLIC_TYPE
ostream& operator<<(ostream& out, PUBLIC_TYPE t);
