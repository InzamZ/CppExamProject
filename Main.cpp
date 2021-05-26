#include <iostream>
#include <fstream>
#include <string>
#include "linklist.h"
#include "employee.h"
#include "unit.h"
#include "title.h"
#include "system.h"

int main()
{
    //InitProg();//Load the init data
    linklist<employee::pointer> Employ;
    std::ifstream datafile("employee.dat");
    if (! datafile.is_open()) {
        std::cout << "Error opening file";
        exit (1);
    }
    std::string eid, name, gender, dob, doe, unitname, titlename;
    title::value_t sal;
    title::pointer _title;
    datafile >> eid >> name >> gender >> dob >> doe >> unitname >> titlename >> sal;
    do {
        if (titlename == "Manager")
            _title = dynamic_cast<title::pointer>(new Manager);
        if (titlename == "Human_Resource_Staff")
            _title = dynamic_cast<title::pointer>(new HumanResStaff);
        if (titlename == "Finance_Staff")
            _title = dynamic_cast<title::pointer>(new FinanceStaff) ;
        if (titlename == "Sales_Staff")
            _title = dynamic_cast<title::pointer>(new SalesStaff) ;
        if (titlename == "Administration_Staff")
            _title = dynamic_cast<title::pointer>(new AdminStaff) ;
        employee::pointer temp = new employee{eid, name, gender, dob, doe, unitname, _title};
        Employ.emplace_back(temp);
        datafile >> eid >> name >> gender >> dob >> doe >> unitname >> titlename >> sal;
    }
    while (!datafile.eof());
    datafile.close();
    for (auto it = Employ.begin(); it != Employ.end(); ++it)
        (*it)->infor();
    return 0;
}