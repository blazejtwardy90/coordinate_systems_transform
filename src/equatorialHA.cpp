#include <stdio.h>
#include "equatorialHA.hpp"
#include <math.h>

EquatorialHA::EquatorialHA(/* args */)
{
}

EquatorialHA::~EquatorialHA()
{
}

bool EquatorialHA::Init()
{
    double hourDeclination[2];
    printf("Input hour angle (format: h min sec)\n");
	scanf("%lf %lf %lf", &_hourAngle[0], &_hourAngle[1], &_hourAngle[2]);

    hourDeclination[0] = _CalcModule.hour2rad(_hourAngle);

    if (_CalcModule.verifyInputPlaneAngle(hourDeclination[0]) == false)
    {
        return false;
    }

    printf("Input declination (format: st min sec)\n");
	scanf("%lf %lf %lf", &_decAngle[0], &_decAngle[1], &_decAngle[2]);

    hourDeclination[1] = _CalcModule.degree2rad(_decAngle);

    if (_CalcModule.verifyInputHeightAngle(hourDeclination[1]) == false)
    {
        return false;
    }

    _CalcModule.spher2vec(hourDeclination, _coordinatesRad);
    
    return true;
}

bool EquatorialHA::ToEquatorialRA() 
{   
    _CalcModule.passiveRotation(1, 2.0, _hourAngle);

    return true;    
}

bool EquatorialHA::ToHorizontal(std::vector<double> inputArg)
{
    double latitude[3];
    double latitudeRadValue = 0.0;
    double sphereMatrix[2];
    double outputAzimuthMatrix[3];
    double outputHeighthMatrix[3];

    try
    {
        printf("Input observer latitude (format st min sec)\n");
        scanf("%lf %lf %lf", &latitude[0], &latitude[1], &latitude[2]);
        latitudeRadValue = _CalcModule.degree2rad(latitude);
        _CalcModule.passiveRotation(Y_AXIS, M_PI/2, _coordinatesRad);
        _CalcModule.passiveRotation(Z_AXIS, -M_PI, _coordinatesRad);
        _CalcModule.vec2spher(_coordinatesRad, sphereMatrix );

        _CalcModule.rad2degree(sphereMatrix[0], outputAzimuthMatrix);
        _CalcModule.rad2degree(sphereMatrix[1], outputHeighthMatrix);

        printf("Azimuth:%.0f %.0f %.6f\n", outputAzimuthMatrix[0], outputAzimuthMatrix[1], outputAzimuthMatrix[2]);
		printf("Heighth: %.0f %.0f %.6f\n", outputHeighthMatrix[0], outputHeighthMatrix[1], outputHeighthMatrix[2]);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
    return true;
};