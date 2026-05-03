#pragma once
#include "House.h"

namespace Population{

    struct Street
    {
        string name;
        Street* next;

        House* houseHead;

        Street(const string& streetName);
    };
}