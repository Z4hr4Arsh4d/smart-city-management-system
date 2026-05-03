#include "People.h"

namespace Population
{
    People::People(const string& cnic, const string& personName, int personAge, const string& personOccupation)
        : CNIC(cnic), name(personName), age(personAge), occupation(personOccupation),
          father(nullptr), mother(nullptr), spouse(nullptr),
          childrenHead(nullptr), siblingsHead(nullptr),
          house(nullptr), street(nullptr), sector(nullptr) {}

    long long getCNICAsNumber(const string& cnic)
    {
       // 61101-1111111-1 example format, remove dashes and get number

            string cnicNumStr = cnic;
            string newStr = "";
            for (char c : cnicNumStr)
            {
                if (c != '-')
                    newStr += c;
            }

            long long num = 0;
            for(char c : newStr)
            {
                if(c < '0' || c > '9')
                {
                    return -1; // invalid CNIC format
                }
                num = num * 10 + (c - '0');
            }
            return num; 
    }

    PeopleHashNode::PeopleHashNode(People* person) : data(person), next(nullptr) {}

    int PeopleHashTable::hash(long long CNIC)
    {
        return CNIC % tableSize;
    }

    void PeopleHashTable::resize()
    {
        int newSize = tableSize * 2 + 1;
            PeopleHashNode** newTable = new PeopleHashNode * [newSize];
            for (int i = 0; i < newSize; i++)
                newTable[i] = nullptr;

            for (int i = 0; i < tableSize; i++)
            {
                PeopleHashNode* current = table[i];
                while (current)
                {
                    PeopleHashNode* nextNode = current->next;
                    long long cnicNum = getCNICAsNumber(current->data->CNIC);
                    int newIndex = cnicNum % newSize;

                    current->next = newTable[newIndex];
                    newTable[newIndex] = current;

                    current = nextNode;
                }
            }

            delete[] table;
            table = newTable;
            tableSize = newSize; 
    }

    PeopleHashTable::PeopleHashTable(int size)
    {
        tableSize = size;
        currentSize = 0;
        table = new PeopleHashNode * [tableSize];
        for (int i = 0; i < tableSize; i++)
            table[i] = nullptr;
    }

    PeopleHashTable::~PeopleHashTable()
    {
        for (int i = 0; i < tableSize; i++)
        {
            PeopleHashNode* current = table[i];
            while (current)
            {
                PeopleHashNode* toDelete = current;
                current = current->next;

                //deletion of object inside handled by list
                delete toDelete;       // free node
            }
        }
        delete[] table;
    }

    bool PeopleHashTable::insertPerson(People* person)
    {
       if (!person)
                return false;

            long long cnicNum = getCNICAsNumber(person->CNIC);
            if (cnicNum < 0)
                return false;

            // prevent duplicates
            if (searchPerson(person->CNIC))
                return false;

            if (static_cast<double>(currentSize) / tableSize >= 0.7)
            {
                resize();
            }

            int index = hash(cnicNum);

            PeopleHashNode* newNode = new PeopleHashNode(person);
            newNode->next = table[index];
            table[index] = newNode;
            currentSize++;
            return true; 
    }

    People* PeopleHashTable::searchPerson(const string& cnic)
    {
       long long cnicNum = getCNICAsNumber(cnic);
            if (cnicNum < 0)
                return nullptr;
            int index = hash(cnicNum);
            PeopleHashNode* current = table[index];
            while (current)
            {
                if (current->data->CNIC == cnic)
                {
                    return current->data;
                }
                current = current->next;
            }
            return nullptr; 
    }

    bool PeopleHashTable::deletePerson(const string& cnic)
    {
        long long cnicNum = getCNICAsNumber(cnic);
            if (cnicNum < 0)
                return false;
            int index = hash(cnicNum);
            PeopleHashNode* current = table[index];
            PeopleHashNode* prev = nullptr;
            while (current)
            {
                if (current->data->CNIC == cnic)
                {
                    if (prev)
                    {
                        prev->next = current->next;
                    }
                    else
                    {
                        table[index] = current->next;
                    }
                    delete current; // free node, object deletion handled by list
                    currentSize--;
                    return true;
                }
                prev = current;
                current = current->next;
            }
            return false; 
    }
};