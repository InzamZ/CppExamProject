#pragma once
#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include "linklist.h"
#include "employee.h"
#include "algorithm.h"
#include "title.h"
#include "set.h"

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
        std::cout << eid << std::endl;
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
        sort<linklist<employee *>, std::function<bool(employee *, employee *)>>(Employ, employee::cmp);
        std::cout << "Loaded data from local file " << filename << "successfully!" << std::endl;
        std::cout << "Added " << cnt << " record(s) in total." << std::endl;
        putchar ('\n');
    }

    void print_all_staff()
    {
        putchar ('\n');
        std::cout << "Print all records ..." << std::endl;
        Employ.traverse([](auto & e) {
            std::cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
            std::cout << e ;
        });
        std::cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
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
        Employ._traverse([&datafile](auto e) {
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
            std::cout << std::left << std::setw(4) << 5 << ":count the record of some tags" << std::endl;
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
                putchar ('\n');
                std::cout << "You are trying to delete record" << std::endl;
                std::cout << std::left << std::setw(4) << 0 << ":cancel and back" << std::endl;
                std::cout << "Enter the EID you wanna delete" << std::endl;
                std::cin >> eid;
                delete_record(eid);
                std::cout << "Successfully!" << std::endl;
                putchar ('\n');
                break;
            }
            case 3: {
                std::string keyval;
                result_set ans;
                putchar ('\n');
                std::cout << "You are trying to query some record." << std::endl;
                std::cout << "Choose the kind of keyword..." << std::endl;
                std::cout << std::left << std::setw(4) << 0 << ":cancel and back" << std::endl;
                std::cout << std::left << std::setw(4) << 1 << ":EID" << std::endl;
                std::cout << std::left << std::setw(4) << 2 << ":name" << std::endl;
                std::cout << std::left << std::setw(4) << 3 << ":unit" << std::endl;
                std::cout << std::left << std::setw(4) << 4 << ":title" << std::endl;
                std::cout << std::left << std::setw(4) << 5 << ":salary" << std::endl;
                std::cin >> op2;
                if (op2 == 0)
                    break;
                if (op2 == 1) {
                    std::cout << "Enter the EID you wanna query..." << std::endl;
                    std::cin >> keyval;
                    if (keyval == "*") {
                        print_all_staff();
                        break;
                    }
                    for (auto it = Employ.begin(); it != Employ.end(); ++it) {
                        if (keyval == (*it)->eid) {
                            auto temp = new employee(*(*it));
                            ans.add(temp);
                        }
                    }
                    ans.print();
                    if (ans.empty())
                        std::cout << "Do not find any records!" << std::endl;
                    putchar('\n');
                    break;
                }
                if (op2 == 2) {
                    std::cout << "Enter the name you wanna query..." << std::endl;
                    std::cin >> keyval;
                    if (keyval == "*") {
                        print_all_staff();
                        break;
                    }
                    for (auto it = Employ.begin(); it != Employ.end(); ++it) {
                        if (keyval == (*it)->name) {
                            auto temp = new employee(*(*it));
                            ans.add(temp);
                        }
                    }
                    ans.print();
                    if (ans.empty())
                        std::cout << "Do not find any records!" << std::endl;
                    putchar('\n');
                    break;
                }
                if (op2 == 3) {
                    std::cout << "Enter the unit you wanna query..." << std::endl;
                    std::cin >> keyval;
                    if (keyval == "*") {
                        print_all_staff();
                        break;
                    }
                    for (auto it = Employ.begin(); it != Employ.end(); ++it) {
                        if (keyval == (*it)->unit) {
                            auto temp = new employee(*(*it));
                            ans.add(temp);
                        }
                    }
                    ans.print();
                    if (ans.empty())
                        std::cout << "Do not find any records!" << std::endl;
                    putchar('\n');
                    break;
                }
                if (op2 == 4) {
                    std::cout << "Enter the title you wanna query..." << std::endl;
                    std::cin >> keyval;
                    if (keyval == "*") {
                        print_all_staff();
                        break;
                    }
                    for (auto it = Employ.begin(); it != Employ.end(); ++it) {
                        if (keyval == ((*it)->_title)->titlename) {
                            auto temp = new employee(*(*it));
                            ans.add(temp);
                        }
                    }
                    ans.print();
                    if (ans.empty())
                        std::cout << "Do not find any records!" << std::endl;
                    putchar('\n');
                    break;
                }
                if (op2 == 5) {
                    int _sal;
                    std::cout << "Enter the salary you wanna query..." << std::endl;
                    std::cin >> _sal;
                    if (keyval == "*") {
                        print_all_staff();
                        break;
                    }
                    for (auto it = Employ.begin(); it != Employ.end(); ++it) {
                        if (_sal == ((*it)->_title)->salary) {
                            auto temp = new employee(*(*it));
                            ans.add(temp);
                        }
                    }
                    ans.print();
                    if (ans.empty())
                        std::cout << "Do not find any records!" << std::endl;
                    putchar('\n');
                    break;
                }
                putchar('\n');
                break;
            }
            case 4: {
                putchar ('\n');
                std::cout << "You are trying to update the information of some record." << std::endl;
                std::cout << std::left << std::setw(4) << 0 << ":cancel and back" << std::endl;
                std::cout << std::left << std::setw(4) << 1 << ":update the information of an exicted record" << std::endl;
                std::cout << std::left << std::setw(4) << 2 << ":change the salary of a title" << std::endl;
                std::cin >> op2;
                if (op2 == 0)
                    break;
                if (op2 == 1)
                    update_infor();
                if (op2 == 2)
                    change_sal();
                std::cout << "Successfully!" << std::endl;
                break;
            }
            case 5: {
                putchar ('\n');
                std::cout << "You are trying to count the record of some tags.Choose a tag..." << std::endl;
                std::cout << std::left << std::setw(4) << 0 << ":cancel and back" << std::endl;
                std::cout << std::left << std::setw(4) << 1 << ":gender" << std::endl;
                std::cout << std::left << std::setw(4) << 2 << ":unit" << std::endl;
                std::cout << std::left << std::setw(4) << 3 << ":title" << std::endl;
                std::cin >> op2;
                count_set ans;
                for (auto it = Employ.begin(); it != Employ.end(); ++it) {
                    if (op2 == 1)
                        ans.add((*it)->gender);
                    if (op2 == 2)
                        ans.add((*it)->unit);
                    if (op2 == 3)
                        ans.add(((*it)->_title)->titlename);
                }
                ans.print();
                std::cout << "Successfully!" << std::endl;
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
            if ((*it)->equal_eid(eid)) {
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
            sort<linklist<employee *>, std::function<bool(employee *, employee *)>>(Employ, employee::cmp);
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
    void update_infor()
    {
        putchar ('\n');
        std::string eid, name, gender, dob, doe, unitname, titlename, op;
        std::cout << "All the input must't include space." << std::endl;
        std::cout << "Enter the EID of the record" << std::endl;
        std::cin >> eid ;
        for (auto it = Employ.begin(); it != Employ.end(); ++it) {
            if ((*it)->equal_eid(eid)) {
                std::cout << "Update the EID of new record? (yes/no) " << std::endl;
                std::cin >> op;
                if (op == "yes") {
                    std::cout << "Enter the EID of the record" << std::endl;
                    std::cin >> eid ;
                    (*it)->eid = eid;
                }
                std::cout << "Update the name of the record? (yes/no) " << std::endl;
                std::cin >> op;
                if (op == "yes") {
                    std::cout << "Enter the new name of the record" << std::endl;
                    std::cin >> name;
                    (*it)->name = name;
                }
                std::cout << "Update the gender of new record? (yes/no) " << std::endl;
                std::cin >> op;
                if (op == "yes") {
                    std::cout << "Enter the new gender of the record" << std::endl;
                    std::cin >> gender ;
                    (*it)->gender = gender;
                }
                std::cout << "Update the date of birth of the record? (yes/no) " << std::endl;
                std::cin >> op;
                if (op == "yes") {
                    std::cout << "Enter the new name of the record" << std::endl;
                    std::cin >> dob;
                    (*it)->dob = dob;
                }
                std::cout << "Update the date of enter of the record? (yes/no) " << std::endl;
                std::cin >> op;
                if (op == "yes") {
                    std::cout << "Enter the new date of enter of the record" << std::endl;
                    std::cin >> doe;
                    (*it)->doe = doe;
                }
                std::cout << "Update the unit of the record? (yes/no) " << std::endl;
                std::cin >> op;
                if (op == "yes") {
                    std::cout << "Enter the new unit of the record.( Human_Resource_Department / Finance_Department / Sales_Department / Administration_Department )" << std::endl;
                    std::cin >> unitname;
                    (*it)->unit = unitname;
                }
                std::cout << "Update the title of the record? (yes/no) " << std::endl;
                std::cin >> op;
                if (op == "yes") {
                    std::cout << "Enter the new title of the record.( Manager / Human_Resource_Staff / Finance_Staff / Sales_Staff / Administration_Staff )" << std::endl;
                    std::cin >> titlename;
                    if (titlename == "Manager")
                        (*it)->_title = salary[MAN];
                    if (titlename == "Human_Resource_Staff")
                        (*it)->_title = salary[HRS];
                    if (titlename == "Finance_Staff")
                        (*it)->_title = salary[FS];
                    if (titlename == "Sales_Staff")
                        (*it)->_title = salary[SS];
                    if (titlename == "Administration_Staff")
                        (*it)->_title = salary[AS];
                }
            }
        }
        sort<linklist<employee *>, std::function<bool(employee *, employee *)>>(Employ, employee::cmp);
    }
    void change_sal()
    {
        std::string titlename;
        title::value_t nsal;
        std::cout << "You are trying to update the salary of a title." << std::endl;
        std::cout << "Enter the title you wanna change salary.( Manager / Human_Resource_Staff / Finance_Staff / Sales_Staff / Administration_Staff )" << std::endl;
        std::cin >> titlename ;
        std::cout << "Enter the new value of salary." << std::endl;
        std::cin >> nsal;
        if (titlename == "Manager")
            salary[MAN]->salary = nsal;
        if (titlename == "Human_Resource_Staff")
            salary[HRS]->salary = nsal;
        if (titlename == "Finance_Staff")
            salary[FS]->salary = nsal;
        if (titlename == "Sales_Staff")
            salary[SS]->salary = nsal;
        if (titlename == "Administration_Staff")
            salary[AS]->salary = nsal;
        for (auto it = Employ.begin(); it != Employ.end(); ++it) {
            if ((*it)->cmp_title(titlename))
                std::cout << (*it);
        }
    }
    void loading()
    {
        load_from_file("employee.dat");
    }
};