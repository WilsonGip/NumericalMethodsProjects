//
// Created by Wilson on 11/5/2018.
//

#ifndef PROJECT2_BISECTION_H
#define PROJECT2_BISECTION_H

#include "EquationAB.h"
#include "Methods.h"
#include <iostream>
#include <string>

class Bisection : public Methods {
public:
    Bisection();
    void findRoot(double a, double b, EquationAB* eq, bool falsePosition);
private:
    void checkMiddle(EquationAB* eq);
    double getFalsePosition(EquationAB* eq);
    double getBisection();
    void reset();
    std::string printIT(int index, EquationAB* eq);
    void logIT(int index, EquationAB* eq);
    double a, b;
};


#endif //PROJECT2_BISECTION_H
