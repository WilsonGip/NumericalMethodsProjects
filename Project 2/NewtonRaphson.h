/**
 * Author: Wilson Gip
 * Project 2
 * Professor Amar Raheja
 * 11/9/2018
 */

#ifndef PROJECT2_NEWTONRAPHSON_H
#define PROJECT2_NEWTONRAPHSON_H
#include <string>
#include <iostream>
#include "EquationAB.h"
#include "Methods.h"

class NewtonRaphson : public Methods {
public:
    NewtonRaphson();
    void findRoot(double x, EquationAB* eq);
private:
    double getNewtonRaphson(EquationAB* eq);
    std::string printIT(int index, EquationAB* eq);
    void logIT(int index, EquationAB* eq);
};


#endif //PROJECT2_NEWTONRAPHSON_H
