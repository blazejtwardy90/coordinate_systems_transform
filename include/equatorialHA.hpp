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
    virtual bool ToHorizontal() {return true;};
    virtual bool ToSystemD() {return true;};
    virtual bool ToSystemE() {return true;};
};