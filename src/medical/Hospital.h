#pragma once
#include <string>
#include <iostream>
using namespace std;

#include "Doctor.h"
#include "DoctorList.h"
#include "Patient.h"
#include "PatientMinHeap.h"

class Hospital
{
private:
    string hospitalID;
    string name;
    string sector;
    int emergencyBeds;
    string specializations;
    int graphNodeIndex;

    DoctorList doctors;
    PatientMinHeap patientQueue;

public:
    Hospital(string id = "", string n = "", string sec = "", int beds = 0,
        string specs = "", int nodeIdx = -1);

    // Getters
    string getHospitalID() const;
    string getName() const;
    string getSector() const;
    int getEmergencyBeds() const;
    string getSpecializations() const;
    int getGraphNodeIndex() const;

    // Update bed count
    void setEmergencyBeds(int beds);

    // Doctor operations
    void addDoctor(const Doctor& doc);
    bool removeDoctorByID(const string& docID);
    bool getDoctorByID(const string& docID, Doctor& out) const;
    bool getDoctorByName(const string& name, Doctor& out) const;
    void displayDoctors() const;
    bool hasDoctor(const string& docID) const;

    // Patient operations
    void addPatient(const Patient& p);
    bool extractNextPatient(Patient& out);
    bool peekNextPatient(Patient& out) const;
    bool updatePatientPriority(const string& patientName, int newPriority);
    bool hasPatient(const string& patientName) const;
    void displayPatients() const;

    int getPatientCount() const;
};
