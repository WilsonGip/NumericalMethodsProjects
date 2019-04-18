/*  Name: Wilson Gip
 *  Class: CS 3010 - Numerical Methods
 *  Project 1
 *  TTH 2:30pm - 3:45pm
 *
 * */
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "GaussPartialPivot.h"
#include "GaussJacobiSiedal.h"

void deleteMatrix(double** matrix, int size);
void getCoefAndB(double** matrix, int &size, double &error);
void getInfo(bool&, std::string&, int&, double&);

int main() {
    double error = 0.05;
    std::string fileName;
    bool read;
    int size;

    getInfo(read, fileName, size, error);

    double** matrix = new double*[size];
    for(int i = 0; i < size; i++){
        matrix[i] = new double[size+1];
    }

    if(read){
        // Unable to make a readFile() function.
        // Instantiating std::ifstream inFile in a function that is not main() will crash for no reason. Cannot find a fix.
        int coef, index = 0, col = 0;
        std::string line;
        std::ifstream inFile;
        inFile.open(fileName);
        if(!inFile.good()){
            std::cout << "Unable to open file!";
            exit(1);
        }
        while(std::getline(inFile, line)){
            std::istringstream iss(line);
            while(iss >> coef){
                if(index < size && col < size+1){
                    matrix[index][col] = (double) coef;
                }
                col++;
            }
            col = 0;
            index++;
        }
        inFile.close();
    }else{
        getCoefAndB(matrix, size, error);
    }

    std::cout << "Gaussian Elimination Scaled Partial Pivot\n";
    GaussPartialPivot *gauss = new GaussPartialPivot(matrix, size, size + 1);
    gauss->Gauss();
    std::cout << "Gaussian Elimination Scaled Partial Pivot\n";
    gauss->printX();

    GaussJacobiSiedal *gaussJS = new GaussJacobiSiedal(matrix, size, size + 1, error);
    std::cout << "Gauss Jacobi\n";
    gaussJS->Jacobi();

    std::cout << "Gauss Siedal\n";
    gaussJS->Siedal();
    deleteMatrix(matrix, size);
    delete gaussJS;
    delete gauss;
    system("PAUSE");
    return 0;
}

void deleteMatrix(double **matrix, int size){
    for(int i = 0; i < size; i++){
        delete [] matrix[i];
    }
    delete [] matrix;
}

void getCoefAndB(double** matrix, int &size, double &error){
    std::string message = "";
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size + 1; j++) {
            message = std::string("\nLinear Equation #" + std::to_string(i) +"\n");
            message += (j < size ? "Enter the X" + std::to_string(j + 1) + " coefficient:" : "Enter the B value: ");
            std::cout << message;
            std::cin >> matrix[i][j];
        }
    }
    system("CLS");
}

void getInfo(bool &read, std::string &fileName, int &size, double &error) {
    std::string ans;
    std::cout << "Do you want to read a file (y/n)? ";
    std::cin >> ans;

    if(read = (ans.at(0) == 'y')){
        std::cout << "Enter the filename: ";
        std::cin >> fileName;
    }

    std::cout << "Enter the matrix size: ";
    std::cin >> size;

    while(size > 10){
        std::cout << "Please enter a number smaller or equal to 10!" << std::endl;
        std::cin.clear();
        std::cout << "Enter the number of linear equations: ";
        std::cin >> size;
    }

    std::cout << "Enter the desired error: ";
    std::cin >> error;

    system("CLS");
}
