/**
 * Author: Wilson Gip
 * Project 2
 * Professor Amar Raheja
 * 11/9/2018
 */

#include "EquationA.h"

EquationA::EquationA() {
}

EquationA::~EquationA() {
}

double EquationA::function(double x) {
    return (2*pow(x,3) - 11.7*pow(x,2) + 17.7*x - 5);
}

double EquationA::functionDerived(double x) {
    return (6*pow(x, 2) - 23.4*x + 17.7);
}

std::string EquationA::toString() {
    return "f(x) = 2x^3 - 11.7x^2 + 17.7x - 5";
}
