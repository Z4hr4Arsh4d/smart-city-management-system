#include "populationModule.h"

namespace Population
{
    void populationModule::printIndent(int count)
    {
        for(int i = 0; i < count; ++i)
            cout << ' ';
    }

    void populationModule::removeFromRelationList(RelationNode*& head, People* target)
    {
        RelationNode* cur = head;
        RelationNode* prev = nullptr;
        while(cur)
        {
            if(cur->data == target)
            {
                if(prev) prev->next = cur->next; else head = cur->next;
                delete cur;
                return;
            }
            prev = cur;
            cur = cur->next;
        }
    }

    void populationModule::unlinkRelations(People* person)
    {
        if(!person) return;

        // Detach from parents' children lists
        if(person->father)
            removeFromRelationList(person->father->childrenHead, person);
        if(person->mother)
            removeFromRelationList(person->mother->childrenHead, person);

        // Detach spouse link
        if(person->spouse && person->spouse->spouse == person)
            person->spouse->spouse = nullptr;

        // Detach from siblings (both sides)
        RelationNode* sib = person->siblingsHead;
        while(sib)
        {
            if(sib->data)
                removeFromRelationList(sib->data->siblingsHead, person);
            RelationNode* next = sib->next;
            delete sib;
            sib = next;
        }
        person->siblingsHead = nullptr;

        // Detach children back-links
        RelationNode* child = person->childrenHead;
        while(child)
        {
            if(child->data)
            {
                if(child->data->father == person) child->data->father = nullptr;
                if(child->data->mother == person) child->data->mother = nullptr;
            }
            RelationNode* next = child->next;
            delete child;
            child = next;
        }
        person->childrenHead = nullptr;

        person->father = person->mother = nullptr;
        person->spouse = nullptr;
    }

    void populationModule::freeAllData()
    {
        Sector* s = sectorHead;
        while(s)
        {
            Street* st = s->streetHead;
            while(st)
            {
                House* h = st->houseHead;
                while(h)
                {
                    PersonListNode* node = h->peopleHead;
                    while(node)
                    {
                        People* p = node->data;
                        unlinkRelations(p);
                        delete p;

                        PersonListNode* nextNode = node->next;
                        delete node;
                        node = nextNode;
                    }
                    h->peopleHead = nullptr;

                    House* nextHouse = h->next;
                    delete h;
                    h = nextHouse;
                }

                Street* nextStreet = st->next;
                delete st;
                st = nextStreet;
            }

            Sector* nextSector = s->next;
            delete s;
            s = nextSector;
        }
        sectorHead = nullptr;
    }

    void populationModule::findTopAncestor(People* person, int depth, People*& best, int& bestDepth)
    {
        if(!person) return;
        if(depth > bestDepth)
        {
            best = person;
            bestDepth = depth;
        }
        findTopAncestor(person->father, depth + 1, best, bestDepth);
        findTopAncestor(person->mother, depth + 1, best, bestDepth);
    }

    void populationModule::printDescendants(People* person, int level, int depthLimit)
    {
        if(!person) return;
        if(depthLimit <= 0) return; // safety guard

        printIndent(level * 2);
        cout << person->name << " (" << person->CNIC << ")";
        if(person->house)
            cout << " - House " << person->house->houseNo;
        if(person->street)
            cout << ", Street " << person->street->name;
        if(person->sector)
            cout << ", Sector " << person->sector->name;
        cout << endl;

        RelationNode* child = person->childrenHead;
        while(child)
        {
            printDescendants(child->data, level + 1, depthLimit - 1);
            child = child->next;
        }
    }

    Sector* populationModule::findSector(const string& name)
    {
        Sector* cur = sectorHead;
        while(cur)
        {
            if(cur->name == name)
                return cur;
            cur = cur->next;
        }
        return nullptr;
    }

    Street* populationModule::findStreet(Sector* sector, const string& name)
    {
        if(!sector) return nullptr;
        Street* cur = sector->streetHead;
        while(cur)
        {
            if(cur->name == name)
                return cur;
            cur = cur->next;
        }
        return nullptr;
    }

