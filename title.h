#pragma once
#include <iostream>
#include <string>

class title
{
public:
    using value_t = int;
    using pointer = title*;
    using refference = title&;
    friend class employee;
protected:
    std::string titlename;
    value_t salary;
public:
    title (std::string str = "Unknown", value_t sal = 0 ) : titlename(str), salary(sal) {}
    virtual ~title () {}
};

class Manager : public title
{
public:
    Manager (std::string str = "Manager", value_t sal = 30000 ) : title(str, sal) {}
    ~Manager () {}
};

class HumanResStaff : public title
{
public:
    HumanResStaff (std::string str = "Human_Resource_Staff", value_t sal = 18000 ) : title(str, sal) {}
    ~HumanResStaff () {}

};

class FinanceStaff : public title
{
public:
    FinanceStaff (std::string str = "Finance_Staff", value_t sal = 17000 ) : title(str, sal) {}
    ~FinanceStaff () {}
};

class SalesStaff : public title
{
public:
    SalesStaff (std::string str = "Sales_Staff", value_t sal = 19000 ) : title(str, sal) {}
    ~SalesStaff () {}
};

class AdminStaff : public title
{
public:
    AdminStaff (std::string str = "Admininstration_Staff", value_t sal = 20000 ) : title(str, sal) {}
    ~AdminStaff () {}
};