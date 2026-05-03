#pragma once
#include "sectorList.h"
#include "../../core/Sector.h"

#include "../../core/utility/utility.h"


namespace Population
{

    class populationModule
    {
        Sector* sectorHead;
        PeopleHashTable peopleTable;
        relationDefiner relationMgr;

        void printIndent(int count);
        
        void removeFromRelationList(RelationNode*& head, People* target);
        void unlinkRelations(People* person);

        void freeAllData();

        void findTopAncestor(People* person, int depth, People*& best, int& bestDepth);

        void printDescendants(People* person, int level, int depthLimit);

        

        bool removeResidentFromHouse(House* house, People* person);

        int countResidents(House* house);

        bool ensureStreetAndHouse(const string& sectorName, const string& streetName, const string& houseNo);
    public:
        populationModule(int hashSize = 101);
        ~populationModule();

        void syncSectorsFromGraph(::Sector::Graph& graph);

        Sector* findSector(const string& name);

        Street* findStreet(Sector* sector, const string& name);

        House* findHouse(Street* street, const string& houseNo);

        void loadCSVData(const string filename);

        relationDefiner* relations();
        PeopleHashTable* table();

        bool addSector(const string& name);

        bool addStreet(const string& sectorName, const string& streetName);

        bool addHouse(const string& sectorName, const string& streetName, const string& houseNo);

        // Adds person only if sector already exists (user-defined rule). Streets/houses are created if missing.
        People* addPerson(const string& cnic, const string& name, int age, const string& occupation,
                                    const string& sectorName, const string& streetName, const string& houseNo,
                                    bool verbose = true);

        People* findPerson(const string& cnic);

        void printFamilyTree(const string& cnic);

        bool removePerson(const string& cnic);

        int populationByHouse(const string& sectorName, const string& streetName, const string& houseNo);

        int populationByStreet(const string& sectorName, const string& streetName);

        int populationBySector(const string& sectorName);

        int totalPopulation();
    };
};