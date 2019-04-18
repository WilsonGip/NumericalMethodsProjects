/**
 * Author: Wilson Gip
 * Project 2
 * Professor Amar Raheja
 * 11/9/2018
 */

#include "Secant.h"

Secant::Secant() : Methods(){
    this->reset();
    this->modified = false;
    this->solvable = true;
}

void Secant::findTheRoot(double a, double b, EquationAB *eq) {
    std::cout << "Secant method: " <<  (this->modified ? "Modified" : "Regular") << "\n";
    this->reset();
    this->a = a;
    this->b = b;
    std::string tableTitle = (modified ?
                                    "n\tx0\t\txi+1\t\tf(x0)\t\td*x0\t\tf(x0+d*x0)\tEa\n" :
                                        "n\tx0\t\tx1\t\txi+1\t\tf(x0)\t\tf(x1)\t\tEa\n");
    tableTitle += "------------------------------------------------------------------------------------------------------------------------\n";
    this->csvLog = (modified ?
                                 "n,x0,xi+1,f(x0),d*x0,f(x0+d*x0),Ea\n" :
                                 "n,x0,x1,xi+1,f(x0),f(x1),Ea\n");
    std::string msg = "";

    std::cout << tableTitle;
    for (int i = 0; i < this->maxIterations; ++i) {
        this->prevC = this->c;
        this->c = (this->modified ? this->getModifiedSecant(eq) : this->getSecant(eq));
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
        this->moveToNext();
    }
    if(this->solvable){ std::cout << msg; }
}

void Secant::findRoot(double a, double b, EquationAB *eq, bool doNothing) {
    this->modified = false;
    this->findTheRoot(a, b, eq);
}

void Secant::findRoot(double a, EquationAB *eq) {
    this->modified = true;
    this->findTheRoot(a, 0, eq);
}


void Secant::reset() {
    Methods::reset();
    this->a = 0.0;
    this->b = 0.0;
}

void Secant::moveToNext() {
    if(this->modified){
        this->a = this->c;
    }else{
        this->a = this->b;
        this->b = this->c;
    }
}

double Secant::getSecant(EquationAB *eq) {
    if((eq->function(this->b) - eq->function(this->a)) == 0.0){
        std::cout << "Denominator equals 0, Not Solvable. Please choose different points!\n";
        this->solvable = false;
    }
    return ((eq->function(this->b) - eq->function(this->a)) == 0.0 ? 0 :
        (this->b - eq->function(this->b) * ((this->b - this->a)/(eq->function(this->b) - eq->function(this->a)))));
}

double Secant::getModifiedSecant(EquationAB *eq){
    if((eq->function(this->a + this->delta * this->a) - eq->function(this->a)) == 0.0){
        std::cout << "Denominator equals 0, Not Solvable. Please choose a different starting point!\n";
        this->solvable = false;
    }
    return ((eq->function(this->a + this->delta * this->a) - eq->function(this->a)) == 0.0 ? 0 :
        (this->a - eq->function(this->a) * ((this->delta * this->a) / (eq->function(this->a + this->delta * this->a) - eq->function(this->a)))));
}

std::string Secant::printIT(int index, EquationAB *eq) {
    std::string msg = std::string(std::to_string(index) + "\t");
    msg.append(std::to_string(this->a) + "\t");
    if (!this->modified) {msg.append(std::to_string(this->b) + "\t");}
    msg.append(std::to_string(this->c) + "\t");
    msg.append(std::to_string(eq->function(this->a)) + "\t");
    if (!this->modified) {msg.append(std::to_string(eq->functionDerived(this->b)) + "\t");}
    else {
        msg.append(std::to_string(this->delta*this->a) + "\t");
        msg.append(std::to_string(eq->function(this->delta*this->a+this->a)) + "\t");
    }
    if(index != 0){
        msg.append(std::to_string(this->getError()) + "\t");
    }
    msg.append("\n------------------------------------------------------------------------------------------------------------------------\n");

    return msg;
}

void Secant::logIT(int index, EquationAB *eq) {
    this->csvLog.append(std::string(std::to_string(index) + ","));
    this->csvLog.append(std::to_string(this->a) + ",");
    if (!this->modified) {this->csvLog.append(std::to_string(this->b) + ",");}
    this->csvLog.append(std::to_string(this->c) + ",");
    this->csvLog.append(std::to_string(eq->function(this->a)) + ",");
    if (!this->modified) {this->csvLog.append(std::to_string(eq->functionDerived(this->b)) + ",");}
    else {
        this->csvLog.append(std::to_string(this->delta*this->a) + ",");
        this->csvLog.append(std::to_string(eq->function(this->delta*this->a+this->a)) + ",");
    }
    if(index != 0){
        this->csvLog.append(std::to_string(this->getError()));
    }
    this->csvLog.append("\n");
}

