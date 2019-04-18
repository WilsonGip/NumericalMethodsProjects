/*  Name: Wilson Gip
 *  Class: CS 3010 - Numerical Methods
 *  Project 1
 *  TTH 2:30pm - 3:45pm
 *
 * */

#ifndef PROJECT1_GAUSSPARTIALPIVOT_H
#define PROJECT1_GAUSSPARTIALPIVOT_H

#include <algorithm>
#include <iostream>
#include "Gaussian.h"

class GaussPartialPivot : public Gaussian {
public:
    GaussPartialPivot(double** matrix, int row, int col);
    ~GaussPartialPivot();
    void Gauss();
    void printX();
private:
    int getLargestRatioIndex(int currentCol);
    void eliminateVariable(int currentCol);
    void findMax();
    void Solve();
    double* scaleArr;
    int* indexArr;
};


#endif //PROJECT1_GAUSSPARTIALPIVOT_H
