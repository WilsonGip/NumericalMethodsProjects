/**
 * Author: Wilson Gip
 * Project 2
 * Professor Amar Raheja
 * 11/9/2018
 */

#include <iostream>
#include <string>
#include <vector>
#include "EquationA.h"
#include "EquationB.h"
#include "EquationAB.h"
#include "Bisection.h"
#include "NewtonRaphson.h"
#include "Secant.h"

void menu();
void requestPoints(int numStart, EquationAB* eq, Methods* method, bool falsePos);
int main() {
    menu();
    return 0;
}

void menu(){
    EquationAB* eq;
    EquationAB* eqA = new EquationA();
    EquationAB* eqB = new EquationB();
    Bisection* bisection = new Bisection();
    NewtonRaphson* newton = new NewtonRaphson();
    Secant* secant = new Secant();
    std::string ans = "y";
    std::string selectFunc;
    while(ans.at(0) == 'y'){
        std::cout << "Please select a function: \n"
                    << "----------------------------\n"
                    << "1." << eqA->toString() << "\n"
                    << "2." << eqB->toString() << "\n"
                    << "----------------------------\n";
        std::cout << "Enter an option: ";
        std::cin >> selectFunc;
        if(selectFunc.at(0) != '1' && selectFunc.at(0) != '2'){ continue; }
        eq = (selectFunc.at(0) == '1' ? eqA : eqB);
        std::cout << "Bisection Method\n";
        requestPoints(2, eq, bisection, false);
        std::cout << "False Position Method\n";
        requestPoints(2, eq, bisection, true);
        std::cout << "Newton Raphson Method\n";
        requestPoints(1, eq, newton, false);
        std::cout << "Secant Method\n";
        requestPoints(2, eq, secant, false);
        std::cout << "Modified Secant Method\n";
        requestPoints(1, eq, secant, false);
        std::cout << "Try Again? y/n: ";
        std::cin >> ans;
    }

    delete eqA;
    delete eqB;
    delete bisection;
    delete newton;
    delete secant;
}

void requestPoints(int numStart, EquationAB* eq, Methods* method, bool falsePos){
    double input[numStart];
    for (int i = 0; i < numStart; ++i) {
        std::cout << "Enter starting point #" << i << ": ";
        std::cin >> input[i];
        std::cout << "\n";
    }

    if(numStart == 1){
        method->findRoot(input[0], eq);
    }else if(numStart == 2){
        method->findRoot(input[0], input[1], eq, falsePos);
    }
//    method->printLog();
}