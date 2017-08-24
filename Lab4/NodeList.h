/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NodeList.h
 * Author: tianxiangchen
 *
 * Created on August 23, 2017, 11:41 PM
 */

#ifndef NODELIST_H
#define NODELIST_H

#include <string>
#include <iostream>
#include <iomanip>
#include "Node.h"
#include "err_display.h"

using namespace std;

class NodeList
{
private:
    Node *head;

public:

   NodeList();
   ~NodeList();

   void Insert(string name_, double resistance_, int endpoint0, int endpoint1);
   bool Delete(string name_);
   bool Modify(string name_, double resistance_);
   bool Print(string name);
   Resistor *Find(string name_);

#endif /* NODELIST_H */

