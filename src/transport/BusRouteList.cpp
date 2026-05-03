#include "BusRouteList.h"

// ----------------------------------------------------------
// Constructor
// ----------------------------------------------------------
BusRouteList::BusRouteList()
{
    head = nullptr;
    tail = nullptr;
    size = 0;
}

// ----------------------------------------------------------
// Destructor
// ----------------------------------------------------------
BusRouteList::~BusRouteList()
{
    RouteNode* current = head;
    while (current != nullptr)
    {
        RouteNode* next = current->next;
        delete current;
        current = next;
    }
}

// ----------------------------------------------------------
// Add stop to end of route
// ----------------------------------------------------------
void BusRouteList::addStop(const string& stopID)
{
    RouteNode* newNode = new RouteNode(stopID);

    if (!head)
    {
        head = tail = newNode;
    }
    else
    {
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}

// ----------------------------------------------------------
// Remove first stop
// ----------------------------------------------------------
void BusRouteList::popFront()
{
    if (!head) return;

    RouteNode* temp = head;
    head = head->next;
    delete temp;
    size--;

    if (!head)
        tail = nullptr;
}

// ----------------------------------------------------------
// Getters
// ----------------------------------------------------------
int BusRouteList::getSize() const
{
    return size;
}

RouteNode* BusRouteList::getFront() const
{
    return head;
}

// ----------------------------------------------------------
// Print entire route
// ----------------------------------------------------------
void BusRouteList::printRoute() const
{
    RouteNode* current = head;

    while (current)
    {
        cout << current->stopID;
        if (current->next) cout << " -> ";
        current = current->next;
    }
    cout << endl;
}
