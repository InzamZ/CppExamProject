#pragma once
#include <iostream>
#include <string>

class title
{
    using value_t = int;
protected:
    std::string titlename;
    value_t salary;
public:
    title (std::string str="Unknown",value_t sal=0 ) : titlename(str) , salary(sal) {}
    ~title () {}
};
