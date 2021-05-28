#pragma once
#include "linklist.h"
#include "employee.h"
#include <iostream>

class result_set
{
private:
    linklist<employee::pointer>res;
public:
    void add(employee::pointer a)
    {
        res.push_back(a);
    }
    void print()
    {
        res.traverse([](auto & e) {
            std::cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
            std::cout << e ;
        });
        std::cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
        putchar ('\n');
    }
    bool empty()
    {
        return res.empty();
    }
};

class count_set
{
private:
    linklist<std::string *>res;
    linklist<int *>cnt;
public:
    void add(std::string a)
    {
        auto it1 = res.begin();
        auto it2 = cnt.begin();
        for ( ;; ) {
            if (it1 == res.end()) {
                auto temp1 = new std::string (a);
                auto temp2 = new int (1);
                res.push_back(temp1);
                cnt.push_back(temp2);
                return ;
            }
            if ((*(*it1)) == a) {
                ++(*(*it2));
                return ;
            }
            ++it1;
            ++it2;
        }
    }
    void print()
    {
        auto it1 = res.begin();
        auto it2 = cnt.begin();
        for ( ; it1 != res.end(); ) {
            std::cout << "------------------------------------------------" << std::endl;
            std::cout << '|' << std::setw(30) << (*(*it1)) << '|' << std::setw(15) << (*(*it2)) << '|' << std::endl;
            ++it2;
            ++it1;
        }
        std::cout << "------------------------------------------------" << std::endl;
        putchar ('\n');
    }
};