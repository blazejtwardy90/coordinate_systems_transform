#pragma once

#include "coordinate_system.hpp"
#include "calculation_module.hpp"

class EquatorialHA :public coordinate_system
{
private:
    /* data */
    double recAngle[3];
    double decAngle[3];
    calculation_module _CalculationModule;

public:
    EquatorialHA(/* args */);
    ~EquatorialHA();
    virtual bool ToEquatorialRA();
    virtual bool ToEquatorialHA() {return false;};
    virtual bool ToSystemC() {return true;};
    virtual bool ToSystemD() {return true;};
    virtual bool ToSystemE() {return true;};
};