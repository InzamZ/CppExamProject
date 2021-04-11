#pragma once

#include <iostream>
#include <string>

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
    unit myunit;
    title mytitle;
    //TODO:add the init value of salary
    const double salary[] {};
}

//TODO:finish class unit and kids class
class unit
{
protected:

}

//TODO:finish class title and kids class
class title
{
protected:

}