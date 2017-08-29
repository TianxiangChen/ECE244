/* 
 * File:   NodeList.h
 * Author: Tianxiang Chen
 *
 * Created on August 23, 2017, 11:41 PM
 */

#ifndef NODELIST_H
#define NODELIST_H

#include <string>
#include <iostream>
#include <iomanip>
#include "Node.h"
#include "Resistor.h"
#include "err_display.h"
#include <cmath>
#define MIN_ITERATION_CHANGE 0.0001
using namespace std;

class NodeList
{
private:
    Node *head;

public:

   NodeList();
   ~NodeList();

   void Insert(int nodeid,Resistor *addr);
   void DeleteAll();
   bool Delete(int nodeid, Resistor *res_addr);
   void Print(string name, int nodeid);
   bool setV(int nodeid, double voltage);
   bool unsetV(int nodeid);
   void solve();
   
   void initialize_voltage();
   bool AllNodeConverge();

};
#endif /* NODELIST_H */

