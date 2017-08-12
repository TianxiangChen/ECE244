/* 
 * File:   Resistor.h
 * Author: JC and VB
 *
 * Created on October 6, 2013, 1:01 PM
 */

#ifndef RESISTOR_H
#define RESISTOR_H

#include <string>
#include <iostream>
using namespace std;

class Resistor
{
private:
   double resistance; // resistance (in Ohms)
   string name; // C++ string holding the label
   int endpointNodeIDs[2]; // IDs of nodes it attaches to

public:
   Resistor(int rIndex_,string name_,double resistance_,int endpoints_[2]);
   // rIndex_ is the index of this resistor in the resistor array
   // endpoints_ holds the node indices to which this resistor connects

   ~Resistor();

   string getName() const; // returns the name
   double getResistance() const; // returns the resistance

   void setResistance (double resistance_);

   // you *may* create either of the below to print your resistor
   void print ();
   friend ostream& operator<<(ostream&,const Resistor&);
};

ostream& operator<<(ostream&,const Resistor&);

#endif	/* RESISTOR_H */

