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

	for (int iIndex = 0; iIndex <= 2; iIndex++)
	{
		work[iIndex] = 0;
	}

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

	for (int jIndex = 0; jIndex <= 2; jIndex++)
	{
		for (int iIndex = 0; iIndex <= 2; iIndex++)
		{
			work[jIndex] = work[jIndex] + M[jIndex][iIndex] * inputMatrix[iIndex];
		}
	}

	for (int iIndex = 0; iIndex <= 2; iIndex++)
	{
		inputMatrix[iIndex] = work[iIndex];
	}
}

void calculation_module::spher2vec(double* inputMatrix)
{
	double returnMatrix[3], s1, c1, s2, c2;

	s1 = sin(inputMatrix[0]);
	c1 = cos(inputMatrix[0]);
	s2 = sin(inputMatrix[1]);
	c2 = cos(inputMatrix[1]);
	returnMatrix[0] = c1 * c2;
	returnMatrix[1] = s1 * c2;
	returnMatrix[2] = s2;

	for (int index = 0; index <= 2; index++)
	{
		inputMatrix[index] = returnMatrix[index];
	}
}

void calculation_module::vec2spher(double *inputMatrix)
{
	double work[2];
	work[1] = asin(inputMatrix[2]);
	work[0] = atan2(inputMatrix[1], inputMatrix[0]);

	if (work[0] < 0)
	{
		work[0] = work[0] + 2 * M_PI;
	}
	for ( int index = 0; index <= 1; index++)
	{
		inputMatrix[index] = work[index];
	}
}

double calculation_module::degree2rad(double *inputMatrix)
{
	double returnValue;

	if (1.0 / inputMatrix[0] < 0)
	{
		inputMatrix[1] = -inputMatrix[1];
		inputMatrix[2] = -inputMatrix[2];
	}

	returnValue = (inputMatrix[0] + inputMatrix[1] / 60.0 + inputMatrix[2] / 3600.0) * M_PI / 180.0;

	return returnValue;
}

double calculation_module::hour2rad(double *inputMatrix)
{
    double returnValue;
	if (1.0 / inputMatrix[0] < 0)
	{
		inputMatrix[1] = -inputMatrix[1];
		inputMatrix[2] = -inputMatrix[2];
	}
	returnValue = (inputMatrix[0] + inputMatrix[1] / 60 + inputMatrix[2] / 3600) * M_PI / 12.0;
	return returnValue;
}

void calculation_module::rad2degree(double inputRad, double *returnValue)
{
	double work[3], minutes, seconds;
	inputRad = inputRad * 180.0 / M_PI;
	if (inputRad >= 0)
	{
		work[0] = floor(inputRad);
		minutes = (inputRad - work[0]) * 60;
		work[1] = floor(minutes);
		seconds = minutes - work[1];
		work[2] = seconds * 60;
	}
	else
	{
		inputRad = -inputRad;
		work[0] = floor(inputRad);
		minutes = (inputRad - work[0]) * 60;
		work[1] = floor(minutes);
		seconds = minutes - work[1];
		work[2] = seconds * 60;
		work[0] = -work[0];
	}

	if (work[2] >= 59.9999995)
	{
		work[2] = 0.0;
		work[1] = work[1] + 1;
	}

	if (work[1] == 60)
	{
		work[1] = 0.0;
		work[0] = work[0] + 1;
	}

	for (int index = 0; index <= 2; index++)
		returnValue[index] = work[index];
}

void calculation_module::rad2hour(double inputRad, double *returnValue)
{
	double work[3], minutes, seconds;
	int i;
	inputRad = inputRad * 12.0 / M_PI;
	if (inputRad >= 0)
	{
		work[0] = floor(inputRad);
		minutes = (inputRad - work[0]) * 60;
		work[1] = floor(minutes);
		seconds = minutes - work[1];
		work[2] = seconds * 60;
	}
	else
	{
		inputRad = -inputRad;
		work[0] = floor(inputRad);
		minutes = (inputRad - work[0]) * 60;
		work[1] = floor(minutes);
		seconds = minutes - work[1];
		work[2] = seconds * 60;
		work[0] = -work[0] + 12;
	}

	if (work[2] >= 59.9999995)
	{
		work[2] = 0.0;
		work[1] = work[1] + 1;
	}

	if (work[1] == 60)
	{
		work[1] = 0.0;
		work[0] = work[0] + 1;
	}

	for (i = 0; i <= 2; i++)
		returnValue[i] = work[i];
}
