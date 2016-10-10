//  poly.cpp
//  Lab1
//  Created by Nguyen Nguyen on 10/4/16.
//
//****************************poly implementation*******************************\\
//Creates a pointer that points dynamically aloocated arrays of polynomials where
//the current exponent is the index of each array, and the number in that index is
//the coefficient.
// Contains constructors, assignment overloads and input/output overloads
//**************************************************************************\\

#include "poly.h"
using namespace std;

//******************************Constructors********************************\\

//**************************************************************************\\
//Create a polynomial with no parameters which will set a new array with 0
//as the initial coefficient
//**************************************************************************\\

Poly::Poly()
{
    this->arraySize=1;
    polyArray= new int[this->arraySize];
    polyArray[0]=0;
}
//**************************************************************************\\
//Create a polynomial array that takes in 1 parameters which will be the coeff, which will
//set a new array with initial size of 1, and added in the coefficient.
//**************************************************************************\\

Poly::Poly(int coeff)
{
    
    this->arraySize=1;
    polyArray= new int[this->arraySize];
    polyArray[0]=coeff;
}

//**************************************************************************\\
//Create a polynomial array that takes in 2 parameters which will set a new array
//with initial size of exponent+1, and added in the coefficient in to that last array spot
//**************************************************************************\\

Poly::Poly(int coeff, int exponent)
{
    
    this->arraySize=exponent+1;
    polyArray= new int[this->arraySize];
  
    for(int i =0; i <this->arraySize;i++)
    {
        polyArray[i]=0;
    }
    polyArray[exponent]=coeff;
}

//**************************************************************************\\
//Create deep copy of that polynomial
//**************************************************************************\\

Poly::Poly(const Poly &a)
{
    this->polyArray =new int[a.arraySize];
    
    for(int i=0; i<a.arraySize; i++)
    {
        this->polyArray[i]=a.polyArray[i];
    }
}

//*******************************Destructor**********************************\\
//Deletes the array and makes it null
//**************************************************************************\\

Poly::~Poly()
{
    delete[] polyArray;  //deletes pointer and nulls out the array
    polyArray = NULL;
}

//*******************************Getters and Setters**********************************\\

//*******************************Getter**********************************\\
//Get the Coefficient inside the requested indexed exponent. Checked the request is accurate
//***********************************************************************\\

int Poly::getCoeff(int exponent) const
{
 if(exponent >= 0 && exponent <this->arraySize) //check if request is illegal or not in the range
 {
     return  polyArray[exponent];
 }
    else
    {
        return 0;
    }
}

//****************************Setter******************************************\\

void Poly::setCoeff(int coeff, int exponent){
    if (exponent >= 0) //check range
    {
        int newSize = exponent +1;
        if ((newSize) > this->arraySize) //check to see which the new array should be
        {
            Poly newArray(0,newSize);
            
            for (int i = 0; i < this->arraySize; i++)
            {
                newArray.polyArray[i] = this->polyArray[i]; //Copy the current array
            }
            for (int j = this->arraySize; j < (newSize); j++)
            {
                newArray.polyArray[j] = 0;
            }
            
            newArray.polyArray[exponent] = coeff;   //assign the entered exponent with the right coeff
            
             }
        else
        {
            this->polyArray[exponent] = coeff; //set coeff value in specified location
        }
    }
}
///****************************Assignment Overloads*************************\\

//****************************Addition Overload*******************************\\
//Overloads the genral add sign to make it work for polynomials
//**************************************************************************\\

Poly Poly::operator+(const Poly &a) const
{
   
    if(this->arraySize > a.arraySize)  //if this array is bigger than the one being added
    {
        Poly sumPoly(0,this->arraySize);  //start new array with the current size
       
        for(int i=0; i<a.arraySize;i++)
        {
            sumPoly.polyArray[i]=this->polyArray[i]+a.polyArray[i];
            //add the coeff in each exponent spot
        }
        
        for(int moveRest = a.arraySize;moveRest < this->arraySize; moveRest++)
            //then go from a to this and just move from current to the new array
        {
            sumPoly.polyArray[moveRest]=this->polyArray[moveRest];
        }
         return sumPoly;
    }
    else  //do same like above but this time a.array size is bigger
    {
        Poly sumPoly(0,a.arraySize);
        
        for(int i=0; i<this->arraySize;i++)
        {
            sumPoly.polyArray[i]=this->polyArray[i]+a.polyArray[i];
        }
        
        for(int moveRest = this->arraySize;moveRest < a.arraySize; moveRest++)
        {
            sumPoly.polyArray[moveRest]=a.polyArray[moveRest];
        }
         return sumPoly;
    }
}

