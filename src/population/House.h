#pragma once
#include "People.h"

namespace Population
{
    struct PersonListNode // contains a list of people in a house
    {
        People* data;
        PersonListNode* next;
        PersonListNode(People* person);
    };


    class relationDefiner
    {
        PeopleHashTable* peopleTable;

        bool isAncestor(People* child, People* potentialAncestor, int depth = 0);

        bool relationExists(RelationNode* head, People* target);

    public:
        relationDefiner(PeopleHashTable* table);

        bool setFather(const string& childCNIC, const string& fatherCNIC);


        bool setMother(const string& childCNIC, const string& motherCNIC);

        bool setSpouse(const string& person1CNIC, const string& person2CNIC);

        bool addSibling(const string& personCNIC, const string& siblingCNIC);

        bool addChild(const string& parentCNIC, const string& childCNIC);
    };


    struct House
    {
  
        string houseNo;

        int numberOfResidents;
        House* next;

        PersonListNode* peopleHead;
        bool familyDefined;

        House(const string& houseNumber);

        void addResident(People* person);

        ~House();
    };
};
