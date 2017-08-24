/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ResistorList.h
 * Author: tianxiangchen
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

using namespace std;

class ResistorList
{
private:
    Resistor *head;

public:

   ResistorList();
   ~ResistorList();

   void Insert(string name_, double resistance_, int endpoint0, int endpoint1);
   bool Delete(string name_);
   bool Modify(string name_, double resistance_);
   bool Print(string name);
   Resistor *Find(string name_);
  
};

#endif /* RESISTORLIST_H */