    House* populationModule::findHouse(Street* street, const string& houseNo)
    {
        if(!street) return nullptr;
        House* cur = street->houseHead;
        while(cur)
        {
            if(cur->houseNo == houseNo)
                return cur;
            cur = cur->next;
        }
        return nullptr;
    }

    bool populationModule::removeResidentFromHouse(House* house, People* person)
    {
        if(!house || !person) return false;
        PersonListNode* cur = house->peopleHead;
        PersonListNode* prev = nullptr;
        while(cur)
        {
            if(cur->data == person)
            {
                if(prev) prev->next = cur->next; else house->peopleHead = cur->next;
                house->numberOfResidents--;
                delete cur;
                return true;
            }
            prev = cur;
            cur = cur->next;
        }
        return false;
    }

    int populationModule::countResidents(House* house)
    {
        return house ? house->numberOfResidents : 0;
    }

    bool populationModule::ensureStreetAndHouse(const string& sectorName, const string& streetName, const string& houseNo)
    {
        Sector* sector = findSector(sectorName);
        if(!sector)
            return false;

        Street* street = findStreet(sector, streetName);
        if(!street)
        {
            Street* node = new Street(streetName);
            node->next = sector->streetHead;
            sector->streetHead = node;
            street = node;
        }

        if(!findHouse(street, houseNo))
        {
            House* node = new House(houseNo);
            node->next = street->houseHead;
            street->houseHead = node;
        }
        return true;
    }

    populationModule::populationModule(int hashSize)
        : sectorHead(nullptr), peopleTable(hashSize), relationMgr(&peopleTable)
    {
    }

    void populationModule::syncSectorsFromGraph(::Sector::Graph& graph)
    {
        ::Sector::Vertex* v = graph.getHead();
        while(v)
        {
            addSector(v->name);
            v = v->next;
        }
    }

    populationModule::~populationModule()
    {
        freeAllData();
    }


    void populationModule::loadCSVData(const string filename)
    {
        int rows = 0, cols = 0;
        string** data = UTIL::CSVParser(filename, rows, cols);
        if(!data)
        {
            cout << "Failed to load population data from CSV." << endl;
            return;
        }

        for(int r = 0; r < rows; r++)
        {
            if(cols < 7)
                continue; // insufficient data

            string cnic = data[r][0];
            string name = data[r][1];
            int age = UTIL::stringToInt(data[r][2]);
            string sector = data[r][3];
            string street = data[r][4];
            string houseNo = data[r][5];
            string occupation = data[r][6];

            if(!UTIL::validateCNIC(cnic))
                continue; // invalid CNIC

            if(name.empty() || age < 0 || sector.empty() || street.empty() || houseNo.empty())
                continue; // invalid data

            if(UTIL::isNumeric(name) || UTIL::isNumeric(sector) || UTIL::isNumeric(occupation))
                continue; // invalid data

            if(!UTIL::isNumeric(street) || !UTIL::isNumeric(houseNo))
                continue; // invalid data 
            

            addPerson(cnic, name, age, occupation, sector, street, houseNo, false);
        }

        UTIL::freeCSV(data, rows);
    }

    relationDefiner* populationModule::relations() { return &relationMgr; }
    PeopleHashTable* populationModule::table() { return &peopleTable; }

    bool populationModule::addSector(const string& name)
    {
        if(findSector(name)) return false;
        Sector* node = new Sector(name);
        node->next = sectorHead;
        sectorHead = node;
        return true;
    }

    bool populationModule::addStreet(const string& sectorName, const string& streetName)
    {
        Sector* sector = findSector(sectorName);
        if(!sector) return false;
        if(findStreet(sector, streetName)) return false;
        Street* node = new Street(streetName);
        node->next = sector->streetHead;
        sector->streetHead = node;
        return true;
    }

