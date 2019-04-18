/**
 * Author: Wilson Gip
 * Project 2
 * Professor Amar Raheja
 * 11/9/2018
 */

#include "Methods.h"

Methods::Methods() {
    this->maxIterations = 100;
    this->epsilon = 0.01;
    this->delta = 0.01;
    this->c = 0.0;
    this->prevC = 0.0;
    this->approxError = new double[this->maxIterations];
    this->solvable = true;
    this->csvLog = "";
}

Methods::~Methods() {
    delete [] this->approxError;
}

double Methods::getError() {
    return abs((this->c - this->prevC) / this->c);
}

bool Methods::checkError(double error) {
    return  error <= this->epsilon;
}

void Methods::log(int index) {
    this->approxError[index] = this->getError();
}

void Methods::fillArray(double *arr) {
    for (int i = 0; i < this->maxIterations; ++i) {
        arr[i] = -1.0;
    }
}

void Methods::reset() {
    this->c = 0.0;
    this->prevC = 0.0;
    this->fillArray(this->approxError);
    this->solvable = true;
    this->csvLog = "";
}

bool Methods::checkError() {
    return this->checkError(this->getError());
}

std::vector<double> Methods::getErrorArr() {
    std::vector<double> vec;
    for (int i = 0; i < this->maxIterations; ++i) {
        vec.push_back(this->approxError[i]);
    }
    return vec;
}

void Methods::findRoot(double a, double b, EquationAB *eq) {

}

void Methods::findRoot(double a, EquationAB *eq) {

}

void Methods::findRoot(double a, double b, EquationAB *eq, bool falsePosition) {

}

void Methods::printLog() {
    std::cout << this->csvLog;
}
