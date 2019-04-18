/*  Name: Wilson Gip
 *  Class: CS 3010 - Numerical Methods
 *  Project 1
 *  TTH 2:30pm - 3:45pm
 *
 * */

#ifndef PROJECT1_GAUSSJACOBISIEDAL_H
#define PROJECT1_GAUSSJACOBISIEDAL_H

#include <iostream>
#include <string>
#include <cmath>
#include "Gaussian.h"

enum GAUSSTYPE {JACOBI, SIEDAL};

class GaussJacobiSiedal : public Gaussian{
public:
    GaussJacobiSiedal(double** matrix, int row, int col, double error);
    ~GaussJacobiSiedal();
    void Jacobi();
    void Siedal();
private:
    void reset();
    void solve();
    void solve(GAUSSTYPE type);
    bool diagonalCheck();
    double jacobiMethod(int currentRow);
    double siedalMethod(int currentRow);
    double solveX();
    double getError();
    double error;
    double* prevX;
    int maxIteration;
    GAUSSTYPE type;
};


#endif //PROJECT1_GAUSSJACOBISIEDAL_H
