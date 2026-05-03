#include "Public.h"

// -------------------- PublicFacility Constructor --------------------
PublicFacility::PublicFacility(const string& n, const string& s, PUBLIC_TYPE t)
    : name(n), sectorName(s), type(t), next(nullptr)
{
}

// -------------------- PublicList Constructor --------------------
PublicList::PublicList()
    : head(nullptr)
{
}

// -------------------- PublicList Destructor --------------------
PublicList::~PublicList()
{
    PublicFacility* curr = head;
    while (curr != nullptr)
    {
        PublicFacility* temp = curr;
        curr = curr->next;
        delete temp;
    }
}

// -------------------- Add Facility --------------------
void PublicList::addPublicFacility(const string& name, const string& sectorName, PUBLIC_TYPE type)
{
    PublicFacility* newFacility = new PublicFacility(name, sectorName, type);

    if (head == nullptr)
    {
        head = newFacility;
    }
    else
    {
        PublicFacility* curr = head;
        while (curr->next != nullptr)
            curr = curr->next;

        curr->next = newFacility;
    }
}

// -------------------- Get Head --------------------
PublicFacility* PublicList::getHead() const
{
    return head;
}

// -------------------- Find by Name --------------------
PublicFacility* PublicList::findFacilityByName(const string& name) const
{
    PublicFacility* curr = head;

    while (curr != nullptr)
    {
        if (curr->name == name)
            return curr;

        curr = curr->next;
    }

    return nullptr;
}

// -------------------- Count Facilities --------------------
int PublicList::getFacilityCount() const
{
    int count = 0;
    PublicFacility* curr = head;

    while (curr != nullptr)
    {
        count++;
        curr = curr->next;
    }

    return count;
}

// -------------------- PUBLIC_TYPE Print Operator --------------------
ostream& operator<<(ostream& out, PUBLIC_TYPE t)
{
    switch (t)
    {
    case MOSQUE:        out << "MOSQUE"; break;
    case PARK:          out << "PARK"; break;
    case WATERCOOLER:   out << "WATERCOOLER"; break;
    default:            out << "UNKNOWN"; break;
    }
    return out;
}
