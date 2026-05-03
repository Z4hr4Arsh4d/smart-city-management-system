#include "sectorList.h"

namespace Population{
    Sector::Sector(const string& sectorName): name(sectorName), next(nullptr), streetHead(nullptr) {}
};