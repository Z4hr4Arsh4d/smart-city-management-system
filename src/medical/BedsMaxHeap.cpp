#include "BedsMaxHeap.h"

// ---------------------------
// Helper Index Functions
// ---------------------------
int BedsMaxHeap::getParent(int index) const { return (index - 1) / 2; }
int BedsMaxHeap::getLeftChild(int index) const { return 2 * index + 1; }
int BedsMaxHeap::getRightChild(int index) const { return 2 * index + 2; }

// ---------------------------
// Swap
// ---------------------------
void BedsMaxHeap::swap(BedHeapElement& a, BedHeapElement& b)
{
    BedHeapElement temp = a;
    a = b;
    b = temp;
}

// ---------------------------
// Constructor & Destructor
// ---------------------------
BedsMaxHeap::BedsMaxHeap(int cap)
{
    capacity = cap;
    size = 0;
    heap = new BedHeapElement[capacity];
}

BedsMaxHeap::~BedsMaxHeap()
{
    delete[] heap;
}

// ---------------------------
// Copy Constructor
// ---------------------------
BedsMaxHeap::BedsMaxHeap(const BedsMaxHeap& other)
{
    capacity = other.capacity;
    size = other.size;

    heap = new BedHeapElement[capacity];
    for (int i = 0; i < size; i++)
        heap[i] = other.heap[i];
}

// ---------------------------
// Assignment Operator
// ---------------------------
BedsMaxHeap& BedsMaxHeap::operator=(const BedsMaxHeap& other)
{
    if (this != &other)
    {
        delete[] heap;

        capacity = other.capacity;
        size = other.size;
        heap = new BedHeapElement[capacity];

        for (int i = 0; i < size; i++)
            heap[i] = other.heap[i];
    }
    return *this;
}

// ---------------------------
// Insert Element
// ---------------------------
void BedsMaxHeap::insert(int hospitalID, string hospitalName, int availableBeds)
{
    if (size >= capacity)
    {
        cerr << "Heap full! Cannot insert " << hospitalName << endl;
        return;
    }

    heap[size] = BedHeapElement(hospitalID, hospitalName, availableBeds);
    heapifyUp(size);
    size++;
}

// ---------------------------
// Heapify Up
// ---------------------------
void BedsMaxHeap::heapifyUp(int index)
{
    while (index > 0 && heap[getParent(index)] < heap[index])
    {
        swap(heap[index], heap[getParent(index)]);
        index = getParent(index);
    }
}

// ---------------------------
// Extract Max
// ---------------------------
BedHeapElement BedsMaxHeap::extractMax()
{
    if (size == 0)
        return BedHeapElement(-1, "", -1);

    BedHeapElement maxVal = heap[0];
    heap[0] = heap[size - 1];
    size--;

    if (size > 0)
        heapifyDown(0);

    return maxVal;
}

// ---------------------------
// Heapify Down
// ---------------------------
void BedsMaxHeap::heapifyDown(int index)
{
    while (true)
    {
        int largest = index;
        int left = getLeftChild(index);
        int right = getRightChild(index);

        if (left < size && heap[left] > heap[largest])
            largest = left;
        if (right < size && heap[right] > heap[largest])
            largest = right;

        if (largest != index)
        {
            swap(heap[index], heap[largest]);
            index = largest;
        }
        else
            break;
    }
}

// ---------------------------
// Get Max
// ---------------------------
BedHeapElement BedsMaxHeap::getMax() const
{
    if (size > 0) return heap[0];
    return BedHeapElement(-1, "", -1);
}

// ---------------------------
// Update Beds
// ---------------------------
bool BedsMaxHeap::updateBeds(int hospitalID, int newBedCount)
{
    for (int i = 0; i < size; i++)
    {
        if (heap[i].hospitalID == hospitalID)
        {
            int old = heap[i].availableBeds;
            heap[i].availableBeds = newBedCount;

            if (newBedCount > old)
                heapifyUp(i);
            else if (newBedCount < old)
                heapifyDown(i);

            return true;
        }
    }
    return false;
}

// ---------------------------
// Contains
// ---------------------------
bool BedsMaxHeap::contains(int hospitalID) const
{
    for (int i = 0; i < size; i++)
        if (heap[i].hospitalID == hospitalID)
            return true;
    return false;
}

// ---------------------------
// Get Hospital by ID
// ---------------------------
bool BedsMaxHeap::getHospitalByID(int hospitalID, BedHeapElement& result) const
{
    for (int i = 0; i < size; i++)
        if (heap[i].hospitalID == hospitalID)
        {
            result = heap[i];
            return true;
        }
    return false;
}

// ---------------------------
// Display
// ---------------------------
void BedsMaxHeap::displayHospitalsByBedAvailability() const
{
    if (size == 0)
    {
        cout << "Heap empty.\n";
        return;
    }

    cout << "\n=== Hospitals by Available Beds (Max-Heap Order) ===\n";
    for (int i = 0; i < size; i++)
    {
        cout << "[" << i + 1 << "] " << heap[i].hospitalName
            << " | Beds: " << heap[i].availableBeds;
        if (i == 0) cout << " <- MOST";
        cout << "\n";
    }
}

// ---------------------------
// Top N Hospitals
// ---------------------------
void BedsMaxHeap::getTopHospitalsByBeds(int count) const
{
    if (size == 0)
    {
        cout << "Heap empty.\n";
        return;
    }

    int limit = (count < size) ? count : size;
    cout << "\n=== Top " << limit << " Hospitals ===\n";

    for (int i = 0; i < limit; i++)
    {
        cout << i + 1 << ". " << heap[i].hospitalName
            << " - " << heap[i].availableBeds << " beds\n";
    }
}

// ---------------------------
// Size / Empty / Clear
// ---------------------------
int BedsMaxHeap::getSize() const { return size; }
bool BedsMaxHeap::isEmpty() const { return size == 0; }
void BedsMaxHeap::clear() { size = 0; }

// ---------------------------
// Display Heap Tree Structure
// ---------------------------
void BedsMaxHeap::displayHeapStructure() const
{
    if (size == 0)
    {
        cout << "Heap empty.\n";
        return;
    }

    cout << "\n=== Heap Structure (Tree View) ===\n";

    int level = 0, nodesThisLevel = 1, printed = 0;
    for (int i = 0; i < size; i++)
    {
        cout << heap[i].hospitalName << "(" << heap[i].availableBeds << ") ";
        printed++;

        if (printed == nodesThisLevel)
        {
            cout << "\n";
            level++;
            nodesThisLevel *= 2;
            printed = 0;
        }
    }
    cout << "\n";
}
