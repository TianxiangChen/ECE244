/* 
 * File:   Node.h
 * Author: JC and VB
 *
 * Created on October 6, 2013, 12:58 PM
 */

#ifndef NODE_H
#define NODE_H

#include <string>
#include <iostream>
#include <iomanip>
#include "Resistor.h"
#include "ResAddrList.h"
using namespace std;

class Node
{
private:
    
   int ID;//node ID
   int numRes; // number of resistors currently connected
   bool set;
   bool converge;//if the change for solve is smaller than MIN ITERATION CHANGE
   double voltage;
   ResAddrList *head;
   Node *next;

public:
   Node();
   ~Node();
   Node(int ID_, Resistor *addr);

   //bool addResistor (int rIndex); 

   int getResNum() const; // returns the numRes
   int getID () const;
   Node *getNext() const;
   double getVoltage() const;
   ResAddrList* getHead() const;
   bool IsSet() const;
   bool IsConverge() const;
   
   void setID(int nodeid);
   void addResNum();
   void addRes(Resistor *addr);
   void deleteRes(Resistor *addr);
   void setNext(Node *next_);
   void setSet();
   void setUnset();
   void setVoltage(double voltage_);
   void unsetVoltage();
   void setResNum(int num);
   void setConverge();
   void setDiverge();
   void printNode();
   void clear();
};

#endif	/* NODE_H */

