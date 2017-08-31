/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   err_display.h
 * Author: tianxiangchen
 *
 * Created on August 23, 2017, 6:53 PM
 */

#ifndef ERR_DISPLAY_H
#define ERR_DISPLAY_H

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;


//error printing function
void Print_InvalidCom();
void Print_InvalidArgu();
void Print_NegRes();
void Print_NodeExceed(const int nodeid);
void Print_NoAll();
void Print_SameTerminal(const int nodeid);
void Print_TooManyArgu();
void Print_ToofewArgu();
void Print_Res_Not_Found(const string name);
void Print_Duplicate(const string name);
void Print_NodeNotFound(const int nodeid);
void Print_SolveNoSet();

#endif /* ERR_DISPLAY_H */

