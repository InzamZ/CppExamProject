#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include "title.h"

class employee
{
public:
    using pointer = employee*;
    using reference = employee&;
    using STR = std::string ;
    // enum {HUMANRESOURCES = 0,  FINANCE, SALES, ADMINISTRATION};
    // enum {MANAGER = 0,  FINANCE, SALES, ADMINISTRATION};

protected:
    std::string eid;
    std::string name;
    std::string gender;
    std::string dob;
    std::string doe;
    std::string unit;
    title::pointer _title;

public:
    employee(STR _eid, STR _name, STR _gender, STR _dob, STR _doe, STR _unit, title::pointer __title)
        : eid(_eid), name(_name), gender(_gender), dob(_dob), doe(_doe), unit(_unit), _title(__title) {}

    void infor()
    {
        std::cout << std::setw(15) << eid << std::setw(15) << name << std::setw(15) << gender << std::setw(15) << dob << std::setw(15) << doe << std::setw(30) << unit << std::setw(30) << _title->titlename << std::setw(15) << _title->salary << std::endl;
    }
};

