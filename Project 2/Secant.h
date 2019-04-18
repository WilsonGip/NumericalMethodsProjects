/**
 * Author: Wilson Gip
 * Project 2
 * Professor Amar Raheja
 * 11/9/2018
 */

#ifndef PROJECT2_SECANT_H
#define PROJECT2_SECANT_H

#include <iostream>
#include <string>
#include "EquationAB.h"
#include "Methods.h"

class Secant : public Methods {
public:
    Secant();
    void findRoot(double a, double b, EquationAB* eq, bool doNothing);
    void findRoot(double a, EquationAB* eq);
private:
    void reset();
    void moveToNext();
    void findTheRoot(double a, double b, EquationAB* eq);
    double getSecant(EquationAB* eq);
    double getModifiedSecant(EquationAB* eq);
    std::string printIT(int index, EquationAB* eq);
    void logIT(int index, EquationAB* eq);
    double a, b;
    bool modified;
};


#endif //PROJECT2_SECANT_H
