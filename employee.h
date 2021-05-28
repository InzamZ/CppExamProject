#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include "algorithm.h"
#include "title.h"

class employee
{
public:
    using pointer = employee*;
    using reference = employee&;
    using STR = std::string ;
    // enum {MANAGER = 0,  FINANCE, SALES, ADMINISTRATION};

protected:
    std::string eid;
    std::string name;
    std::string gender;
    std::string dob;
    std::string doe;
    std::string unit;
    title::pointer _title;
    void infor (std::ostream &os) const
    {
        os << '|' << std::setw(15) << eid << '|' << std::setw(15) << name << '|' << std::setw(10) << gender << '|' << std::setw(14) << dob << '|' << std::setw(14) << doe << '|' << std::setw(35) << unit << '|' << std::setw(30) << _title->titlename << '|' << std::setw(10) << _title->salary << '|' << std::endl;
    }
    void infor_file (std::ostream &os) const
    {
        os << eid << ' '  << name << ' ' << gender << ' ' <<  dob << ' ' <<  doe << ' ' <<  unit << ' ' <<  _title->titlename << ' ' << _title->salary  << std::endl;
    }

public:
    employee(STR _eid, STR _name, STR _gender, STR _dob, STR _doe, STR _unit, title::pointer __title)
        : eid(_eid), name(_name), gender(_gender), dob(_dob), doe(_doe), unit(_unit), _title(__title) {}

    ~employee() {}

    bool equal_eid(std::string _eid)
    {
        return _eid == eid;
    }

    static bool cmp( const pointer C, const pointer D )
    {
        if (C->eid.length() < D->eid.length())
            return true;
        if (D->eid.length() < C->eid.length())
            return false;
        return C->eid < D->eid;
    }

    bool cmp_title(std::string _titlename)
    {
        return _titlename == _title->titlename;
    }

    friend std::ostream &operator<<( std::ostream &os, const employee D )
    {
        D.infor_file(os);
        return os;
    }

    friend std::ostream &operator<<( std::ostream &os, const pointer D )
    {
        D->infor(os);
        return os;
    }

    bool operator<( const employee D )
    {
        if (D.eid.length() > eid.length())
            return true;
        if (D.eid.length() < eid.length())
            return false;
        return eid < D.eid;
    }

    friend class sys;
};

