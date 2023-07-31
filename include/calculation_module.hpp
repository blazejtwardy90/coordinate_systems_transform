#pragma once

constexpr int X_AXIS = 1;
constexpr int Y_AXIS = 2;
constexpr int Z_AXIS = 3;

class calculation_module
{
private:
    /* data */
public:
    calculation_module(/* args */);
    ~calculation_module();

    void passiveRotation(int axis, double rotAngle, double* inputMatrix);
    void spher2vec(double* inputMatrix, double* outputMatrix);
    void vec2spher(double* inputMatrix, double* outputMatrix);
    double degree2rad(double* inputMatrix);
    double hour2rad(double* inputMatrix);
    void rad2degree(double inputRad, double* returnValue);
    void rad2hour(double inputRad, double* returnValue);
    void initiateMatrix(double* inputMatrix, const int matrixSize );

    bool verifyInputPlaneAngle(double& inputangle);
    bool verifyInputHeightAngle(double& inputangle);
};