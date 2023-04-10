#include <stdio.h>
#include "equatorialHA.hpp"


EquatorialHA::EquatorialHA(/* args */)
{
    printf("Podaj rektascencje (format: h min sec)\n");
	scanf("%lf %lf %lf", &recAngle[0], &recAngle[1], &recAngle[2]);

    printf("Podaj deklinację (format: st min sec)\n");
	scanf("%lf %lf %lf", &decAngle[0], &decAngle[1], &decAngle[2]);
}

EquatorialHA::~EquatorialHA()
{
}

bool EquatorialHA::ToEquatorialRA() 
{   
    _CalculationModule.passiveRotation(1, 2.0, recAngle);

    return true;    
};