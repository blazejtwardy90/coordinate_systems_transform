#pragma once
#include "coordinate_system.hpp"
#include "calculation_module.hpp"

constexpr int X_AXIS = 1;
constexpr int Y_AXIS = 2;
constexpr int Z_AXIS = 3;

class EquatorialRA :public coordinate_system
{
private:
    /* data */
    double _recAngle[3];
    double _decAngle[3];
    double _coordinatesRad[3];

    calculation_module _CalcModule;
public:
    EquatorialRA(/* args */);
    virtual ~EquatorialRA();
    virtual bool Init();
    virtual bool ToEquatorialRA() {return false;};
    virtual bool ToEquatorialHA();
    virtual bool ToHorizontal(std::vector<double> inputArg);
    virtual bool ToEcliptic();
    virtual bool ToGalactic();
};