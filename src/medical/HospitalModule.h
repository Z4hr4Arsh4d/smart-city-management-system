#pragma once
#include <string>
#include <iostream>
using namespace std;

#include "BedsMaxHeap.h"
#include "Hospital.h"
#include "DoctorList.h"
#include "Patient.h"

#include "../../core/utility/utility.h"
#include "../../core/Sector.h"

class HospitalModule
{
private:
    Hospital** hospitals;
    int hospitalCount;
    int hospitalCapacity;

    Facility::SubGraph* hospitalGraph;
    BedsMaxHeap bedHeap;

    void resizeHospitalList();
    int stringToInt(const string& str) const;
    string cleanSpecializations(const string& specs) const;

public:
    HospitalModule();
    ~HospitalModule();

    int getHospitalCount() const;
    Hospital* getHospitalAt(int index) const;

    void loadHospitalsFromCSV(const string& filename, Sector::Graph& sectorGraph);
    void addHospital(Hospital* h);
    void attachHospitalsToSectors(Sector::Graph& graph);

    Hospital* findHospitalByName(const string& name);
    Hospital* findHospitalByName(const string& name) const;
    Hospital* findHospitalByID(const string& id);

    void registerDoctorToHospital(const string& hospitalName,
        const string& doctorID,
        const string& doctorName,
        const string& specialization);

    void addPatientToHospital(const string& hospitalName, const Patient& patient);

    void updateHospitalBeds(const string& hospitalName, int newBedCount);

    BedHeapElement getHospitalWithMostBeds() const;
    Hospital* getHospitalWithLeastBeds() const;

    void searchBySpecialization(const string& specialization);

    void buildHospitalGraph(Sector::Graph& graph);
    Hospital* findNearestHospital(const string& fromHospitalName);

    void displayAllHospitals() const;
    void displayHospitalDetails(const string& hospitalName) const;
    void displayEmergencyBedStatus() const;

    int getTotalBeds() const;
    int getAverageBeds() const;
};
