#include <stdio.h>
#include "equatorialRA.hpp"
#include <math.h>

EquatorialRA::EquatorialRA(/* args */)
{
    for (int index = 0; index < 3; index++)
    {
        _recAngle[index] = 0;
        _decAngle[index] = 0;
        _coordinatesRad[index] = 0;
    }
}

EquatorialRA::~EquatorialRA()
{
}

bool EquatorialRA::Init()
{
    double rightAscDeclination[2];

    printf("Input right ascension (format: h min sec)\n");
	scanf("%lf %lf %lf", &_recAngle[0], &_recAngle[1], &_recAngle[2]);

    rightAscDeclination[0] = _CalcModule.hour2rad(_recAngle);

    if (_CalcModule.verifyInputPlaneAngle(rightAscDeclination[0]) == false)
    {
        return false;
    }

    printf("Input declination (format: st min sec)\n");
	scanf("%lf %lf %lf", &_decAngle[0], &_decAngle[1], &_decAngle[2]);

    rightAscDeclination[1] = _CalcModule.degree2rad(_decAngle);

    if (_CalcModule.verifyInputHeightAngle(rightAscDeclination[1]) == false)
    {
        return false;
    }

    _CalcModule.spher2vec(rightAscDeclination, _coordinatesRad);

    return true;
}

bool EquatorialRA::ToEquatorialHA()
{
    double siderealTime[3];
    double timeRad = 0.0;
    double hourAngleReturn[3];
    double declinationReturn[3];
    double sphereCoord[2];

    printf("Input local sidereal time (format: h min sec)\n");
	scanf("%lf %lf %lf", &siderealTime[0], &siderealTime[1], &siderealTime[2]);
	timeRad = _CalcModule.hour2rad(siderealTime);
    
	if (_CalcModule.verifyInputPlaneAngle(timeRad) == false)
	{
		return false;
	}
	_CalcModule.passiveRotation(Z_AXIS, timeRad, _coordinatesRad);
	_coordinatesRad[1] = -_coordinatesRad[1];
    _CalcModule.vec2spher(_coordinatesRad, sphereCoord);
    _CalcModule.rad2hour(sphereCoord[0], hourAngleReturn);
    _CalcModule.rad2degree(sphereCoord[1], declinationReturn);

	printf("Hour Angle: %.0f %.0f %.6f\n", hourAngleReturn[0], hourAngleReturn[1], hourAngleReturn[2]);
	printf("Declination: %.0f %.0f %.6f\n", declinationReturn[0], declinationReturn[1], declinationReturn[2]);

    return true;
}

bool EquatorialRA::ToHorizontal(std::vector<double> inputArg)
{
    double siderealTime[3];
    double timeRad = 0.0;
    double azimutReturn[3];
    double heightReturn[3];
    double latitude[3];
    double latitudeRad = 0.0;
    double sphereCoord[2];

    printf("Input local sidereal time (format: h min sec)\n");
	scanf("%lf %lf %lf", &siderealTime[0], &siderealTime[1], &siderealTime[2]);
	timeRad = _CalcModule.hour2rad(siderealTime);
    
	if (_CalcModule.verifyInputPlaneAngle(timeRad) == false)
	{
		return false;
	}
    _CalcModule.passiveRotation(Z_AXIS, timeRad, _coordinatesRad);
	_coordinatesRad[1] = -_coordinatesRad[1];
    printf("Input observer latitude (format st min sec)\n");
	scanf("%lf %lf %lf", &latitude[0], &latitude[1], &latitude[2]);
    
    latitudeRad = _CalcModule.degree2rad(latitude);
    _CalcModule.passiveRotation(Y_AXIS, M_PI / 2 - latitudeRad, _coordinatesRad);
    _CalcModule.passiveRotation(Z_AXIS, -M_PI, _coordinatesRad);
    _CalcModule.vec2spher(_coordinatesRad, sphereCoord);
    _CalcModule.rad2degree(sphereCoord[0], azimutReturn);
    _CalcModule.rad2degree(sphereCoord[1], heightReturn);

    printf("Azimuth: %.0f %.0f %.6f\n", azimutReturn[0], azimutReturn[1], azimutReturn[2]);
    printf("Height: %.0f %.0f %.6f\n", heightReturn[0], heightReturn[1], heightReturn[2]);

    return true;
}

bool EquatorialRA::ToEcliptic()
{
    double eclipticIncl[3];
    double eclipticLongitude[3];
    double eclipticLatitude[3];
    double sphereCoord[2];
    double eclipticInclRad = 0.0;
    
    eclipticIncl[0] = 0;
    eclipticIncl[1] = 26;
	eclipticIncl[2] = 21.448;
	
    eclipticInclRad = _CalcModule.degree2rad(eclipticIncl);

    _CalcModule.passiveRotation(X_AXIS, eclipticInclRad, _coordinatesRad);
    _CalcModule.vec2spher(_coordinatesRad, sphereCoord);

    _CalcModule.rad2degree(sphereCoord[0], eclipticLongitude);
    _CalcModule.rad2degree(sphereCoord[1], eclipticLatitude);

    printf("Ecliptic longitude: %.0f %.0f %.6f\n", eclipticLongitude[0], eclipticLongitude[1], eclipticLongitude[2]);
	printf("Ecliptic latitude: %.0f %.0f %.6f\n", eclipticLatitude[0], eclipticLatitude[1], eclipticLatitude[2]);

    return true;
}

bool EquatorialRA::ToGalactic()
{
    double RAForGalactic[3];
    double RAForGalacticRadValue = 0.0;

    double DecForGalactic[3];
    double DecForGalacticRadValue = 0.0;

    double eclipticIncl[3];
    double eclipticInclRad = 0.0;

    double sphereCoordinates[2];
    double galacticLongitude[3];
    double galacticLatitude[3];
    
    for (int index = 0; index < 3; index++)
    {
        galacticLatitude[index] = 0;
        galacticLongitude[index] = 0;
    }
    
    double theta = 122.93191857 * M_PI / 180.0;

    eclipticIncl[0] = 0;
    eclipticIncl[1] = 26;
	eclipticIncl[2] = 21.448;
	

    RAForGalactic[0] = 12;
	RAForGalactic[1] = 51;
	RAForGalactic[2] = 26.27549;
    
    DecForGalactic[0] = 27; 
    DecForGalactic[1] = 7;
    DecForGalactic[2] = 42.7048;

    RAForGalacticRadValue = _CalcModule.hour2rad(RAForGalactic);
    DecForGalacticRadValue = _CalcModule.degree2rad(DecForGalactic);
    eclipticInclRad = _CalcModule.degree2rad(eclipticIncl);

    _CalcModule.passiveRotation(Z_AXIS, M_PI/2 + RAForGalacticRadValue, _coordinatesRad);
    _CalcModule.passiveRotation(X_AXIS, M_PI/2 - DecForGalacticRadValue, _coordinatesRad);
    _CalcModule.passiveRotation(Z_AXIS, M_PI/2 - theta, _coordinatesRad);

    _CalcModule.vec2spher(_coordinatesRad, sphereCoordinates);
    _CalcModule.rad2degree(sphereCoordinates[0], galacticLongitude);
    _CalcModule.rad2degree(sphereCoordinates[1], galacticLatitude);

    printf("Galactic longitude: %.0f %.0f %.6f\n", galacticLongitude[0], galacticLongitude[1], galacticLongitude[2]);
	printf("Galactic latitude: %.0f %.0f %.6f\n", galacticLatitude[0], galacticLatitude[1], galacticLatitude[2]);
    
    return true;
}
