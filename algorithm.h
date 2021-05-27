#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "linklist.h"
#include "employee.h"
#include "title.h"

template <typename T>
void f()
{
    typename T::pointer p;
}
/*
template <typename range, typename compare>
void sort(range k, compare fn)
{
    auto l = k.begin(), r =k.end();
    for (auto i = l + 1; i != r; ++i) {
        auto key = (*i);
        for (auto j = i - 1;j != k.rend() && (*j) > key){
            s[j + 1] = s[j];
            j--;
        }
        s[j + 1] = key;
    }
}*/

template <typename iterator, typename filter>
iterator find(iterator first, iterator last, filter fn) {
    for (auto it=first;it!=last;++it)
    {
        if (fn(*it)) return it;
    }
    return nullptr;
}

