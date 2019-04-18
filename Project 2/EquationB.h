/**
 * Author: Wilson Gip
 * Project 2
 * Professor Amar Raheja
 * 11/9/2018
 */

#ifndef PROJECT2_EQUATIONB_H
#define PROJECT2_EQUATIONB_H
#include <math.h>
#include "EquationAB.h"

class EquationB : public EquationAB {
public:
    EquationB();
    ~EquationB();
    double function(double x);
    double functionDerived(double x);
    std::string toString();
};


#endif //PROJECT2_EQUATIONB_H
