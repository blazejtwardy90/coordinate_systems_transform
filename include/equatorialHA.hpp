#pragma once

#include "coordinate_system.hpp"
#include "calculation_module.hpp"

class EquatorialHA :public coordinate_system
{
private:
    /* data */
    double _hourAngle[3];
    double _decAngle[3];
    double _coordinatesRad[3];
    calculation_module _CalcModule;

public:
    EquatorialHA(/* args */);
    ~EquatorialHA();
    bool Init();
    virtual bool ToEquatorialRA();
    virtual bool ToEquatorialHA() {return false;};
    virtual bool ToHorizontal(std::vector<double> inputArg);
    virtual bool ToEcliptic() {return true;};
    virtual bool ToGalactic() {return true;};
};