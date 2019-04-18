/**
 * Author: Wilson Gip
 * Project 2
 * Professor Amar Raheja
 * 11/9/2018
 */
#include "EquationB.h"
#include <iostream>

EquationB::EquationB() {
}

EquationB::~EquationB() {
}

double EquationB::function(double x) {
    return (x + 10 - x*cosh(50.0/x));
}

double EquationB::functionDerived(double x) {
    return (((50.0*sinh(50.0/x))/ x) - cosh(50.0/x) + 1);
}

std::string EquationB::toString() {
    return "f(x) = x + 10 - xcosh(50/x)";
}
