/*  Name: Wilson Gip
 *  Class: CS 3010 - Numerical Methods
 *  Project 1
 *  TTH 2:30pm - 3:45pm
 *
 * */

#include "GaussJacobiSiedal.h"

GaussJacobiSiedal::GaussJacobiSiedal(double **matrix, int row, int col, double error):Gaussian(matrix, row, col) {
    this->error = error;
    this->maxIteration = 50;
    this->prevX = this->zeroes();
    this->type = JACOBI;
    this->solvable = this->diagonalCheck();
}

GaussJacobiSiedal::~GaussJacobiSiedal() {
    delete [] this->prevX;
}

void GaussJacobiSiedal::Jacobi() {
    this->solve(JACOBI);
}

void GaussJacobiSiedal::Siedal() {
    this->solve(SIEDAL);
}

double GaussJacobiSiedal::jacobiMethod(int currentRow) {
    double sum = 0.0;
    for (int j = 0; j < this->row; ++j) {
        if(currentRow != j){
            sum += this->matrix[currentRow][j] * this->prevX[j];
        }
    }
    return sum;
}

double GaussJacobiSiedal::siedalMethod(int currentRow) {
    double sum = 0.0;
    for (int j = 0; j < currentRow; ++j) {
        sum += this->matrix[currentRow][j] * this->X[j];
    }
    for (int j = currentRow + 1; j < this->row; ++j) {
        sum += this->matrix[currentRow][j] * this->prevX[j];
    }
    return sum;
}


double GaussJacobiSiedal::solveX() {
    double sum;
    for (int i = 0; i < this->row; ++i) {
        sum = (this->type == SIEDAL ? siedalMethod(i) : jacobiMethod(i));
        this->X[i] = (this->matrix[i][row] - sum) / this->matrix[i][i];
    }
}

void GaussJacobiSiedal::solve() {
    this->reset();
    for (int i = 0; i < this->maxIteration; ++i) {
        std::copy(this->X, this->X + this->row, this->prevX);
        this->solveX();
        std::cout << "Iteration: " << std::to_string(i+1) << "\n";
        this->printX();
        if(this->getError() <= this->error){
            break;
        }
    }
}

void GaussJacobiSiedal::solve(GAUSSTYPE type) {
    this->type = type;
    if(this->solvable) {
        this->solve();
    }else{
        std::cout << "Please re-arrange your matrix to have nonzero diagonals.\n";
    }
}

void GaussJacobiSiedal::reset() {
    for (int i = 0; i < this->row; ++i) {
        this->prevX[i] = 0.0;
        this->X[i] = 0.0;
    }
}

double GaussJacobiSiedal::getError() {
    double bNorm = 0.0, resNorm = 0.0, residual[this->row];

    for (int i = 0; i < this->row; ++i) {
        for (int j = 0; j < this->row; ++j) {
            residual[i] += this->matrix[i][j]*this->X[j];
        }
        residual[i] -= this->matrix[i][this->row];
    }

    for (int i = 0; i < this->row; ++i) {
        bNorm += pow(this->matrix[i][this->row], 2);
        resNorm += pow(residual[i], 2);
    }

    return std::sqrt(resNorm)/std::sqrt(bNorm);
}

bool GaussJacobiSiedal::diagonalCheck() {
    for (int i = 0; i < this->row; ++i) {
        if(this->matrix[i][i] == 0.0){
            return false;
        }
    }
    return true;
}
