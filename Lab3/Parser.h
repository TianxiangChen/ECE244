/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Parser.h
 * Author: Tianxiang Chen
 *
 * Created on August 21, 2017, 1:21 PM
 */

#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include "Node.h"
#include "Resistor.h"

#define UppBound 5000
#define LowBound 0
using namespace std;


void insertR(stringstream &lineStream, Node *node, Resistor *res, int &res_index, 
        const int MaxNodeNumber, const int MaxResistors);
void modifyR(stringstream &lineStream, Resistor *res, int res_index);
void printR(stringstream &lineStream, Resistor *res, int res_index);
void printNode(stringstream &lineStream, Resistor *res, Node *node, const int MaxNodeNumber);
void deleteR(stringstream &lineStream, Resistor *&res, Node *&node, 
        const int MaxNodeNumber, const int MaxResistors, int &res_index);
void maxVal(stringstream &lineStream,Node *&node, Resistor *&res, int &MaxNodeNumber
, int &MaxResistors, int &res_index);

//valid checking
bool NameChecking(stringstream &lineStream, string &name);
bool NameChecking2(stringstream &lineStream, string &name);//For printR
bool NameChecking3(stringstream &lineStream, string &name);//For deleteR
bool NameChecking4(stringstream &lineStream, string &name, const int MaxNodeNumber
, int &nodeid);//For printNode
bool ResChecking(stringstream &lineStream, double &resistance);
bool ResChecking2(stringstream &lineStream, double &resistance);//For modifyR
bool NodeChecking(stringstream &lineStream, int &nodeid, const int MaxNodeNumber);
bool Node2Checking(stringstream &lineStream, int &nodeid1, int &nodeid2,
        const int MaxNodeNumber);
bool maxValNumCheching(stringstream &lineStream, int &MaxNodeNumber, int &MaxResistors);
//bool NodeNumChecking(stringstream &lineStream, int &num);//For maxVal
//bool ResNumChecking(stringstream &lineStream, int &num);//For maxVal
bool TooFewArguChecking(stringstream &lineStream);
bool TooManyArguChecking(stringstream &lineStream);


//error printing function
void Print_InvalidCom();
void Print_InvalidArgu();
void Print_NegRes();
void Print_NodeExceed(const int nodeid, const int MaxNodeNumber);
void Print_NoAll();
void Print_SameTerminal(const int nodeid);
void Print_TooManyArgu();
void Print_ToofewArgu();
void Print_NegMaxVal();
void Print_Array_Full();
void Print_Node_Full();
void Print_Res_Not_Found(string name);
void Print_Duplicate(string name);

int Parser();

#endif /* PARSER_H */

