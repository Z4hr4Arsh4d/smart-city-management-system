#include "EducationModule.h"
#include <fstream>


void EducationModule::resizeSchoolList() {
    int newCap = schoolCapacity * 2;
    School** newList = new School * [newCap];

    for (int i = 0; i < schoolCount; i++)
        newList[i] = schools[i];

    delete[] schools;
    schools = newList;
    schoolCapacity = newCap;
}
// ==================== CLEAN STRING HELPER ====================
string cleanField(string s)
{
    // Trim spaces
    while (!s.empty() && (s[0] == ' ')) s.erase(0, 1);
    while (!s.empty() && (s.back() == ' ')) s.pop_back();

    // Trim surrounding quotes
    if (!s.empty() && s[0] == '"') s.erase(0, 1);
    if (!s.empty() && s.back() == '"') s.pop_back();

    return s;
}
// small helper: trim spaces and quotes from both ends
static string trimField(const string& s)
{
    int start = 0;
    int end = (int)s.size() - 1;

    while (start <= end &&
        (s[start] == ' ' || s[start] == '\t' || s[start] == '"'))
        start++;

    while (end >= start &&
        (s[end] == ' ' || s[end] == '\t' || s[end] == '"'))
        end--;

    if (start > end) return "";
    return s.substr(start, end - start + 1);
}

// --------------------------------------------------------------
// Constructor
// --------------------------------------------------------------
EducationModule::EducationModule() {
    schoolCapacity = 200;
    schoolCount = 0;
    schools = new School * [schoolCapacity];
    schoolGraph = nullptr;
}

// --------------------------------------------------------------
// Destructor
// --------------------------------------------------------------
EducationModule::~EducationModule() {
    for (int i = 0; i < schoolCount; i++)
        delete schools[i];
    delete[] schools;

    delete schoolGraph;
}

int EducationModule::getSchoolCount() const {
    return schoolCount;
}

School* EducationModule::getSchoolAt(int index) const {
    if (index < 0 || index >= schoolCount) return nullptr;
    return schools[index];
}

// --------------------------------------------------------------
// Load CSV
// --------------------------------------------------------------
void EducationModule::loadSchoolsFromCSV(const string& filename, Sector::Graph& sectorGraph)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Failed to open " << filename << "\n";
        return;
    }

    string line;

    if (!getline(file, line))
    {
        cout << "Empty CSV.\n";
        return;
    }

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        string id, name, sectorName, ratingStr, subjectsCell;
        string current;
        int col = 0;

        for (size_t i = 0; i < line.size(); ++i)
        {
            char ch = line[i];

            if (ch == ',' && col < 4)
            {
                string field = trimField(current);

                if (col == 0)      id = field;
                else if (col == 1) name = field;
                else if (col == 2) sectorName = field;
                else if (col == 3) ratingStr = field;

                current.clear();
                col++;
            }
            else
            {
                current += ch;
            }
        }

        subjectsCell = trimField(current);

        if(UTIL::isNumeric(id) || UTIL::isNumeric(name) || UTIL::isNumeric(sectorName))
            continue;

        if(!sectorGraph.searchSector(sectorName))
            continue;

        if(!UTIL::isNumeric(ratingStr))
            continue;

        if (id == "" || name == "" || sectorName == "" || ratingStr == "")
            continue;   

        float rating = static_cast<float>(atof(ratingStr.c_str()));

        School* s = new School(id, name, sectorName);
        s->setRating(rating);

        current.clear();
        for (size_t i = 0; i < subjectsCell.size(); ++i)
        {
            char ch = subjectsCell[i];
            if (ch == ',')
            {
                string sub = trimField(current);
                if(UTIL::isNumeric(sub))
                {
                    current.clear();
                    continue;
                }
                if (!sub.empty())
                    s->addSubject(sub);
                current.clear();
            }
            else
            {
                current += ch;
            }
        }

        {
            string sub = trimField(current);
            if(UTIL::isNumeric(sub))
            {
                current.clear();
                continue;
            }
            if (!sub.empty())
                s->addSubject(sub);
        }

        addSchool(s);
    }

    file.close();
}


// --------------------------------------------------------------
// Add School
// --------------------------------------------------------------
void EducationModule::addSchool(School* s) {
    if (schoolCount >= schoolCapacity)
        resizeSchoolList();
    schools[schoolCount++] = s;
}

// --------------------------------------------------------------
// Attach to Sector Graph
// --------------------------------------------------------------
void EducationModule::attachSchoolsToSectors(Sector::Graph& graph) {

    for (int i = 0; i < schoolCount; i++) {
        School* s = schools[i];

        graph.addFacility(
            s->getSector(),
            s->getId(),
            s->getName(),
            Facility::EDUCATION
        );
    }
}

