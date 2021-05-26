#pragma once
#include <iostream>
#include <string>
#include "title.h"
#include "unit.h"

class employee
{
protected:
    enum {HUMANRESOURCES = 0,  FINANCE, SALES, ADMINISTRATION};
    enum {MANAGER = 0,  FINANCE, SALES, ADMINISTRATION};
    std::string eid;
    std::string name;
    std::string gender;
    std::string dob;
    std::string doe;
    title _title;
};

