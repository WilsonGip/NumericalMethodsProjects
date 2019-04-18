/*  Name: Wilson Gip
 *  Class: CS 3010 - Numerical Methods
 *  Project 1
 *  TTH 2:30pm - 3:45pm
 *
 * */
#include "GaussPartialPivot.h"

GaussPartialPivot::GaussPartialPivot(double** matrix, int row, int col):Gaussian(matrix, row, col){
    this->indexArr = new int[row];
    this->scaleArr = new double[row];
}

GaussPartialPivot::~GaussPartialPivot(){
    delete [] this->indexArr;
    delete [] this->scaleArr;
}

void GaussPartialPivot::Gauss(){
    this->printMatrix();
    this->findMax();
    if(this->solvable){
        int largestRatioIndex, tempSwap;
        for (int k = 0; k < this->row-1; ++k) {
            largestRatioIndex = this->getLargestRatioIndex(k);

            tempSwap = this->indexArr[largestRatioIndex];
            this->indexArr[largestRatioIndex] = this->indexArr[k];
            this->indexArr[k] = tempSwap;

            this->eliminateVariable(k);
            this->printMatrix();
        }
    }
    this->Solve();
}

void GaussPartialPivot::Solve(){
    if(this->solvable) {
        double sum;
        for (int i = this->row - 1; i >= 0; --i) {
            sum = 0.0;
            for (int j = i + 1; j < this->row; ++j) {
                sum += this->matrix[this->indexArr[i]][j] * this->X[j];
            }
            if (this->matrix[this->indexArr[i]][i] == 0.0) {
                std::cerr << "Error: Cannot divide by zero!" << std::endl;
                this->solvable = false;
                break;
            } else {
                this->X[i] = (this->matrix[this->indexArr[i]][row] - sum) / this->matrix[this->indexArr[i]][i];
            }
        }
    }
}


void GaussPartialPivot::findMax(){
    double smax;
    for (int i = 0; i < this->row; ++i) {
        this->indexArr[i] = i;
        smax = 0.0;
        for (int j = 0; j < this->row; ++j) {
            smax = std::max(smax, std::abs(this->matrix[i][j]));
        }
        if(smax == 0){
            std::cerr << "Error: A Large Coefficient is a Zero!" << std::endl;
            this->solvable = false;
            break;
        }
        this->scaleArr[i] = smax;
    }
}

void GaussPartialPivot::printX(){
    if(this->solvable){
        this->print(this->X);
    } else {
        std::cout << "The matrix cannot be solved with Scaled Partial Pivot!\n";
    }

}

int GaussPartialPivot::getLargestRatioIndex(int currentCol) {
    double ratio, ratioMax = 0.0;
    int largestRatioIndex = 0, currentIndex;
    for (int i = currentCol; i < this->row; ++i) {
        currentIndex = this->indexArr[i];
        ratio = std::abs(this->matrix[currentIndex][currentCol] / this->scaleArr[currentIndex]);
        if (ratio > ratioMax) {
            ratioMax = ratio;
            largestRatioIndex = i;
        }
    }
    return largestRatioIndex;
}

void GaussPartialPivot::eliminateVariable(int currentCol) {
    double xMult;
    for (int i = currentCol + 1; i < this->row; ++i) {
        xMult = this->matrix[this->indexArr[i]][currentCol] / this->matrix[this->indexArr[currentCol]][currentCol];
        for (int j = currentCol; j < this->col; ++j) {
            this->matrix[this->indexArr[i]][j] -= (xMult * this->matrix[this->indexArr[currentCol]][j]);
        }
    }
}
