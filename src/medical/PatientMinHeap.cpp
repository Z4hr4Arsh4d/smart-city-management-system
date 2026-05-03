#include "PatientMinHeap.h"

// -----------------------------
// Parent / Child Calculations
// -----------------------------
int PatientMinHeap::getParent(int i) const { return (i - 1) / 2; }
int PatientMinHeap::getLeftChild(int i) const { return 2 * i + 1; }
int PatientMinHeap::getRightChild(int i) const { return 2 * i + 2; }

// -----------------------------
// Compare Priorities
// -----------------------------
bool PatientMinHeap::isHigherPriority(const Patient& a, const Patient& b) const
{
    return a.Priototy < b.Priototy;
}

// -----------------------------
// Constructor
// -----------------------------
PatientMinHeap::PatientMinHeap(int cap)
    : capacity(cap), size(0)
{
    heap = new Patient[capacity];
}

// -----------------------------
// Destructor
// -----------------------------
PatientMinHeap::~PatientMinHeap()
{
    delete[] heap;
}

// -----------------------------
// Copy Constructor
// -----------------------------
PatientMinHeap::PatientMinHeap(const PatientMinHeap& other)
    : capacity(other.capacity), size(other.size)
{
    heap = new Patient[capacity];
    for (int i = 0; i < size; ++i)
        heap[i] = other.heap[i];
}

// -----------------------------
// Assignment Operator
// -----------------------------
PatientMinHeap& PatientMinHeap::operator=(const PatientMinHeap& other)
{
    if (this != &other)
    {
        delete[] heap;
        capacity = other.capacity;
        size = other.size;
        heap = new Patient[capacity];
        for (int i = 0; i < size; ++i)
            heap[i] = other.heap[i];
    }
    return *this;
}

// -----------------------------
// Heapify Up
// -----------------------------
void PatientMinHeap::heapifyUp(int i)
{
    while (i > 0 && isHigherPriority(heap[i], heap[getParent(i)]))
    {
        Patient temp = heap[i];
        heap[i] = heap[getParent(i)];
        heap[getParent(i)] = temp;

        i = getParent(i);
    }
}

// -----------------------------
// Heapify Down
// -----------------------------
void PatientMinHeap::heapifyDown(int i)
{
    int smallest = i;
    int left = getLeftChild(i);
    int right = getRightChild(i);

    if (left < size && isHigherPriority(heap[left], heap[smallest]))
        smallest = left;

    if (right < size && isHigherPriority(heap[right], heap[smallest]))
        smallest = right;

    if (smallest != i)
    {
        Patient temp = heap[i];
        heap[i] = heap[smallest];
        heap[smallest] = temp;
        heapifyDown(smallest);
    }
}

// -----------------------------
// Insert Patient
// -----------------------------
void PatientMinHeap::insert(const Patient& patient)
{
    if (size >= capacity)
    {
        cout << "Heap capacity full! Cannot insert patient "
            << patient.getPatientName() << "\n";
        return;
    }

    heap[size] = patient;
    heapifyUp(size);
    size++;
}

// -----------------------------
// Extract Min Priority Patient
// -----------------------------
bool PatientMinHeap::extractMin(Patient& result)
{
    if (size == 0)
    {
        cout << "Heap is empty! No patient to extract.\n";
        return false;
    }

    result = heap[0];
    heap[0] = heap[size - 1];
    size--;

    if (size > 0)
        heapifyDown(0);

    return true;
}

// -----------------------------
// Peek Highest Priority
// -----------------------------
bool PatientMinHeap::peek(Patient& result) const
{
    if (size == 0)
    {
        cout << "Heap is empty!\n";
        return false;
    }

    result = heap[0];
    return true;
}

// -----------------------------
// Update Priority
// -----------------------------
bool PatientMinHeap::updatePatientPriority(const string& patientName, int newPriority)
{
    int index = -1;

    for (int i = 0; i < size; ++i)
    {
        if (heap[i].getPatientName() == patientName)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        cout << "Patient not found: " << patientName << "\n";
        return false;
    }

    int oldPriority = heap[index].Priototy;
    heap[index].Priototy = newPriority;

    if (newPriority < oldPriority)
        heapifyUp(index);
    else if (newPriority > oldPriority)
        heapifyDown(index);

    return true;
}

// -----------------------------
// Contains Patient?
// -----------------------------
bool PatientMinHeap::containsPatient(const string& patientName) const
{
    for (int i = 0; i < size; ++i)
    {
        if (heap[i].getPatientName() == patientName)
            return true;
    }
    return false;
}

// -----------------------------
// Get Size / Empty
// -----------------------------
int PatientMinHeap::getSize() const { return size; }
bool PatientMinHeap::isEmpty() const { return size == 0; }

// -----------------------------
// Display
// -----------------------------
void PatientMinHeap::display() const
{
    if (size == 0)
    {
        cout << "Priority Queue is empty.\n";
        return;
    }

    cout << "\n=== Patient Priority Queue (Min-Heap) ===\n";
    cout << "Total Patients: " << size << "\n";

    for (int i = 0; i < size; ++i)
    {
        cout << "  [Priority " << heap[i].Priototy << "] "
            << heap[i].getPatientName();

        if (i == 0)
            cout << " <- CRITICAL (Next to be treated)";
        cout << "\n";
    }
}

// -----------------------------
// Heap Tree Structure
// -----------------------------
void PatientMinHeap::displayHeapStructure() const
{
    if (size == 0)
    {
        cout << "Heap is empty.\n";
        return;
    }

    cout << "\n=== Heap Structure (Tree View) ===\n";
    int nodesInLevel = 1;
    int displayed = 0;

    for (int i = 0; i < size; ++i)
    {
        cout << heap[i].getPatientName()
            << "(" << heap[i].Priototy << ") ";

        displayed++;
        if (displayed == nodesInLevel)
        {
            cout << "\n";
            nodesInLevel *= 2;
            displayed = 0;
        }
    }
    cout << "\n";
}

// -----------------------------
// Get All Patients Sorted
// -----------------------------
void PatientMinHeap::getAllPatientsSortedByPriority(Patient* result, int& count) const
{
    if (size == 0)
    {
        count = 0;
        return;
    }

    PatientMinHeap tempHeap = *this;
    count = 0;

    Patient temp;
    while (tempHeap.extractMin(temp) && count < 100)
    {
        result[count++] = temp;
    }
}
