#include "calculation_module.hpp"
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>


calculation_module::calculation_module(/* args */)
{
}

calculation_module::~calculation_module()
{
}

void calculation_module::passiveRotation(int axis, double rotAngle, double *inputMatrix)
{
    double M[3][3], work[3];
	double s, c;
	int i, j;
	for (i = 0; i <= 2; i++)
		work[i] = 0;

	s = sin(rotAngle);
	c = cos(rotAngle);

	if (axis == 1)
	{
		M[0][0] = 1;
		M[0][1] = 0;
		M[0][2] = 0;
		M[1][0] = 0;
		M[1][1] = c;
		M[1][2] = s;
		M[2][0] = 0;
		M[2][1] = -s;
		M[2][2] = c;
	}
	else if (axis == 2)
	{
		M[0][0] = c;
		M[0][1] = 0;
		M[0][2] = -s;
		M[1][0] = 0;
		M[1][1] = 1;
		M[1][2] = 0;
		M[2][0] = s;
		M[2][1] = 0;
		M[2][2] = c;
	}
	else if (axis == 3)
	{
		M[0][0] = c;
		M[0][1] = s;
		M[0][2] = 0;
		M[1][0] = -s;
		M[1][1] = c;
		M[1][2] = 0;
		M[2][0] = 0;
		M[2][1] = 0;
		M[2][2] = 1;
	}

	for (j = 0; j <= 2; j++)
		for (i = 0; i <= 2; i++)
			work[j] = work[j] + M[j][i] * inputMatrix[i];

	for (i = 0; i <= 2; i++)
		inputMatrix[i] = work[i];
}
