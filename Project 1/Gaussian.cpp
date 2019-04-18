/*  Name: Wilson Gip
 *  Class: CS 3010 - Numerical Methods
 *  Project 1
 *  TTH 2:30pm - 3:45pm
 *
 * */
#include "Gaussian.h"

Gaussian::Gaussian(double **matrix, int row, int col) {
    this->matrix = new double*[row];
    for (int i = 0; i < row; ++i) {
        this->matrix[i] = new double[col];
        for (int j = 0; j < col; ++j) {
            this->matrix[i][j] = matrix[i][j];
        }
    }
    this->row = row;
    this->col = col;
    this->X = this->zeroes();
    this->solvable = true;
}

Gaussian::~Gaussian() {
    this->deleteMatrix();
    delete [] this->X;
}

void Gaussian::printMatrix() {
    for (int i = 0; i < this->row; ++i) {
        std::cout << "[";
        for (int j = 0; j < this->col; ++j) {
            std::cout << std::to_string(this->matrix[i][j]) << (j < this->row ? ", " : "");
        }
        std::cout << "]\n";
    }
    std::cout << std::endl;
}

void Gaussian::deleteMatrix() {
    for(int i = 0; i < this->row; i++){
        delete [] this->matrix[i];
    }
    delete [] this->matrix;
}

void Gaussian::print(double* arr){
    for (int i = 0; i < this->row; ++i) {
        std::cout << "X" << std::to_string(i+1) << " = " << std::to_string(arr[i]) << "\n";
    }
    std::cout << "\n";
}

void Gaussian::printX() {
    this->print(this->X);
}

double* Gaussian::zeroes() {
    double* array = new double[this->row];
    for (int i = 0; i < this->row; ++i) {
        array[i] = 0.0;
    }
    return array;
}
