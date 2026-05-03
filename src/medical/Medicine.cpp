#include "Medicine.h"

// ---------------- Constructor ----------------
Medicine::Medicine(string name, string form, double p)
    : medicineName(name), formula(form), price(p)
{
}

// ---------------- Getter ----------------
string Medicine::getMedicineName() const
{
    return medicineName;
}

// ---------------- Operator Overload ----------------
ostream& operator<<(ostream& os, const Medicine& med)
{
    os << "Name:" << med.medicineName
        << " | Formula:" << med.formula
        << " | Price:" << med.price;

    return os;
}
