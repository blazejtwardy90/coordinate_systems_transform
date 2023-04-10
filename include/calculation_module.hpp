#pragma once
class calculation_module
{
private:
    /* data */
public:
    calculation_module(/* args */);
    ~calculation_module();

    void passiveRotation(int axis, double rotAngle, double* inputMatrix);
    void spher2vec(double* inputMatrix);
    void vec2spher(double* inputMatrix);
    double degree2rad(double* inputMatrix);
    double hour2rad(double* inputMatrix);
    void rad2degree(double inputRad, double* returnValue);
    void rad2hour(double inputRad, double* returnValue);
};