#pragma once
#include <string>
#include <iostream>
using namespace std;

#include "public.h"              // PublicFacility + PublicList
#include "../../core/Sector.h"   // Facility::SubGraph, Facility::Vertex

class PublicModule
{
private:
    PublicList publicList;
    Facility::SubGraph* publicGraph;

public:
    PublicModule();
    ~PublicModule();

    void addPublicFacility(const string& name, const string& sectorName, PUBLIC_TYPE type);

    void printAll() const;
    void printType(PUBLIC_TYPE type) const;

    bool searchFacility(const string& name) const;

    void buildSubgraph(Sector::Graph& graph);

    PublicFacility* nearestPublicFacility(const string& facilityName);
};
