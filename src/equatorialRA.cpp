#include <stdio.h>
#include "equatorialRA.hpp"

EquatorialRA::EquatorialRA(/* args */)
{
}

EquatorialRA::~EquatorialRA()
{
}

bool EquatorialRA::Init()
{
    printf("Input right ascension (format: h min sec)\n");
	scanf("%lf %lf %lf", &_recAngle[0], &_recAngle[1], &_recAngle[2]);

    _coordinatesRad[0] = _CalcModule.hour2rad(_recAngle);

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

bool EquatorialRA::ToEquatorialHA()
{
    double siderealTime[3];
    double timeRad = 0.0;
    double hourAngleReturn[3];
    double declinationReturn[3];

    printf("Input local sidereal time (format: h min sec)\n");
	scanf("%lf %lf %lf", &siderealTime[0], &siderealTime[1], &siderealTime[2]);
	timeRad = _CalcModule.hour2rad(siderealTime);
    
	if (_CalcModule.verifyInputPlaneAngle(timeRad) == false)
	{
		return false;
	}
	_CalcModule.passiveRotation(Z_AXIS, timeRad, _coordinatesRad);
	_coordinatesRad[1] = -_coordinatesRad[1];
    _CalcModule.vec2spher(_coordinatesRad);
    _CalcModule.rad2hour(_coordinatesRad[0], hourAngleReturn);
    _CalcModule.rad2degree(_coordinatesRad[1], declinationReturn);

	printf("Hour Angle: %.0f %.0f %.6f\n", hourAngleReturn[0], hourAngleReturn[1], hourAngleReturn[2]);
	printf("Declination: %.0f %.0f %.6f\n", declinationReturn[0], declinationReturn[1], declinationReturn[2]);
    
    return true;
}
