#include "PassengerQueue.h"

// ---------------------------------------------------------
// Constructor
// ---------------------------------------------------------
PassengerQueue::PassengerQueue(int cap)
{
    capacity = cap;
    arr = new string[capacity];
    front = 0;
    rear = -1;
    count = 0;
}

// ---------------------------------------------------------
// Destructor
// ---------------------------------------------------------
PassengerQueue::~PassengerQueue()
{
    delete[] arr;
}

// ---------------------------------------------------------
// Check Full
// ---------------------------------------------------------
bool PassengerQueue::isFull() const
{
    return count == capacity;
}

// ---------------------------------------------------------
// Check Empty
// ---------------------------------------------------------
bool PassengerQueue::isEmpty() const
{
    return count == 0;
}

// ---------------------------------------------------------
// Enqueue
// ---------------------------------------------------------
bool PassengerQueue::enqueue(const string& passengerName)
{
    if (isFull())
    {
        cout << "Queue is full. Cannot add passenger: " << passengerName << endl;
        return false;
    }

    rear = (rear + 1) % capacity;
    arr[rear] = passengerName;
    count++;

    return true;
}

// ---------------------------------------------------------
// Dequeue
// ---------------------------------------------------------
bool PassengerQueue::dequeue(string& passengerName)
{
    if (isEmpty())
    {
        cout << "Queue is empty. Cannot dequeue passenger.\n";
        return false;
    }

    passengerName = arr[front];
    front = (front + 1) % capacity;
    count--;

    return true;
}

// ---------------------------------------------------------
// Peek
// ---------------------------------------------------------
string PassengerQueue::peek() const
{
    if (isEmpty())
    {
        cout << "Queue is empty. No passenger to peek.\n";
        return "";
    }

    return arr[front];
}

// ---------------------------------------------------------
// Size
// ---------------------------------------------------------
int PassengerQueue::size() const
{
    return count;
}

// ---------------------------------------------------------
// Print Queue
// ---------------------------------------------------------
void PassengerQueue::printQueue() const
{
    if (isEmpty())
    {
        cout << "Passenger Queue is empty.\n";
        return;
    }

    cout << "Passenger Queue: ";
    for (int i = 0; i < count; i++)
    {
        int index = (front + i) % capacity;
        cout << arr[index];

        if (i < count - 1)
            cout << " <- ";
    }
    cout << endl;
}
