/* 
 * File:   ResAddrList.h
 * Author: Tianxiang Chen
 *
 * Created on August 24, 2017, 2:48 PM
 */

#ifndef RESADDRLIST_H
#define	RESADDRLIST_H

#include <string>
#include <iostream>
#include <iomanip>
#include "ResAddr.h"

using namespace std;

class ResAddrList
{
private:
    ResAddr *head;

public:

   ResAddrList();
   ~ResAddrList();

   void Insert(Resistor *Addr);
   bool Delete(Resistor *Addr);
   void Print();
   ResAddr* getHead() const;


};


#endif	/* RESADDRLIST_H */

