/* 
 * File:   Node.h
 * Author: JC and VB
 *
 * Created on October 6, 2013, 12:58 PM
 */

#ifndef NODE_H
#define NODE_H

#define MAX_RESISTORS_PER_NODE 5
#include <string>
#include <iostream>
#include <iomanip>
#include "Resistor.h"
using namespace std;

class Node
{
private:
    
   int numRes; // number of resistors currently connected
   int resIDArray[MAX_RESISTORS_PER_NODE]; // stores the index of each resistor connected

public:
   Node();
   ~Node();

   // Updates resIDArray to show the resistor in position rIndex in
   // the resistor array is now connected to this node.
   // Returns true if successful
   bool addResistor (int rIndex); 

   int getResNum() const; // returns the numRes
   int getIndex(int NodeNum) const; //return the index
   // prints the whole node
   // nodeIndex is the position of this node in the node array.
   void printNode(int nodeid, Resistor *res);
};

#endif	/* NODE_H */

