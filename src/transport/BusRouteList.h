#pragma once
#include <iostream>
#include <string>
using namespace std;

#include "RouteNode.h"

class BusRouteList
{
private:
    RouteNode* head;
    RouteNode* tail;
    int size;

public:
    BusRouteList();
    ~BusRouteList();

    void addStop(const string& stopID);
    void popFront();

    int getSize() const;
    RouteNode* getFront() const;

    void printRoute() const;
};
