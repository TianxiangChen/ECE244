/* 
 * File:   Node.h
 * Author: JC and VB
 *
 * Created on October 6, 2013, 12:58 PM
 */

#ifndef NODE_H
#define NODE_H

#define MAX_RESISTORS_PER_NODE 5


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

   // prints the whole node
   // nodeIndex is the position of this node in the node array.
   void print (int nodeIndex); 

};

#endif	/* NODE_H */