// --------------------------------------------------------------
// Find School
// --------------------------------------------------------------
School* EducationModule::findSchoolByName(const string& name) {
    for (int i = 0; i < schoolCount; i++)
        if (schools[i]->getName() == name)
            return schools[i];
    return nullptr;
}

// --------------------------------------------------------------
// Faculty Register w/ Role
// --------------------------------------------------------------
void EducationModule::registerFacultyWithRole(const string& schoolName,
    const Faculty& f,
    const string& parentRole)
{
    School* s = findSchoolByName(schoolName);
    if (!s) {
        cout << "School not found.\n";
        return;
    }

    s->ensureOrganogram();

    if (!s->registerFacultyWithRole(f, parentRole)) {
        cout << "Failed to register faculty with role.\n";
        return;
    }

    cout << "Faculty and Role registered successfully.\n";
}

// --------------------------------------------------------------
// Search By Subject
// --------------------------------------------------------------
void EducationModule::searchBySubject(const string& subject)
{
    if (schoolCount == 0)
    {
        cout << "No schools loaded.\n";
        return;
    }

    // Convert search subject to lowercase for case-insensitive matching
    string target = subject;
    for (char& c : target) c = tolower(c);

    cout << "\nSchools offering '" << subject << "':\n\n";

    bool found = false;

    for (int i = 0; i < schoolCount; i++)
    {
        School* s = schools[i];

        // Check all subjects offered by this school
        for (int j = 0; j < s->getSubjectsCount(); j++)
        {
            string sub = s->getSubjectAt(j);

            // lowercase copy to compare
            string subLower = sub;
            for (char& c : subLower) c = tolower(c);

            if (subLower == target)
            {
                found = true;

                cout << "--------------------------------------------------\n";
                cout << "School: " << s->getName() << " (" << s->getSector() << ")\n";
                cout << "Rating: " << s->getRating() << "\n";

                cout << "Subjects Offered:\n";
                for (int k = 0; k < s->getSubjectsCount(); k++)
                {
                    cout << "   - " << s->getSubjectAt(k) << "\n";
                }
                cout << "--------------------------------------------------\n\n";

                break; // stop checking this school � we already printed it
            }
        }
    }

    if (!found)
        cout << "No schools offer this subject.\n\n";
}

// --------------------------------------------------------------
// Ranking
// --------------------------------------------------------------
void EducationModule::printSchoolRanking() {
    SchoolRankingQueue q(schoolCount);
    for (int i = 0; i < schoolCount; i++)
        q.insert(schools[i]);
    q.printRanking();
}

// --------------------------------------------------------------
// Print Organogram
// --------------------------------------------------------------
void EducationModule::printOrganogram(const string& name) {
    School* s = findSchoolByName(name);
    if (!s) {
        cout << "School not found.\n";
        return;
    }
    s->printOrganogram();
}

// --------------------------------------------------------------
// Build School Subgraph
// --------------------------------------------------------------
void EducationModule::buildSchoolGraph(Sector::Graph& graph)
{
    if (schoolGraph)
        delete schoolGraph;

    schoolGraph = graph.getSubgraph(Facility::EDUCATION);

    if (!schoolGraph)
        cout << "No schools found in Sector Graph.\n";
    else
        cout << "School SubGraph created successfully.\n";
}

// --------------------------------------------------------------
// Nearest School (global)
// --------------------------------------------------------------
School* EducationModule::nearestSchoolGlobal(const string& schoolName)
{
    if (!schoolGraph) {
        cout << "SchoolGraph not built.\n";
        return nullptr;
    }

    Facility::Vertex* startV = schoolGraph->getVertex(schoolName);
    if (!startV) {
        cout << "School not found in subgraph.\n";
        return nullptr;
    }

    string nearestName = "";
    int bestDist = 20000000;

    Facility::Vertex* v = schoolGraph->getHead();
    while (v)
    {
        if (v->name != schoolName)
        {
            string* path = nullptr;
            int pathLen = 0;
            int dist = -1;

            bool ok = schoolGraph->shortestPath(schoolName,
                v->name,
                path,
                pathLen,
                dist);

            if (ok && dist >= 0 && dist < bestDist)
            {
                bestDist = dist;
                nearestName = v->name;
            }

            delete[] path;
        }

        v = v->next;
    }

    if (nearestName == "")
        return nullptr;

    for (int i = 0; i < schoolCount; i++)
        if (schools[i]->getName() == nearestName)
            return schools[i];

    return nullptr;
}

// --------------------------------------------------------------
// Register Student
// --------------------------------------------------------------
void EducationModule::registerStudent(const string& schoolName,
    const Student& st)
{
    School* s = findSchoolByName(schoolName);
    if (!s) {
        cout << "School not found.\n";
        return;
    }

    if (s->registerStudent(st))
        cout << "Student registered successfully.\n";
    else
        cout << "Student already exists.\n";
}
