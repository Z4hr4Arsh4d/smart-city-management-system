#include "DoctorList.h"

// =======================
// Node Constructor
// =======================
DoctorList::Node::Node(const Doctor& d)
    : data(d), next(nullptr)
{
}

// =======================
// Constructor
// =======================
DoctorList::DoctorList()
{
    head = nullptr;
    count = 0;
}

// =======================
// Copy Constructor
// =======================
DoctorList::DoctorList(const DoctorList& other)
{
    head = nullptr;
    count = 0;
    copyFrom(other);
}

// =======================
// Assignment Operator
// =======================
DoctorList& DoctorList::operator=(const DoctorList& other)
{
    if (this != &other)
        copyFrom(other);
    return *this;
}

// =======================
// Deep Copy Helper
// =======================
void DoctorList::copyFrom(const DoctorList& other)
{
    clear();
    if (!other.head)
        return;

    Node* curOther = other.head;
    head = new Node(curOther->data);
    Node* cur = head;

    curOther = curOther->next;
    while (curOther)
    {
        cur->next = new Node(curOther->data);
        cur = cur->next;
        curOther = curOther->next;
    }
    count = other.count;
}

// =======================
// Destructor
// =======================
DoctorList::~DoctorList()
{
    clear();
}

// =======================
// Add Doctor at End
// =======================
void DoctorList::addDoctor(const Doctor& doc)
{
    Node* node = new Node(doc);

    if (!head)
    {
        head = node;
    }
    else
    {
        Node* cur = head;
        while (cur->next)
            cur = cur->next;

        cur->next = node;
    }
    count++;
}

// =======================
// Remove Doctor by ID
// =======================
bool DoctorList::removeDoctorByID(const string& id)
{
    Node* cur = head;
    Node* prev = nullptr;

    while (cur)
    {
        if (cur->data.getDoctorID() == id)
        {
            if (prev)
                prev->next = cur->next;
            else
                head = cur->next;

            delete cur;
            count--;
            return true;
        }
        prev = cur;
        cur = cur->next;
    }
    return false;
}

// =======================
// Get Doctor by ID
// =======================
bool DoctorList::getDoctorByID(const string& id, Doctor& out) const
{
    Node* cur = head;

    while (cur)
    {
        if (cur->data.getDoctorID() == id)
        {
            out = cur->data;
            return true;
        }
        cur = cur->next;
    }
    return false;
}

// =======================
// Get Doctor by Name
// =======================
bool DoctorList::getDoctorByName(const string& name, Doctor& out) const
{
    Node* cur = head;

    while (cur)
    {
        if (cur->data.getName() == name)
        {
            out = cur->data;
            return true;
        }
        cur = cur->next;
    }
    return false;
}

// =======================
// Contains by ID
// =======================
bool DoctorList::containsDoctorID(const string& id) const
{
    Node* cur = head;
    while (cur)
    {
        if (cur->data.getDoctorID() == id)
            return true;

        cur = cur->next;
    }
    return false;
}

// =======================
// Size / Empty
// =======================
int DoctorList::size() const { return count; }
bool DoctorList::isEmpty() const { return head == nullptr; }

// =======================
// Clear List
// =======================
void DoctorList::clear()
{
    Node* cur = head;
    while (cur)
    {
        Node* temp = cur;
        cur = cur->next;
        delete temp;
    }
    head = nullptr;
    count = 0;
}

// =======================
// Display
// =======================
void DoctorList::display() const
{
    if (!head)
    {
        cout << "No doctors available\n";
        return;
    }

    cout << "\n=== Doctor List (" << count << ") ===\n";
    Node* cur = head;

    while (cur)
    {
        cout << cur->data << "\n";
        cur = cur->next;
    }
}