    bool populationModule::addHouse(const string& sectorName, const string& streetName, const string& houseNo)
    {
        Sector* sector = findSector(sectorName);
        if(!sector) return false;
        Street* street = findStreet(sector, streetName);
        if(!street) return false;
        if(findHouse(street, houseNo)) return false;
        House* node = new House(houseNo);
        node->next = street->houseHead;
        street->houseHead = node;
        return true;
    }

    // Adds person only if sector already exists (user-defined rule). Streets/houses are created if missing.
    People* populationModule::addPerson(const string& cnic, const string& name, int age, const string& occupation,
                                             const string& sectorName, const string& streetName, const string& houseNo,
                                             bool verbose)
    {
        if(!findSector(sectorName))
        {
            if(verbose)
                cout << "Sector '" << sectorName << "' is not defined; person not added." << endl;
            return nullptr;
        }

        // ensure street and house exist within the already-defined sector
        ensureStreetAndHouse(sectorName, streetName, houseNo);

        if(peopleTable.searchPerson(cnic))
        {
            if(verbose)
                cout << "Duplicate CNIC '" << cnic << "'; person not added." << endl;
            return nullptr;
        }

        Sector* sector = findSector(sectorName);
        Street* street = findStreet(sector, streetName);
        House* house = findHouse(street, houseNo);
        if(!sector || !street || !house)
        {
            if(verbose)
                cout << "Failed to locate sector/street/house after creation; person not added." << endl;
            return nullptr;
        }

        People* p = new People(cnic, name, age, occupation);
        p->sector = sector;
        p->street = street;
        p->house = house;

        house->addResident(p);
        peopleTable.insertPerson(p);
        return p;
    }

    People* populationModule::findPerson(const string& cnic)
    {
        return peopleTable.searchPerson(cnic);
    }

    void populationModule::printFamilyTree(const string& cnic)
    {
        People* start = peopleTable.searchPerson(cnic);
        if(!start)
        {
            cout << "Person not found." << endl;
            return;
        }

        People* root = start;
        int bestDepth = 0;
        findTopAncestor(start, 0, root, bestDepth);

        cout << "Family Tree starting from oldest ancestor:" << endl;
        printDescendants(root, 0, 256); // depth cap to avoid cycles
    }

    bool populationModule::removePerson(const string& cnic)
    {
        People* person = peopleTable.searchPerson(cnic);
        if(!person) return false;
        House* house = person->house;
        // unlink relations before deletion
        unlinkRelations(person);

        // unlink from house list first
        removeResidentFromHouse(house, person);

        // remove from hash (node only, not the person object)
        peopleTable.deletePerson(cnic);

        delete person; // prevent leak; ownership transferred here after unlinking
        return true;
    }

    int populationModule::populationByHouse(const string& sectorName, const string& streetName, const string& houseNo)
    {
        Sector* sector = findSector(sectorName);
        if(!sector) return 0;
        Street* street = findStreet(sector, streetName);
        if(!street) return 0;
        House* house = findHouse(street, houseNo);
        return countResidents(house);
    }

    int populationModule::populationByStreet(const string& sectorName, const string& streetName)
    {
        Sector* sector = findSector(sectorName);
        if(!sector) return 0;
        Street* street = findStreet(sector, streetName);
        if(!street) return 0;
        int total = 0;
        House* h = street->houseHead;
        while(h)
        {
            total += countResidents(h);
            h = h->next;
        }
        return total;
    }

    int populationModule::populationBySector(const string& sectorName)
    {
        Sector* sector = findSector(sectorName);
        if(!sector) return 0;
        int total = 0;
        Street* st = sector->streetHead;
        while(st)
        {
            House* h = st->houseHead;
            while(h)
            {
                total += countResidents(h);
                h = h->next;
            }
            st = st->next;
        }
        return total;
    }

    int populationModule::totalPopulation()
    {
        int total = 0;
        Sector* s = sectorHead;
        while(s)
        {
            total += populationBySector(s->name);
            s = s->next;
        }
        return total;
    } 
};