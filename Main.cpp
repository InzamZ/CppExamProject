#include <iostream>
#include <functional>
#include <fstream>
#include <string>
#include "linklist.h"
#include "employee.h"
#include "title.h"
#include "feature.h"

int main()
{
    sys staffsys;
    staffsys.welcome();
    staffsys.loading();
    staffsys.choose();
    staffsys.print_all_staff();
    staffsys.rewrite();
    return 0;
}