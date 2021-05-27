#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "linklist.h"
#include "employee.h"
#include "algorithm.h"
#include "title.h"

class sys
{
private:
    linklist<employee::pointer> Employ;
    title::pointer salary[5];
    enum {MAN = 0, HRS, FS, SS, AS};
public:
    sys()
    {
        salary[0] = dynamic_cast<title::pointer>(new Manager);
        salary[1] = dynamic_cast<title::pointer>(new HumanResStaff);
        salary[2] = dynamic_cast<title::pointer>(new FinanceStaff) ;
        salary[3] = dynamic_cast<title::pointer>(new SalesStaff) ;
        salary[4] = dynamic_cast<title::pointer>(new AdminStaff) ;
    }

    ~sys()
    {
        delete dynamic_cast<Manager::pointer>(salary[0]);
        delete dynamic_cast<HumanResStaff::pointer>(salary[1]);
        delete dynamic_cast<FinanceStaff::pointer>(salary[2]);
        delete dynamic_cast<SalesStaff::pointer>(salary[3]);
        delete dynamic_cast<AdminStaff::pointer>(salary[4]);
    }

    void welcome()
    {
        std::cout << "This is a Staff Record System." << std::endl;
        std::cout << "Please wait for a while because of loading local records." << std::endl;
    }

    void load_from_file(std::string filename)
    {
        putchar ('\n');
        int cnt = 0;
        std::cout << "Loading data from local file " << filename << " ..." << std::endl;
        std::ifstream datafile(filename);
        if (! datafile.is_open()) {
            std::cout << "Error opening file " << filename << " in loadin process" << std::endl;
            exit (1);
        }
        std::string eid, name, gender, dob, doe, unitname, titlename;
        title::value_t _salary;
        title::pointer _title;
        datafile >> eid >> name >> gender >> dob >> doe >> unitname >> titlename >> _salary;
        do {
            ++cnt;
            if (titlename == "Manager")
                _title = salary[MAN], salary[MAN]->update(_salary);
            if (titlename == "Human_Resource_Staff") {
                _title = salary[HRS]; salary[HRS]->update(_salary);
            }
            if (titlename == "Finance_Staff") {
                _title = salary[FS]; salary[FS]->update(_salary);
            }
            if (titlename == "Sales_Staff") {
                _title = salary[SS]; salary[SS]->update(_salary);
            }
            if (titlename == "Administration_Staff") {
                _title = salary[AS]; salary[AS]->update(_salary);
            }
            employee::pointer temp = new employee{eid, name, gender, dob, doe, unitname, _title};
            Employ.push_back(temp);
            datafile >> eid >> name >> gender >> dob >> doe >> unitname >> titlename >> _salary;
        }
        while (!datafile.eof());
        datafile.close();
        putchar ('\n');
        std::cout << "Loaded data from local file " << filename << " successfully!" << std::endl;
        std::cout << "Added " << cnt << " record(s) in total." << std::endl;
        putchar ('\n');
    }

    void print_all_staff()
    {
        putchar ('\n');
        std::cout << "Print all records ..." << std::endl;
        Employ.traverse([](auto & e) {
            std::cout << e ;
        });
        putchar ('\n');
    }

    void rewrite()
    {
        std::cout << "Rewriting data into local file \"employee.data\" ..." << std::endl;
        std::ofstream datafile("employee.dat");
        if (! datafile.is_open()) {
            std::cout << "Error opening file in rewrite process";
            exit (1);
        }
        Employ.traverse([&datafile](auto & e) {
            datafile << e ;
        });
        datafile.close();
        std::cout << "Rewrited data into local file \"employee.data\" successfully!" << std::endl;
        std::cout << "Have a nice day! (^ - ^)" << std::endl;
    }

    void choose ()
    {
        putchar ('\n');
        while (1) {
            std::cout << "Enter the number below to choose the operator" << std::endl;
            std::cout << std::left << std::setw(4) << 0 << ":quit and rewrite the local records" << std::endl;
            std::cout << std::left << std::setw(4) << 1 << ":add record" << std::endl;
            std::cout << std::left << std::setw(4) << 2 << ":delete record" << std::endl;
            std::cout << std::left << std::setw(4) << 3 << ":query records" << std::endl;
            std::cout << std::left << std::setw(4) << 4 << ":update the information of some record" << std::endl;
            int op, op2;
            std::cin >> op;
            switch (op) {
            case 0: {
                return ;
            }
            case 1: {
                std::cout << "You are trying to add record" << std::endl;
                std::cout << std::left << std::setw(4) << 0 << ":cancel and back" << std::endl;
                std::cout << std::left << std::setw(4) << 1 << ":enter to add record" << std::endl;
                std::cout << std::left << std::setw(4) << 2 << ":add record from files" << std::endl;
                std::cin >> op2;
                add_record(op2);
                break;
            }
            case 2: {
                std::string eid;
                std::cout << "You are trying to delete record" << std::endl;
                std::cout << std::left << std::setw(4) << 0 << ":cancel and back" << std::endl;
                std::cout << "Enter the EID you wanna delete" << std::endl;
                std::cin >> eid;
                delete_record(eid);
                break;
            }
            case 3: {
                std::cout << "You are trying to add record" << std::endl;
                break;
            }
            default:
                std::cout << "Illegal input!" << std::endl;
                break;
            }
        }
        putchar ('\n');
    }

    void delete_record(std::string eid)
    {
        for (auto it = Employ.begin(); it != Employ.end(); ++it) {
            if ((*it)->cmp_eid(eid)) {
                it.remove();
                return ;
            }
        }
    }

    void add_record(int op)
    {
        putchar ('\n');
        if (op == 1) {
            std::string eid, name, gender, dob, doe, unitname, titlename;
            title::pointer _title;
            std::cout << "All the input must't include space." << std::endl;
            std::cout << "Enter the EID of new record" << std::endl;
            std::cin >> eid ;
            std::cout << "Enter the name of new record" << std::endl;
            std::cin >> name ;
            std::cout << "Enter the gender of new record.(male/female)" << std::endl;
            std::cin >> gender ;
            std::cout << "Enter the date of birth of new record.(yyyy/mm/dd)" << std::endl;
            std::cin >> dob ;
            std::cout << "Enter the date of  of new record.(yyyy/mm/dd)" << std::endl;
            std::cin >> doe ;
            std::cout << "Enter the unitname of new record.( Human_Resource_Department / Finance_Department / Sales_Department / Administration_Department )" << std::endl;
            std::cin >> unitname ;
            std::cout << "Enter the title of new record.( Manager / Human_Resource_Staff / Finance_Staff / Sales_Staff / Administration_Staff )" << std::endl;
            std::cin >> titlename ;
            if (titlename == "Manager")
                _title = salary[MAN];
            if (titlename == "Human_Resource_Staff")
                _title = salary[HRS];
            if (titlename == "Finance_Staff")
                _title = salary[FS];
            if (titlename == "Sales_Staff")
                _title = salary[SS];
            if (titlename == "Administration_Staff")
                _title = salary[AS];
            employee::pointer temp = new employee{eid, name, gender, dob, doe, unitname, _title};
            Employ.emplace_back(temp);
            std::cout << "Successfully!" << std::endl;
        }
        else if (op == 2) {
            std::cout << "Enter the name of the file (space is illegal!) " << std::endl;
            std::string filename;
            std::cin >> filename;
            load_from_file(filename);
        }
        else
            std::cout << "Illegal input!" << std::endl;
        putchar ('\n');
    }

    void loading()
    {
        load_from_file("employee.dat");
    }
};