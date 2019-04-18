/**
 * Author: Wilson Gip
 * Project 2
 * Professor Amar Raheja
 * 11/9/2018
 */

#include "Bisection.h"

Bisection::Bisection():Methods(){
    this->reset();
}
void Bisection::findRoot(double a, double b, EquationAB *eq, bool falsePosition) {
    std::cout << "Bisection method: " <<  (falsePosition ? "False Position" : "Regular") << "\n";
    this->reset();
    this->a = a;
    this->b = b;
    std::string tableTitle  =   "n\ta\t\tb\t\tc\t\tf(a)\t\tf(b)\t\tf(c)\t\tEa\n";
    tableTitle              +=  "------------------------------------------------------------------------------------------------------------------------\n";
    this->csvLog = "n,a,b,c,f(a),f(b),f(c),Ea\n";
    std::string msg = "";

    std::cout << tableTitle;
    for (int i = 0; i < this->maxIterations + 1; ++i) {
        this->prevC = this->c;
        this->c = (falsePosition ? this->getFalsePosition(eq) : this->getBisection());
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
        this->checkMiddle(eq);
    }
    if(this->solvable) { std::cout << msg; }
}

void Bisection::checkMiddle(EquationAB* eq) {
    if(eq->function(this->a) * eq->function(this->b) > 0){
        std::cout << "The starting points given cannot be solved.\n\n";
        this->solvable = false;
    }else{
        if(eq->function(this->c) * eq->function(this->a) < 0){
            this->b = this->c;
        }else{
            this->a = this->c;
        }
    }
}

double Bisection::getFalsePosition(EquationAB* eq) {
    if((eq->function(this->b) - eq->function(this->a)) == 0.0){
        std::cout << "Denominator equals 0, Not Solvable. Please choose different points!\n";
        this->solvable = false;
    }
    return ((eq->function(this->b) - eq->function(this->a)) == 0.0 ? 0 :
        (this->a - eq->function(this->a) *((this->b - this->a)/(eq->function(this->b) - eq->function(this->a)))));
}

double Bisection::getBisection() {
    return ((this->a + this-> b)/2.0);
}

void Bisection::reset() {
    Methods::reset();
    this->a = 0.0;
    this->b = 0.0;
}

std::string Bisection::printIT(int index, EquationAB* eq) {
    std::string msg = std::string(std::to_string(index) + "\t");
    msg.append(std::to_string(this->a) + "\t");
    msg.append(std::to_string(this->b) + "\t");
    msg.append(std::to_string(this->c) + "\t");
    msg.append(std::to_string(eq->function(this->a)) + "\t");
    msg.append(std::to_string(eq->function(this->b)) + "\t");
    msg.append(std::to_string(eq->function(this->c)) + "\t");
    if(index != 0){
        msg.append(std::to_string(this->getError()) + "\t");
    }
    msg.append("\n------------------------------------------------------------------------------------------------------------------------\n");

    return msg;
}

void Bisection::logIT(int index, EquationAB *eq) {
    this->csvLog.append(std::string(std::to_string(index) + ","));
    this->csvLog.append(std::to_string(this->a) + ",");
    this->csvLog.append(std::to_string(this->b) + ",");
    this->csvLog.append(std::to_string(this->c) + ",");
    this->csvLog.append(std::to_string(eq->function(this->a)) + ",");
    this->csvLog.append(std::to_string(eq->function(this->b)) + ",");
    this->csvLog.append(std::to_string(eq->function(this->c)) + ",");
    if(index != 0){
        this->csvLog.append(std::to_string(this->getError()));
    }
    this->csvLog.append("\n");
}
