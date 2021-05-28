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

template <typename range, typename compare>
void sort(range &k, compare fn)
{
    auto l = k.begin(), r = k.end();
    auto i = l, j = l, m = j;
    for (i = l + 1; i != r; ++i) {
        j = i;
        --j;
        for (; j != k.rend() && fn(*(j + 1), (*j));) {
            m = j + 1;
            // auto temp = (*j);
            // (*j) = (*m);
            // (*m) = temp;
            j._swap(m);
            --j;
        }
    }
}

template <typename iterator, typename filter>
iterator find(iterator first, iterator last, filter fn)
{
    for (auto it = first; it != last; ++it) {
        if (fn(*it))
            return it;
    }
    return nullptr;
}

