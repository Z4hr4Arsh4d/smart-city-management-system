#include "SchoolRankingQueue.h"

// --------------------------------------------------
// Constructor
// --------------------------------------------------
SchoolRankingQueue::SchoolRankingQueue(int cap)
{
    capacity = cap;
    size = 0;
    heap = new School * [capacity];
}

// --------------------------------------------------
// Destructor
// --------------------------------------------------
SchoolRankingQueue::~SchoolRankingQueue()
{
    delete[] heap;
}

// --------------------------------------------------
// Swap Helper
// --------------------------------------------------
void SchoolRankingQueue::swap(School*& a, School*& b)
{
    School* temp = a;
    a = b;
    b = temp;
}

// --------------------------------------------------
// Heapify Up (Insert)
// --------------------------------------------------
void SchoolRankingQueue::heapifyUp(int index)
{
    while (index > 0)
    {
        int parent = (index - 1) / 2;
        if (heap[parent]->getRating() >= heap[index]->getRating())
            return;

        swap(heap[parent], heap[index]);
        index = parent;
    }
}

// --------------------------------------------------
// Heapify Down (extractMax)
// --------------------------------------------------
void SchoolRankingQueue::heapifyDown(int index)
{
    while (true)
    {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;

        if (left < size && heap[left]->getRating() > heap[largest]->getRating())
            largest = left;

        if (right < size && heap[right]->getRating() > heap[largest]->getRating())
            largest = right;

        if (largest == index)
            return;

        swap(heap[index], heap[largest]);
        index = largest;
    }
}

// --------------------------------------------------
// Insert a school into ranking heap
// --------------------------------------------------
void SchoolRankingQueue::insert(School* s)
{
    if (size >= capacity)
    {
        cout << "Ranking Queue full! Cannot insert.\n";
        return;
    }

    heap[size] = s;
    heapifyUp(size);
    size++;
}

// --------------------------------------------------
// Extract highest ranked school (max heap)
// --------------------------------------------------
School* SchoolRankingQueue::extractMax()
{
    if (size == 0)
        return nullptr;

    School* top = heap[0];
    heap[0] = heap[size - 1];
    size--;

    heapifyDown(0);

    return top;
}

// --------------------------------------------------
// Check empty
// --------------------------------------------------
bool SchoolRankingQueue::isEmpty() const
{
    return size == 0;
}

// --------------------------------------------------
// Print ranking (Highest to Lowest)
// --------------------------------------------------
void SchoolRankingQueue::printRanking()
{
    cout << "\n--- School Ranking (Highest to Lowest) ---\n";

    // Backup
    int originalSize = size;
    School** backup = new School * [capacity];
    for (int i = 0; i < size; i++)
        backup[i] = heap[i];

    // Print ranks
    for (int rank = 1; rank <= originalSize; rank++)
    {
        School* top = extractMax();
        cout << rank << ". " << top->getName()
            << " | Rating: " << top->getRating() << endl;
    }

    // Restore
    delete[] heap;
    heap = backup;
    size = originalSize;
}

// --------------------------------------------------
// Build Ranking from array
// --------------------------------------------------
void SchoolRankingQueue::buildRanking(School** arr, int count)
{
    size = 0;  // reset heap

    for (int i = 0; i < count; i++)
        insert(arr[i]);
}
