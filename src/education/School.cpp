#include "School.h"

// ------------------------------------------------------------
// Constructors
// ------------------------------------------------------------
School::School()
{
    id = "";
    name = "";
    sector = "";
    subjects = new string[100];
    subjectsCount = 0;

    rating = 0;
    organogramRoot = nullptr;

    facultyTable = new FacultyHashTable();
    studentTable = new StudentHashTable();
}

School::School(string id, string name, string sector)
{
    this->id = id;
    this->name = name;
    this->sector = sector;

    subjects = new string[100];
    subjectsCount = 0;

    rating = 0;
    organogramRoot = nullptr;

    facultyTable = new FacultyHashTable();
    studentTable = new StudentHashTable();
}

// ------------------------------------------------------------
// Destructor
// ------------------------------------------------------------
School::~School()
{
    delete[] subjects;
    delete facultyTable;
    delete studentTable;

    freeOrgTree(organogramRoot);
}

// ------------------------------------------------------------
// Getters / Setters
// ------------------------------------------------------------
void School::setId(string x) { id = x; }
string School::getId() { return id; }

void School::setName(string n) { name = n; }
string School::getName() { return name; }

void School::setSector(string s) { sector = s; }
string School::getSector() { return sector; }

void School::setRating(float r) { rating = r; }
float School::getRating() { return rating; }

// ------------------------------------------------------------
// Subjects
// ------------------------------------------------------------
void School::addSubject(string sub)
{
    subjects[subjectsCount++] = sub;
}

bool School::offersSubject(string sub)
{
    for (int i = 0; i < subjectsCount; i++)
        if (subjects[i] == sub)
            return true;

    return false;
}

// ------------------------------------------------------------
// Faculty
// ------------------------------------------------------------
bool School::registerFaculty(Faculty f)
{
    return facultyTable->insertFaculty(f);
}

Faculty* School::findFaculty(string id)
{
    return facultyTable->searchFaculty(id);
}

void School::removeFaculty(string id)
{
    facultyTable->deleteFaculty(id);
}

bool School::registerFacultyWithRole(const Faculty& f, const string& parentRole)
{
    if (!registerFaculty(f)) return false;

    ensureOrganogram();

    if (!addRoleToNode(organogramRoot, parentRole, f.getRole()))
        return false;

    return assignFacultyToRole(f.getRole(), f.getId());
}

bool School::assignFacultyToRole(const string& roleName, const string& facultyId)
{
    if (!organogramRoot) return false;
    return ::assignFacultyToRole(organogramRoot, roleName, facultyId);
}

// ------------------------------------------------------------
// Students
// ------------------------------------------------------------
bool School::registerStudent(const Student& s)
{
    return studentTable->insertStudent(s);
}

Student* School::findStudent(string roll)
{
    return studentTable->searchStudent(roll);
}

void School::removeStudent(string roll)
{
    studentTable->deleteStudent(roll);
}

// ------------------------------------------------------------
// Organogram
// ------------------------------------------------------------
void School::initOrganogram()
{
    if (!organogramRoot)
        organogramRoot = new OrgNode("Principal");
}

void School::addRole(string parentRole, string newRole)
{
    if (!organogramRoot)
    {
        cout << "Organogram not initialized!\n";
        return;
    }

    if (!addRoleToNode(organogramRoot, parentRole, newRole))
        cout << "Parent role not found\n";
}

OrgNode* School::getOrganogramRoot()
{
    return organogramRoot;
}

void School::ensureOrganogram()
{
    if (!organogramRoot)
        organogramRoot = new OrgNode("Principal");
}

void School::printOrganogram()
{
    if (!organogramRoot)
    {
        cout << "Organogram not initialized\n";
        return;
    }
    printOrgDFS(organogramRoot);
}

// ------------------------------------------------------------
// Faculty Reporting
// ------------------------------------------------------------
void School::printFacultyWithAndWithoutRoles()
{
    string usedIds[500];
    int usedCount = 0;

    collectRoleFacultyIds(organogramRoot, usedIds, usedCount);

    cout << "\n--- Faculty WITH Roles ---\n";

    FacultyNode** table = facultyTable->getTable();
    int size = facultyTable->getSize();

    for (int i = 0; i < size; i++)
    {
        FacultyNode* curr = table[i];
        while (curr != nullptr)
        {
            bool hasRole = false;
            for (int j = 0; j < usedCount; j++)
                if (usedIds[j] == curr->data.getId())
                    hasRole = true;

            if (hasRole)
            {
                cout << curr->data.getName()
                    << " (" << curr->data.getId()
                    << ") | Role: " << curr->data.getRole() << endl;
            }
            curr = curr->next;
        }
    }

    cout << "\n--- Faculty WITHOUT Roles ---\n";

    for (int i = 0; i < size; i++)
    {
        FacultyNode* curr = table[i];
        while (curr != nullptr)
        {
            bool hasRole = false;
            for (int j = 0; j < usedCount; j++)
                if (usedIds[j] == curr->data.getId())
                    hasRole = true;

            if (!hasRole)
                cout << curr->data.getName() << " (" << curr->data.getId() << ")\n";

            curr = curr->next;
        }
    }
}

int School::getSubjectsCount() const { return subjectsCount; }

string School::getSubjectAt(int index) const
{
    if (index >= 0 && index < subjectsCount)
        return subjects[index];
    return "";
}

void School::collectRoleFacultyIds(OrgNode* root, string* ids, int& count)
{
    if (!root) return;

    if (root->facultyId != "")
        ids[count++] = root->facultyId;

    collectRoleFacultyIds(root->firstChild, ids, count);
    collectRoleFacultyIds(root->nextSibling, ids, count);
}
