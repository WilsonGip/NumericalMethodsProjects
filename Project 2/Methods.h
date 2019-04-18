/**
 * Author: Wilson Gip
 * Project 2
 * Professor Amar Raheja
 * 11/9/2018
 */

#ifndef PROJECT2_METHODS_H
#define PROJECT2_METHODS_H

#include <math.h>
#include <iostream>
#include <string>
#include <vector>
#include "EquationAB.h"

class Methods {
public:
    Methods();
    virtual ~Methods();
    virtual void findRoot(double a, double b, EquationAB* eq);
    virtual void findRoot(double a, double b, EquationAB* eq, bool falsePosition);
    virtual void findRoot(double a, EquationAB* eq);
    std::string getTitle();
    std::vector<double> getErrorArr();
    void printLog();
protected:
    bool checkError();
    void log(int index);
    void reset();
    double getError();
    int maxIterations;
    double c, prevC;
    double delta;
    bool solvable;
    std::string csvLog;
private:
    bool checkError(double error);
    void fillArray(double* arr);
    double epsilon;
    double* approxError;
};


#endif //PROJECT2_METHODS_H
