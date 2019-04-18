/**
 * Wilson Gip
 * Numerical Methods - Programming Project 3
 * 12/1/2018
 */
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <math.h>
#include <iomanip>

using namespace std;

/** Return the size of array y, n * ( n + 1 ) / 2*/
int getSize(int n);
/** Solve the divided difference table*/
void solveDifTable(const float* x, float* y, int n);
/** Print the divided difference table*/
void printTable(const float* x, const float* y, int n);
/** Multiply each element of poly by a constant*/
void scalePoly(const float& constant, float* poly, int size);
/** Return the denominator for a single lagrange's poly*/
float getDenominator(const float* x, int index, int size);
/** Read a string and return an array of float*/
float* getStrToArr(string line, int& inSize, bool isOutput);
/** Multiply 2 polynomials*/
float* multiply(const float* a, const float* b, int m, int n);
/** Get the multiplied polynomials for an interpolating polynomial section*/
float* getMultipliedPoly(const float* x, int& inSize, int index);
/** Add 2 polynomials*/
float* add(const float* a, const float* b, int m, int n);
/** Get the string of the interpolation polynomial from the divided difference table*/
string getInterPoly(float* x, float* y, int size);
/** Get the polynomial (x - xi) etc*/
string getPoly(float* x, int index);
/** Return a string with a setPrecision for the float input*/
string getPrecise(float f);
/** Get the simplified polynomial*/
string getSimplified(const float* x, const float* y, int size);
/** Generate the array into a polynomial*/
string generateArrToPoly(const float* arr, int size);
/** Duplicate a string for x amount of times and return it*/
string duplicate(const string& dup, int amount);
/** Get the Lagrange's form */
string getLagrangePoly(const float* x, const float* y, int size);
/** Get the polynomial for a single set of Lagrange's*/
string getLagrangeSinglePoly(const float* x, int index, int size);

int main()
{
    string filename = "";
    cout << "Enter filename: ";
    cin >> filename;

    ifstream infile;
    infile.open(filename);

    /**ifstream's good(), is_open(), fail() does not work in executable, so I cannot check if file truly exists*/

    string line;
    int size;

    getline(infile, line);
    float* x = getStrToArr(line, size, false);

    getline(infile, line);
    float* y = getStrToArr(line, size, true);


    solveDifTable(x, y, size);
    printTable(x, y, size);

    cout << "Interpolating Polynomial (Newtons): \n" << getInterPoly(x, y, size) << "\n\n";
    cout << "Lagrange Form: \n" << getLagrangePoly(x, y, size) << "\n\n";
    cout << "Simplified Polynomial: \n" << getSimplified(x, y, size) << "\n\n";

    delete [] x;
    delete [] y;
    infile.close();
    system("PAUSE");
    return 0;
}

string getLagrangePoly(const float* x, const float* y, int size)
{
    string poly = "L(x) = ";
    for (int i = 0; i < size; ++i) {
        poly.append( "(" + getLagrangeSinglePoly(x, i, size) + " / " + getPrecise(getDenominator(x, i, size) * y[i]) + ")");
        poly.append(i % 2 && i != 0 ? "\n" : "");
        poly.append(i < size - 1 ? " + " : "" );
    }
    return poly;
}

string getLagrangeSinglePoly(const float* x, int index, int size)
{
    string poly;
    int zeros = 0;
    for (int i = 0; i < size; ++i) {
        if(i != index){
            if(x[i] != 0.0){
                poly.append("(x");
                poly.append(x[i] < 0.0 ? "+" : "-");
                poly.append(getPrecise(abs(x[i])));
                poly.append(")");

            }else{ ++zeros; }
        }
    }
    for (int i = 0; i < zeros; ++i) {
        poly.append("x");
    }
    return poly;
}

float getDenominator(const float* x, int index, int size)
{
    float product = 1.0;
    float dif;
    for (int i = 0; i < size; ++i) {
        if(i != index){
            dif = x[index] - x[i];
            product *= dif;
        }
    }
    return product;
}

float* add(const float* a, const float* b, int m, int n)
{
    int size = max(m, n);
    auto* sum = new float[size];

    for (int i = 0; i < m; i++){
        sum[i] = a[i];
    }

    for (int i=0; i < n; i++){
        sum[i] += b[i];
    }

    return sum;
}

float* multiply(const float* a, const float* b, int m, int n)
{
    int size = m + n - 1;
    auto* prod = new float[size];

    for (int i = 0; i < size; i++){
        prod[i] = 0;
    }

    for (int i=0; i < m; i++){
        for (int j=0; j < n; j++){
            prod[i+j] += a[i]*b[j];
        }
    }

    return prod;
}

