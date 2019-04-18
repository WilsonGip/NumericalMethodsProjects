/**
 * Author: Wilson Gip
 * Project 2
 * Professor Amar Raheja
 * 11/9/2018
 */

#include "NewtonRaphson.h"

NewtonRaphson::NewtonRaphson() : Methods() {
    this->reset();
}

void NewtonRaphson::findRoot(double x, EquationAB *eq) {
    std::cout << "Newton Raphson Method\n";
    this->reset();
    this->c = x;
    std::string tableTitle  =   "n\tx\t\tf(x)\t\tf'(x)\t\tEa\n";
    tableTitle              +=  "------------------------------------------------------------------------------------------------------------------------\n";
    this->csvLog = "n,x,f(x),f'(x),Ea\n";
    std::string msg = "";

    std::cout << tableTitle;
    for (int i = 0; i < this->maxIterations; ++i) {
        this->prevC = this->c;
        this->c = getNewtonRaphson(eq);
        if(!this->solvable){ break; }
        msg = "The approx solution: " + std::to_string(this->c)
              + " @ iteration: " + std::to_string(i) + " for equation: " + eq->toString() + "\n\n";
        if(i != 0){
            this->log(i);
            if(this->checkError()){
                std::cout << this->printIT(i, eq);
                this->logIT(i, eq);
                break;
            }
        }
        std::cout << this->printIT(i, eq);
        this->logIT(i, eq);
    }
    if(this->solvable){std::cout << msg;}
}

std::string NewtonRaphson::printIT(int index, EquationAB *eq) {
    std::string msg = std::string(std::to_string(index) + "\t");
    if(index != 0){
        msg.append(std::to_string(this->c) + "\t");
        msg.append(std::to_string(eq->function(this->c)) + "\t");
        msg.append(std::to_string(eq->functionDerived(this->c)) + "\t");
        msg.append(std::to_string(this->getError()) + "\t");
    }else{
        msg.append(std::to_string(this->prevC) + "\t");
        msg.append(std::to_string(eq->function(this->prevC)) + "\t");
        msg.append(std::to_string(eq->functionDerived(this->prevC)) + "\t");
    }
    msg.append("\n------------------------------------------------------------------------------------------------------------------------\n");

    return msg;
}

double NewtonRaphson::getNewtonRaphson(EquationAB* eq) {
    if(eq->functionDerived(this->c) == 0.0){
        std::cout << "f'(" << this->c << ") equals to 0. Please choose another starting point!\n";
        this->solvable = false;
    }
    return (eq->functionDerived(this->c) == 0.0 ? 0 :
        (this->c - (eq->function(this->c)/eq->functionDerived(this->c))));
}

void NewtonRaphson::logIT(int index, EquationAB *eq) {
    this->csvLog.append(std::string(std::to_string(index) + ","));
    if(index != 0){
        this->csvLog.append(std::to_string(this->c) + ",");
        this->csvLog.append(std::to_string(eq->function(this->c)) + ",");
        this->csvLog.append(std::to_string(eq->functionDerived(this->c)) + ",");
        this->csvLog.append(std::to_string(this->getError()));
    }else{
        this->csvLog.append(std::to_string(this->prevC) + ",");
        this->csvLog.append(std::to_string(eq->function(this->prevC)) + ",");
        this->csvLog.append(std::to_string(eq->functionDerived(this->prevC)) + ",");
    }
    this->csvLog.append("\n");
}
