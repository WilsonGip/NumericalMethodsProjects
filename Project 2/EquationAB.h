/**
 * Author: Wilson Gip
 * Project 2
 * Professor Amar Raheja
 * 11/9/2018
 */

#ifndef PROJECT2_EQUATIONAB_H
#define PROJECT2_EQUATIONAB_H
#include <string>

class EquationAB {
public:
    EquationAB();
    virtual ~EquationAB();
    virtual double function(double x);
    virtual double functionDerived(double x);
    virtual std::string toString();
};


#endif //PROJECT2_EQUATIONAB_H
