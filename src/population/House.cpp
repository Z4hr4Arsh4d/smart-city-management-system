#include "House.h"

namespace Population
{
    PersonListNode::PersonListNode(People* person) : data(person), next(nullptr) {}

    bool relationDefiner::isAncestor(People* child, People* potentialAncestor, int depth)
    {
        if(!child) return false;
        if(depth > 256) return false; // safety cap to avoid infinite loops on bad data
        if(child->father == potentialAncestor || child->mother == potentialAncestor)
            return true;
        return isAncestor(child->father, potentialAncestor, depth + 1) || isAncestor(child->mother, potentialAncestor, depth + 1);
    }

    bool relationDefiner::relationExists(RelationNode* head, People* target)
    {
        RelationNode* temp = head;
        while(temp)
        {
            if(temp->data == target)
                return true;
            temp = temp->next;
        }
        return false;
    }

    relationDefiner::relationDefiner(PeopleHashTable* table) : peopleTable(table) {}

    bool relationDefiner::setFather(const string& childCNIC, const string& fatherCNIC)
    {
        People* child = peopleTable->searchPerson(childCNIC);
        People* father = peopleTable->searchPerson(fatherCNIC);

        if (!child || !father)
            return false;

        if(child == father)
            return false;

        // check if same house
        if(child->house != father->house)
            return false;


        // validation first
        if (isAncestor(father, child))
            return false; // to prevent cycles

        child->father = father;

        if(!relationExists(father->childrenHead, child))
        {
            RelationNode* childNode = new RelationNode{child, nullptr};
            RelationNode* fatherChildren = father->childrenHead;
            if (!fatherChildren)
            {
                father->childrenHead = childNode;
            }
            else
            {
                RelationNode* temp = fatherChildren;
                while (temp->next)
                    temp = temp->next;
                temp->next = childNode;
            }
        }
        
        return true;
    }

    
    bool relationDefiner::setMother(const string& childCNIC, const string& motherCNIC)
        {
            People* child = peopleTable->searchPerson(childCNIC);
            People* mother = peopleTable->searchPerson(motherCNIC);

            if (!child || !mother)
                return false;

            if(child == mother)
                return false;

            // check if same house
            if(child->house != mother->house)
                return false;

            if(isAncestor(mother, child))
                return false; // to prevent cycles

            child->mother = mother;
            if(!relationExists(mother->childrenHead, child))
            {
                RelationNode* childNode = new RelationNode{child, nullptr};
                RelationNode* motherChildren = mother->childrenHead;
                if (!motherChildren)
                {
                    mother->childrenHead = childNode;
                }
                else
                {
                    RelationNode* temp = motherChildren;
                    while (temp->next)
                        temp = temp->next;
                    temp->next = childNode;
                }
            }
            return true;
        }

        bool relationDefiner::setSpouse(const string& person1CNIC, const string& person2CNIC)
        {
            People* person1 = peopleTable->searchPerson(person1CNIC);
            People* person2 = peopleTable->searchPerson(person2CNIC);

            if (!person1 || !person2)
                return false;

            // check if same house
            if(person1->house != person2->house)
                return false;

            // prevent marrying self or if already married
            if (person1 == person2 || person1->spouse != nullptr || person2->spouse != nullptr)
                return false;

            person1->spouse = person2;
            person2->spouse = person1;
            return true;
        }

        bool relationDefiner::addSibling(const string& personCNIC, const string& siblingCNIC)
        {
            People* person = peopleTable->searchPerson(personCNIC);
            People* sibling = peopleTable->searchPerson(siblingCNIC);

            if (!person || !sibling)
                return false;

            if(person == sibling)
                return false;

            // check if same house
            if(person->house != sibling->house)
                return false;

            if(!relationExists(person->siblingsHead, sibling))
            {
                RelationNode* siblingNode = new RelationNode{ sibling, nullptr };
                RelationNode* personSiblings = person->siblingsHead;
                if (!personSiblings)
                {
                    person->siblingsHead = siblingNode;
                }
                else
                {
                    RelationNode* temp = personSiblings;
                    while (temp->next)
                        temp = temp->next;
                    temp->next = siblingNode;
                }
            }

            if(!relationExists(sibling->siblingsHead, person))
            {
                RelationNode* back = new RelationNode{ person, nullptr };
                RelationNode* sibList = sibling->siblingsHead;
                if(!sibList)
                {
                    sibling->siblingsHead = back;
                }
                else
                {
                    RelationNode* temp = sibList;
                    while(temp->next)
                        temp = temp->next;
                    temp->next = back;
                }
            }
            return true;
        }



        bool relationDefiner::addChild(const string& parentCNIC, const string& childCNIC)
        {
            People* parent = peopleTable->searchPerson(parentCNIC);
            People* child = peopleTable->searchPerson(childCNIC);

            if (!parent || !child)
                return false;

            if(parent == child)
                return false;

            // check if same house
            if(parent->house != child->house)
                return false;

            // determine if parent is father or mother
            if(isAncestor(child, parent))
                return false; // to prevent cycles

            bool alreadyRelated = (child->father == parent) || (child->mother == parent);
            bool assigned = false;

            // prefer filling empty slots rather than overwriting
            if(!alreadyRelated)
            {
                if(!child->father && child->mother != parent)
                {
                    child->father = parent;
                    assigned = true;
                }
                else if(!child->mother && child->father != parent)
                {
                    child->mother = parent;
                    assigned = true;
                }
                else
                {
                    return false; // both parents already set or conflicting
                }
            }
            else
            {
                assigned = true; // parent already linked
            }

            if(!relationExists(parent->childrenHead, child))
            {
                RelationNode* childNode = new RelationNode{ child, nullptr };
                RelationNode* parentChildren = parent->childrenHead;
                if(!parentChildren)
                {
                    parent->childrenHead = childNode;
                }
                else
                {
                    RelationNode* temp = parentChildren;
                    while(temp->next)
                        temp = temp->next;
                    temp->next = childNode;
                }
            }

            return assigned;
        }

        House::House(const string& houseNumber) : houseNo(houseNumber), numberOfResidents(0), next(nullptr), familyDefined(false), peopleHead(nullptr) {}

        void House::addResident(People* person)
        {
            PersonListNode* newNode = new PersonListNode(person);
            if (!peopleHead)
            {
                peopleHead = newNode;
            }
            else
            {
                PersonListNode* temp = peopleHead;
                while (temp->next)
                    temp = temp->next;
                temp->next = newNode;
            }
            numberOfResidents++;
            person->house = this;
        }

        House::~House()
        {
            PersonListNode* current = peopleHead;
            while (current)
            {
                PersonListNode* toDelete = current;
                current = current->next;
                delete toDelete;
            }
        }
};