//****************************subtraction Overload*******************************\\
//Overloads the genral subtract sign to make it work for polynomials
//**************************************************************************\\

Poly Poly::operator-(const Poly &a) const
{
    if(this->arraySize > a.arraySize) //If current array size is bigger than create new
    {     //array with the current size because doing the subtraction
        Poly subtractPoly(0,this->arraySize);
        
        for(int i=0; i<a.arraySize;i++)
        {
            subtractPoly.polyArray[i]=this->polyArray[i]-a.polyArray[i];
        }
        
        for(int moveRest = a.arraySize;moveRest < this->arraySize; moveRest++)
        {
            subtractPoly.polyArray[moveRest]=this->polyArray[moveRest];
        }
        return subtractPoly;
    }
    else  //if the current isn't bigger than the new addition then just continue and subtract
    {
        Poly subtractPoly(0,a.arraySize);
        
        for(int i=0; i<this->arraySize;i++)
        {
            subtractPoly.polyArray[i]=this->polyArray[i]-a.polyArray[i];
        }
 //Once complete then the difference of the current array, complete the rest into the new array
        for(int moveRest = this->arraySize;moveRest < a.arraySize; moveRest++)
        {
            subtractPoly.polyArray[moveRest]=a.polyArray[moveRest];
        }
        return subtractPoly;
    }
}
//****************************multiplication Overload*******************************\\
//Overloads the general multiplication sign to make it work for polynomials
//**************************************************************************\\

Poly Poly::operator*(const Poly &a) const
{
    int newArraySize =(this->arraySize +a.arraySize);
    Poly multArray(0,newArraySize);
    
    for(int i=0; i < this->arraySize; i++) //deal with outside coeff
    {
        if(this->polyArray[i] !=0){   //if it's 0's then next
            for(int j=0; j< a.arraySize; j++)   //deal with inside terms
            {
                if(a.polyArray[j]!=0)  //if it's 0's then skip
                {
                    multArray.polyArray[i+j]+= (this->polyArray[i] *a.polyArray[j]); //add them together with like exponents into the new exponent position
                }
            }
        }
    }
        return multArray;
}

//Assignment Operator
    
Poly& Poly::operator=(const Poly&a)
{
    if(&a != this)
    {
        delete[] this->polyArray;
        this->polyArray = NULL;
        this->arraySize = a.arraySize;
        this->polyArray= new int[this->arraySize];
        
        for(int i=0; i<this->arraySize; i++)
        {
            this->polyArray[i]=a.polyArray[i];
        }
    }
    return *this;
}

//Assignment Operators

Poly& Poly::operator+=(const Poly &a)
{
    *this =*this+ a;
    return *this;
}


Poly& Poly::operator-=(const Poly &a){
    *this =*this -a;
    return *this;
}

Poly& Poly::operator*=(const Poly &a){
    *this =*this * a;
    return *this;
}

//equality and inequality operators
bool Poly::operator==(const Poly &a) const
{
    if(this-> arraySize != a.arraySize)
    {
        return false;
    }
    else
    {
        for(int i=0; i <this->arraySize; i++)
        {
            if(this->polyArray[i]!=a.polyArray[i])
            {
                return false;
            }
        }
    }
    return true;
}

bool Poly::operator!=(const Poly &a) const
{
    return !(*this == a);
}
//****************************sInput/Output Mutators*******************************\\

//******************************Output Mutator**************************************\\

ostream& operator<<(ostream &output, const Poly &a){
    
    bool isEmpty = true; //Flag to indicate empty array
    
    for(int i = a.arraySize - 1; i >= 0; --i)
    {
        if(a.polyArray[i] != 0)
        {
            isEmpty = false;
            output << " ";
        }
        else continue;
        if (a.polyArray[i] > 0)
        {//Display "+" if positive coeff
            output << "+";
        }
       // else if(a.polyArray[i] <0)
       // {
         //   output << "-"; //Display "-" if negative
        //}
        if(i == 1)
        {//Chooses correct output for polynomial
            output  << a.polyArray[i] << "x";
        }
        else if (i == 0)
        {
            output  << a.polyArray[i];
        }
        else
        {
            output  << a.polyArray[i] << "x^" << i;
        }
    }

    if (isEmpty)
    {   //If empty polynomial display " 0"
        output << " 0";
    }
    return output;
}

//****************************Input Mutator**********************************************\\

istream& operator>>(istream &input, Poly &a){
    int coeff;
    int exponent;
    
    while(input >> coeff >> exponent) //Until input stops
    {
        if ((coeff == -1) && (exponent == -1)) //checking the -1, -1 for exiting
        {
            break;
        }
        a.setCoeff(coeff,exponent); //set the new value for each pair of int
    }
    return input;
}


