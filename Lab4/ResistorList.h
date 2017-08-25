/* 
 * File:   ResistorList.h
 * Author: Tianxiang Chen
 *
 * Created on August 23, 2017, 5:04 PM
 */

#ifndef RESISTORLIST_H
#define RESISTORLIST_H

#include <string>
#include <iostream>
#include <iomanip>
#include "Resistor.h"
#include "err_display.h"
#include "NodeList.h"

using namespace std;

class ResistorList
{
private:
    Resistor *head;

public:

   ResistorList();
   ~ResistorList();

   void Insert(string name_, double resistance_, int endpoint0, int endpoint1, NodeList *nlist);
   bool Delete(string name_, NodeList *nlist);
   bool Modify(string name_, double resistance_);
   bool Print(string name);
   Resistor *Find(string name_);
  
};

#endif /* RESISTORLIST_H */

