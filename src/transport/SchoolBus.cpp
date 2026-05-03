#include "SchoolBus.h"

// --------------------------------------------------------
// Constructor
// --------------------------------------------------------
SchoolBus::SchoolBus(const string& no, School* s)
    : Bus(no, (s ? s->getName() : "UnknownSchool")),
    schoolPtr(s),
    studentCount(0),
    studentCapacity(50),
    emergencyMode(false),
    maxCapacity(50)
{
    studentList = new string[studentCapacity];
    schoolBus = true;  // inherited flag
}

// --------------------------------------------------------
// Destructor
// --------------------------------------------------------
SchoolBus::~SchoolBus()
{
    delete[] studentList;
}

// --------------------------------------------------------
// Resize student list
// --------------------------------------------------------
void SchoolBus::resizeStudentList()
{
    int newCap = studentCapacity * 2;
    string* newArr = new string[newCap];

    for (int i = 0; i < studentCount; i++)
        newArr[i] = studentList[i];

    delete[] studentList;
    studentList = newArr;
    studentCapacity = newCap;
}

// --------------------------------------------------------
// Set / Get school
// --------------------------------------------------------
void SchoolBus::setSchool(School* s)
{
    schoolPtr = s;
    if (s)
        company = s->getName();
}

School* SchoolBus::getSchool() const
{
    return schoolPtr;
}

// --------------------------------------------------------
// Assign student
// --------------------------------------------------------
bool SchoolBus::assignStudent(const Student& st)
{
    if (studentCount >= maxCapacity)
    {
        cout << "SchoolBus is full! Cannot assign student "
            << st.getRollNumber() << endl;
        return false;
    }

    if (studentCount >= studentCapacity)
        resizeStudentList();

    studentList[studentCount++] = st.getRollNumber();
    return true;
}

// --------------------------------------------------------
// Check student assignment
// --------------------------------------------------------
bool SchoolBus::isStudentAssigned(const string& rollNo)
{
    for (int i = 0; i < studentCount; i++)
        if (studentList[i] == rollNo)
            return true;

    return false;
}

// --------------------------------------------------------
// Emergency mode
// --------------------------------------------------------
void SchoolBus::activateEmergencyMode()
{
    emergencyMode = true;
    cout << "** EMERGENCY MODE ENABLED for SchoolBus " << busNo << " **\n";
}

void SchoolBus::disableEmergencyMode()
{
    emergencyMode = false;
    cout << "** Emergency mode disabled for SchoolBus " << busNo << " **\n";
}

bool SchoolBus::isInEmergencyMode() const
{
    return emergencyMode;
}

// --------------------------------------------------------
// Movement override
// --------------------------------------------------------
void SchoolBus::moveToNextStop()
{
    if (emergencyMode)
    {
        cout << "SchoolBus " << busNo
            << " is in EMERGENCY MODE. Normal movement paused.\n";
        return;
    }

    Bus::moveToNextStop();
}

// --------------------------------------------------------
// Print students
// --------------------------------------------------------
void SchoolBus::printAssignedStudents() const
{
    cout << "\n=== Students Assigned to SchoolBus " << busNo << " ===\n";

    if (studentCount == 0)
    {
        cout << "No students assigned.\n";
        return;
    }

    for (int i = 0; i < studentCount; i++)
        cout << i + 1 << ". " << studentList[i] << endl;

    cout << "-------------------------------------\n";
}

// --------------------------------------------------------
// Display override
// --------------------------------------------------------
void SchoolBus::displayInfo() const
{
    cout << "\n==============================\n";
    cout << "          SCHOOL BUS\n";
    cout << "==============================\n";

    cout << "Bus No         : " << busNo << endl;

    if (schoolPtr)
        cout << "School         : " << schoolPtr->getName() << endl;
    else
        cout << "School         : (NOT LINKED)\n";

    cout << "Max Capacity   : " << maxCapacity << endl;
    cout << "Assigned       : " << studentCount << " students\n";
    cout << "Emergency Mode : " << (emergencyMode ? "ACTIVE" : "OFF") << endl;

    if (currentStop)
        cout << "Current Stop   : " << currentStop->getName() << endl;
    else
        cout << "Current Stop   : (not assigned)\n";

    cout << "Route          : ";
    route.printRoute();

    cout << "=================================\n";
}

void SchoolBus::autoLoadStudents()
{
    int num = rand() % 7;   

    for (int i = 0; i < num; i++)
    {
        string name = "Student" + to_string(i + 1);
        passengers.enqueue(name);
    }

    studentCount = num;
}
