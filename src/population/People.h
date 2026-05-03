#pragma once
#include<string>
#include<iostream>
using namespace std;

namespace Population
{

    struct People;

    struct RelationNode // tracks siblinga nd childrend
        {
            People* data;
            RelationNode* next;
        }; 

    struct People
    {
        string CNIC;
        string name;
        int age;
        string occupation;

        People *father, *mother, *spouse;

        RelationNode* childrenHead;
        RelationNode* siblingsHead;

        // Uses forward declarations to define relationships
        struct House* house;
        struct Street* street;
        struct Sector* sector;
        People(const string& cnic, const string& personName, int personAge, const string& personOccupation);
    };

    long long getCNICAsNumber(const string& cnic);

    struct PeopleHashNode
    {
        People* data;
        PeopleHashNode* next;
        PeopleHashNode(People* person);
    };

    class PeopleHashTable
    {
        int tableSize;
        int currentSize;
        PeopleHashNode** table;


        int hash(long long CNIC);
        void resize();

    public:
        PeopleHashTable(int size);
        ~PeopleHashTable();

        bool insertPerson(People* person);
        People* searchPerson(const string& cnic);
        bool deletePerson(const string& cnic);
    };
};