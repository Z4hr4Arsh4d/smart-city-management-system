#include "TravelHistoryStack.h"

// ---------------------------------------------------
// Constructor
// ---------------------------------------------------
TravelHistoryStack::TravelHistoryStack(int cap)
{
    capacity = cap;
    arr = new string[capacity];
    top = -1;
}

// ---------------------------------------------------
// Destructor
// ---------------------------------------------------
TravelHistoryStack::~TravelHistoryStack()
{
    delete[] arr;
}

// ---------------------------------------------------
// Check full
// ---------------------------------------------------
bool TravelHistoryStack::isFull() const
{
    return top == capacity - 1;
}

// ---------------------------------------------------
// Check empty
// ---------------------------------------------------
bool TravelHistoryStack::isEmpty() const
{
    return top == -1;
}

// ---------------------------------------------------
// Push operation
// ---------------------------------------------------
bool TravelHistoryStack::push(const string& location)
{
    if (isFull())
    {
        cout << "Stack is full. Cannot push location: " << location << endl;
        return false;
    }
    arr[++top] = location;
    return true;
}

// ---------------------------------------------------
// Pop operation
// ---------------------------------------------------
bool TravelHistoryStack::pop(string& location)
{
    if (isEmpty())
    {
        cout << "Stack is empty. Cannot pop location.\n";
        return false;
    }
    location = arr[top--];
    return true;
}

// ---------------------------------------------------
// Peek
// ---------------------------------------------------
string TravelHistoryStack::peek() const
{
    if (isEmpty())
    {
        cout << "Stack is empty. No location to peek.\n";
        return "";
    }
    return arr[top];
}

// ---------------------------------------------------
// Print stack
// ---------------------------------------------------
void TravelHistoryStack::printHistory() const
{
    if (isEmpty())
    {
        cout << "Stack is empty.\n";
        return;
    }

    cout << "Travel History Stack (top to bottom):\n";
    for (int i = top; i >= 0; i--)
        cout << arr[i] << endl;
}

// ---------------------------------------------------
// Clear stack
// ---------------------------------------------------
void TravelHistoryStack::clear()
{
    top = -1;
}
