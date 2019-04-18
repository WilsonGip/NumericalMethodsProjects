/**
 * Author: Wilson Gip
 * Project 2
 * Professor Amar Raheja
 * 11/9/2018
 */
#ifndef PROJECT2_EQUATIONA_H
#define PROJECT2_EQUATIONA_H
#include <math.h>
#include <string>
#include "EquationAB.h"

class EquationA : public EquationAB {
public:
    EquationA();
    ~EquationA();
    double function(double x);
    double functionDerived(double x);
    std::string toString();
};


#endif //PROJECT2_EQUATIONA_H
