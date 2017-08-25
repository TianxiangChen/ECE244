/* 
 * File:   ResAddr.h
 * Author: Tianxiang Chen
 *
 * Created on August 24, 2017, 2:37 PM
 */

#ifndef RESADDR_H
#define	RESADDR_H

#include <string>
#include <iostream>
#include <iomanip>
#include "Resistor.h"

using namespace std;

class ResAddr
{
private:
    Resistor *Addr;
    ResAddr *next;

public:
   
   ResAddr();
   ~ResAddr();
   ResAddr(Resistor *Addr_);
   
   Resistor* getResAddr() const;
   ResAddr* getNext() const;
   void setNext(ResAddr *next_);
};



#endif	/* RESADDR_H */