string getSimplified(const float* x, const float* y, int size)
{
    float arr[size];
    for (int i = 0, idx = 0; i < size; idx += (size-i), ++i) {
        arr[i] = y[idx];
    }

    int curSize = 0, prevSize = 0;
    float* poly = getMultipliedPoly(x, curSize, 0);
    float* deleteMe = nullptr;
    scalePoly(arr[0], poly, curSize);

    for (int i = 1; i < size; ++i) {
        prevSize = curSize;
        float *nextPoly = getMultipliedPoly(x, curSize, i);

        // Scale the array
        scalePoly(arr[i], nextPoly, curSize);

        deleteMe = poly;
        poly = add(nextPoly, poly, curSize, prevSize);
        curSize = max(prevSize, curSize);

        delete [] nextPoly;
        delete [] deleteMe;
    }

    string polyString = "F(x) = ";
    polyString += generateArrToPoly(poly, curSize);
    delete [] poly;
    return polyString;
}

void scalePoly(const float& constant, float* poly, int size)
{
    for (int i = 0; i < size; ++i) {
        poly[i] *= constant;
    }
}

float* getMultipliedPoly(const float* x, int& inSize, int index)
{
    bool isIdxZero = (index == 0);
    inSize = (isIdxZero? 1 : 2); // m + n - 1
    auto* arrA = new float[inSize];
    float* deleteMe = nullptr;

    arrA[0] = (isIdxZero ? 1 : (x[0] * (float)-1.0));
    if(isIdxZero){ return arrA; }
    arrA[1] = 1.0;

    float arrNext[2];
    for (int i = 1; i < index; ++i, ++inSize) {
        arrNext[0] = (x[i] * (float)-1.0);
        arrNext[1] = 1.0;

        deleteMe = arrA;
        arrA = multiply(arrA, arrNext, inSize, 2);

        delete [] deleteMe;
    }

    return arrA;
}

string generateArrToPoly(const float* arr, int size)
{
    string poly;
    for (int i = size - 1; i >= 0; --i) {
        if(arr[i] != 0.0){
            float curAbs = abs(arr[i]);
            poly.append(i != size - 1 ? (arr[i] < 0.0 ? " - " : " + "): (arr[i] < 0.0 ? "-" : ""));
            poly.append((curAbs == 1.0 && i == 0) || curAbs != 1.0 ? getPrecise(curAbs) : "");
            if(i != 0){
                poly.append("x");
                if(i != 1) {
                    poly.append("^");
                    poly.append(to_string(i));
                }
            }
        }
    }
    return poly;
}

string getInterPoly(float* x, float* y, int size)
{
    string interPoly = "P(x) = ";
    int idx = 0;
    for (int i = 0; i < size; ++i) {
        interPoly.append(i != 0 ? (y[idx] < 0.0 ? " - " : " + "): (y[idx] < 0.0 ? "-" : ""));
        interPoly.append(getPrecise(abs(y[idx])));
        interPoly.append(getPoly(x, i));
        idx += (size - i);
    }
    return interPoly;
}

string getPoly(float* x, int index)
{
    string poly;
    for (int i = 0; i < index; ++i) {
        if(x[i] != 0.0){
            poly.append("(x");
            poly.append(x[i] < 0 ? "+" : "-");
            poly.append(getPrecise(abs(x[i])));
            poly.append(")");

        }else{
            poly.append("x");
        }
    }
    return poly;
}

string getPrecise(float f)
{
    stringstream ss;
    ss << fixed << setprecision(2) << f;
    return ss.str();
}

float* getStrToArr(string line, int& inSize, bool isOutput)
{
    int size = count(line.begin(), line.end(), ' ') + 1;
    if(isOutput){ size = getSize(size); }

    auto* arr = new float[size];
    for (int i = 0; i < size; ++i) {
        arr[i] = 0.0;
    }

    istringstream iss(line);
    float value;
    int i = 0;
    while (iss >> value){
        arr[i++] = value;
    }
    if(!isOutput){ inSize = i; }
    return arr;
}

int getSize(int n)
{
    return (n * (n + 1))/2;
}

void solveDifTable(const float* x, float* y, int n)
{
    int arrSize = getSize(n);
    for (int i = n, idx = 0, levelIdx = 0, level = 1; i < arrSize; ++i, ++idx, ++levelIdx) {
        y[i] = (y[idx+1] - y[idx])/(x[level+levelIdx] - x[levelIdx]);
        if((levelIdx+1) % (n-level) == 0){
            ++idx;
            ++level;
            levelIdx = -1;
        }
    }
}

void printTable(const float* x, const float* y, int n)
{
    string msg = "\nDivided Difference Table:";
    msg.append("\n" + duplicate("-", n * 12) + "\n");
    msg.append("x\t");
    for (int i = 0; i < n; ++i) {
        msg.append("f["+duplicate(",", i)+"]\t");
    }
    msg.append("\n" + duplicate("-", n * 12) + "\n");
    for (int i = 0; i < n; ++i) {
        int idx = i;
        msg.append(getPrecise(x[i]) + "\t");
        for (int j = 0; j < n-i; ++j) {
            msg.append(getPrecise(y[idx]) + "\t");
            idx += (n-j);
        }
        msg.append("\n");
    }

    cout << msg << endl;
}

string duplicate(const string& dupeThis, int amount) {
    string ret;
    for (int i = 0; i < amount; ++i) {
        ret += dupeThis;
    }
    return ret;
}
