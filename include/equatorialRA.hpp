#pragma once
#include "coordinate_system.hpp"
#include "calculation_module.hpp"

class EquatorialRA :public coordinate_system
{
private:
    /* data */
public:
    EquatorialRA(/* args */);
    ~EquatorialRA();
    virtual bool ToEquatorialRA() {return false;};
    virtual bool ToEquatorialHA() {return true;};
    virtual bool ToSystemC() {return true;};
    virtual bool ToSystemD() {return true;};
    virtual bool ToSystemE() {return true;};
};