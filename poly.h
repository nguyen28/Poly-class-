//  poly.hpp
//  Lab1
//  Created by Nguyen Nguyen on 10/4/16.
//
//****************************poly header*******************************\\
//Creates a poly class with private arraySize and a pointer that points dynamically aloocate
//arrays of polynomials where the current exponent is the index of each array, and the
//number in that index is the coefficient.
// Contains constructors, assignment overloads and input/output overloads
//**************************************************************************\\

#ifndef poly_hpp
#define poly_hpp
#include <stdio.h>
#include <iostream>
using namespace std;

//Constructors
class Poly{
private:
    int arraySize;
    int* polyArray;

public:

    //Constructors
    Poly(int coeff, int exponent);
    Poly(int coeff);
    Poly();
    Poly(const Poly &a);
    ~Poly();
    
    //getters and setters
    int getCoeff(int exponent) const;
    void setCoeff(int coeff, int exponent);
    
    //Assignment overloads
    Poly operator+(const Poly &a) const;
    Poly operator-(const Poly &a) const;
    Poly operator*(const Poly &a) const;
    
    //Assignment Operator
    Poly& operator=(const Poly &a);
    
    //Assignment Operators
    Poly& operator+=(const Poly &a);
    Poly& operator-=(const Poly &a);
    Poly& operator*=(const Poly &a);
    
    //equality and inequality operators
    bool operator==(const Poly &a) const;
    bool operator!=(const Poly &a) const;

    //Ostream and iStream overloads
    friend ostream& operator<<(ostream& output, const Poly &a);
    friend istream& operator>>(istream &input, Poly &a);
};


#endif /* poly_hpp */
