#pragma once

#include <iostream>
#include <string>
#include "employee.h"

using value_t = employee*;

struct Node {
    value_t value;
    Node *pre, *next;
    Node(): value(nullptr), pre(nullptr), next(nullptr) {}
}