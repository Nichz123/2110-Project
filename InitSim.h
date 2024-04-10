#include "City.h"
using namespace std;

#ifndef INITSIM_H
#define INITSIM_H

class InitSim
{
    public:
        int InputConfig(City& theCity);
        int InputRegionData(City& theCity);
    private:
        string regionLayout;
};

#endif