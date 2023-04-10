#include <stdio.h>
#include "equatorialHA.hpp"


EquatorialHA::EquatorialHA(/* args */)
{
}

EquatorialHA::~EquatorialHA()
{
}

bool EquatorialHA::Init()
{
    printf("Input hour angle (format: h min sec)\n");
	scanf("%lf %lf %lf", &_hourAngle[0], &_hourAngle[1], &_hourAngle[2]);

    _coordinatesRad[0] = _CalcModule.hour2rad(_hourAngle);

    if (_CalcModule.verifyInputPlaneAngle(_coordinatesRad[0]) == false)
    {
        return false;
    }

    printf("Input declination (format: st min sec)\n");
	scanf("%lf %lf %lf", &_decAngle[0], &_decAngle[1], &_decAngle[2]);

     _coordinatesRad[1] = _CalcModule.degree2rad(_decAngle);
    if (_CalcModule.verifyInputHeightAngle(_coordinatesRad[1]) == false)
    {
        return false;
    }

    _CalcModule.spher2vec(_coordinatesRad);
    
    return true;
}

bool EquatorialHA::ToEquatorialRA() 
{   
    _CalcModule.passiveRotation(1, 2.0, _hourAngle);

    return true;    
};