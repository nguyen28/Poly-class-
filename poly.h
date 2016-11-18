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
//  Created by Nguyen Nguyen on 11/4/16.
//  Copyright © 2016 Nguyen Nguyen. All rights reserved.
//  graphm.cpp
//  Lab3
//Lab 3 is about Implementing Dijskra's shortest path algorithm. It reads in a file given
//in the order of the total destinations, destination's name, numbered respectively,
//it's connected path and the weight. Then the shortest path is fonud for each destination to
//all other destinations. Printing options can be for only one destination or for all options.

#include "graphm.h"
#include "nodedata.h"

//*************************Constructor*****************************//
//Sets Tabletype T to set all, dist to infinity,
//all visited to false and all paths to 0.
//*****************************************************************//

GraphM::GraphM()
{
    this->size=0;
    for(int i=1; i<MAXNODES; i++)
    {
        for(int j=1; j<MAXNODES; j++)
        {
            C[i][j]=INT_MAX;
            T[i][j].dist=INT_MAX;
            T[i][j].path=0;
            T[i][j].visited=false;
        }
    }
}

//*************************buildGraph*****************************//
//builds up graph node info and adjacenct matrix of edges between each
//node reading from a data file
//*****************************************************************//

void GraphM::buildGraph(istream& inFile)

{
    int fromPath, toPath, dist=0;
    string locationName= "";
    inFile >> size;
    inFile.get();
    
    for(int i=1; i <=size; i++)
    {
        data[i].setData(inFile);
        
    }
    
    for(int a=1; a <=size; a++)
    {
        inFile >> fromPath >> toPath >> dist;
        
        if (inFile.eof())
        {
            break;
        }
        if(fromPath == 0 && toPath ==0)
        {
            break;
        }
        
        C[fromPath][toPath]=dist;
    }
}


//*************************insert***********************************//
// insert an edge into graph between 2 given nodes
//******************************************************************//

void GraphM::insertEdge(int insertFrom, int insertTo, int distCost)
{
    if(insertFrom >0 && insertTo >0 && distCost >0)
    {
        C[insertFrom][insertTo]=distCost;
    }
}

//**************************remove***********************************//
//remove an edge from graph 2 given nodes
//*******************************************************************//

void GraphM::removeEdge(int removeFrom, int removeTo)
{
    //make sure that the removeFrom and removeTo is within the right boundaries
    if(removeFrom <=this->size && removeFrom >0 && removeTo <=this->size &&removeTo>0)
    {
        C[removeFrom][removeTo]=INT_MAX; //reset the data to INT_MAX
    }
}

//***********************Shortest Path***********************************//
//Finds the shortest path between every node to every other node in the
//graph, TableType T is updated with shortest path info
//****************************************************************//

void GraphM::findShortestPath()
{
    
    int visited=-1;
    int current=0;
    
    for(int source= 1; source<=size;source++)
    {
        T[source][source].dist=0;
        //T[source][source].visited=true;
        
        for(int to=1; to<=size; to++)
        {
            if(C[source][to] != INT_MAX){
                T[source][to].dist=C[source][to];
                T[source][to].path=source;
            }
        }
        
        while(visited != 0){
            visited=0;
            for(int to=1; to <=size; to++) //looking for closest child
            {
                if((T[source][to].visited==false) && (C[source][to]!=INT_MAX))
                {
                    current=C[source][to];
                    visited=to;
                }
            }
            
            if(visited==0){
                break;
            }
            
            T[source][visited].visited=true;
            
            for(int neighbors=1; neighbors<=size; ++neighbors){
                if(visited == neighbors || (C[visited][neighbors]==INT_MAX)){
                    continue;
                }
                if(T[source][neighbors].visited ==true){
                    continue;
                }
                if(T[source][neighbors].dist > (T[source][visited].dist + C[visited][neighbors]))
                {
                    T[source][neighbors].dist = T[source][visited].dist + C[visited][neighbors];
                    T[source][neighbors].path = visited;
                }
            }
        }
    }
}

//***********************Display ALL***********************************//
//Displays the cost and path from every node to every other node.
//******************************************************************//

void GraphM::displayAll()
{
    //Prints out the top line
    cout << "Description" << setw(20) << "From node" << setw(10) << "To node"
    << setw(15) << "Dijkstra's" << setw(5) << "Path" << endl;
    
    for(int fromPath=1; fromPath <=size; fromPath++)
    {
        cout << data[fromPath] << endl;
        
        for(int toPath=1; toPath <=size; toPath++)
        {
            if (T[fromPath][toPath].dist != 0)
            {
                cout << setw(27) << fromPath;   // print from node
                cout << setw(10) << toPath;     // print to node
                
                if((T[fromPath][toPath].dist > 0) && (T[fromPath][toPath].dist < INT_MAX))
                {
                    cout << setw(25) <<fromPath << setw(10) << toPath;
                    cout << setw(15) << T[fromPath][toPath].dist << setw(5);
                    // findPath(fromPath, toPath); //calling helper function to get the path
                    cout << endl;
                    
                }else{
                    cout << setw(15) << "---" << endl;
                }
            }
        }
    }
    cout << endl;
}

//***********************display***********************************//
//displays the shortest distance with path info between the from path
//and the toPath.
//****************************************************************//

void GraphM::display(int fromPath, int toPath){
    
    if (T[fromPath][toPath].dist != INT_MAX)    // adjacent node check
    {
        cout << setw(7) << fromPath << setw(7) << toPath;   // print node from and to data
        cout << setw(12) << T[fromPath][toPath].dist << setw(15); // print distance
        
        helpGetPath(fromPath, toPath); // call helper
        cout << endl;
        
        // findData(fromPath, toPath); // call helper
    }
    else    // no adjacent node
    {
        cout << setw(15) << "--fsfsdfd--" << endl;
    }
    
    helpGetData(fromPath,toPath);
    cout << endl;
    
}

//***********************helper function***********************************//
//helps recursively call and get the path from one path to another
//****************************************************************//

void GraphM::helpGetPath(int fromPath, int toPath)
{
    if(fromPath != toPath){
        if(T[fromPath][toPath].path!=0){
            helpGetPath(fromPath, T[fromPath][toPath].path);
        }
    }
    cout << toPath << "";
    // cout << data[T[fromPath][toPath].path] << " " << endl;
}

//***********************Find the Path***********************************//
//Helper function that will from the path
//****************************************************************//
void GraphM::findPath(int fromPath, int toPath)
{
    if (T[fromPath][toPath].dist == INT_MAX)
    {
        return; // no path
    }
    
    if (fromPath == toPath)
    {
        cout << toPath << " ";  // print data
        
        return;
    }
    
    int pathData = toPath; // assign to path to pathData
    findPath(fromPath, toPath = T[fromPath][toPath].path);
    
    cout  << pathData << " ";   // print path
}

//***********************Find the Path***********************************//
//Helper function that will from the path
//****************************************************************//

void GraphM::helpGetData( int fromPath, int toPath)
{
    if (fromPath != toPath && (T[fromPath][toPath].path != 0)){
        helpGetData(fromPath, T[fromPath][toPath].path); //Recursive call to find previous
    }
    
    cout << data[T[fromPath][toPath].path] << endl; //Print path data (description)
}


