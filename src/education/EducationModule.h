#pragma once
#include <iostream>
#include <string>
using namespace std;

#include "School.h"
#include "SchoolRankingQueue.h"
#include "../../core/utility/utility.h"
#include "../../core/Sector.h"


class EducationModule {

private:
    School** schools;
    int schoolCount;
    int schoolCapacity;

    Facility::SubGraph* schoolGraph;

    void resizeSchoolList();

public:

    EducationModule();
    ~EducationModule();

    int getSchoolCount() const;

    School* getSchoolAt(int index) const;

    void loadSchoolsFromCSV(const string& filename, Sector::Graph& sectorGraph);

    void addSchool(School* s);

    void attachSchoolsToSectors(Sector::Graph& graph);

    School* findSchoolByName(const string& name);

    void registerFacultyWithRole(const string& schoolName,
        const Faculty& f,
        const string& parentRole);

    void searchBySubject(const string& subject);

    void printSchoolRanking();

    void printOrganogram(const string& name);

    void buildSchoolGraph(Sector::Graph& graph);

    School* nearestSchoolGlobal(const string& schoolName);

    void registerStudent(const string& schoolName,
        const Student& st);
	void debugPrintSubjects() const;
};
