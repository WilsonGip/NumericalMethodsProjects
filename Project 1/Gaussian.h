/*  Name: Wilson Gip
 *  Class: CS 3010 - Numerical Methods
 *  Project 1
 *  TTH 2:30pm - 3:45pm
 *
 * */

#ifndef PROJECT1_GAUSSIAN_H
#define PROJECT1_GAUSSIAN_H

#include <iostream>
#include <string>

class Gaussian {
public:
    Gaussian(double** matrix, int row, int col);
    virtual ~Gaussian();
    virtual void printX();
protected:
    void print(double* arr);
    void printMatrix();
    void deleteMatrix();
    double* zeroes();
    double** matrix;
    double* X;
    int row;
    int col;
    bool solvable;
};


#endif //PROJECT1_GAUSSIAN_H
