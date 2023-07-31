#pragma once
#include <vector>
#include "iostream"

class coordinate_system
{
private:
    /* data */
public:
    coordinate_system();
    virtual ~coordinate_system()= 0;
    virtual bool Init() = 0;
    virtual bool ToEquatorialRA() = 0;
    virtual bool ToEquatorialHA() = 0;  
    virtual bool ToHorizontal(std::vector<double> inputArg ) = 0; 
    virtual bool ToEcliptic() = 0;
    virtual bool ToGalactic() = 0;
};