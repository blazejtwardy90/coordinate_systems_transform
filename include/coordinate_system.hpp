#pragma once

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
    virtual bool ToHorizontal() = 0;
    virtual bool ToEcliptic() = 0;
    virtual bool ToSystemE() = 0;
};