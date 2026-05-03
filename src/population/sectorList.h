#pragma once
#include "Street.h"

namespace Population{

    struct Sector
    {
        string name;
        Sector* next;
        Street* streetHead;

        Sector(const string& sectorName);
    };
};
