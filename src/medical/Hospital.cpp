#include "Hospital.h"

// ---------------- Constructor ----------------
Hospital::Hospital(string id, string n, string sec, int beds,
    string specs, int nodeIdx)
    : hospitalID(id), name(n), sector(sec), emergencyBeds(beds),
    specializations(specs), graphNodeIndex(nodeIdx),
    doctors(), patientQueue()
{
}

// ---------------- Getters ----------------
string Hospital::getHospitalID() const { return hospitalID; }
string Hospital::getName() const { return name; }
string Hospital::getSector() const { return sector; }
int Hospital::getEmergencyBeds() const { return emergencyBeds; }
string Hospital::getSpecializations() const { return specializations; }
int Hospital::getGraphNodeIndex() const { return graphNodeIndex; }

// ---------------- Bed Update ----------------
void Hospital::setEmergencyBeds(int beds)
{
    emergencyBeds = beds;
}

// ---------------- Doctor Operations ----------------
void Hospital::addDoctor(const Doctor& doc)
{
    doctors.addDoctor(doc);
}

bool Hospital::removeDoctorByID(const string& docID)
{
    return doctors.removeDoctorByID(docID);
}

bool Hospital::getDoctorByID(const string& docID, Doctor& out) const
{
    return doctors.getDoctorByID(docID, out);
}

bool Hospital::getDoctorByName(const string& name, Doctor& out) const
{
    return doctors.getDoctorByName(name, out);
}

void Hospital::displayDoctors() const
{
    cout << "\n=== Hospital: " << name << " (" << sector << ") ===\n";
    cout << "Specializations: " << specializations << "\n";
    cout << "Emergency Beds: " << emergencyBeds << "\n";
    doctors.display();
}

bool Hospital::hasDoctor(const string& docID) const
{
    return doctors.containsDoctorID(docID);
}

// ---------------- Patient Operations ----------------
void Hospital::addPatient(const Patient& p)
{
    patientQueue.insert(p);
}

bool Hospital::extractNextPatient(Patient& out)
{
    return patientQueue.extractMin(out);
}

bool Hospital::peekNextPatient(Patient& out) const
{
    return patientQueue.peek(out);
}

bool Hospital::updatePatientPriority(const string& patientName, int newPriority)
{
    return patientQueue.updatePatientPriority(patientName, newPriority);
}

bool Hospital::hasPatient(const string& patientName) const
{
    return patientQueue.containsPatient(patientName);
}

void Hospital::displayPatients() const
{
    cout << "\n=== Patients Queue for Hospital: " << name << " ===\n";
    patientQueue.display();
}

int Hospital::getPatientCount() const
{
    return patientQueue.getSize();
}
