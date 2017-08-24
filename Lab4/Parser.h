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
#include "ResistorList.h"
#include "Resistor.h"

#define LowBound 0
using namespace std;


void insertR(stringstream &lineStream, ResistorList *res_head);
void modifyR(stringstream &lineStream, ResistorList *res_head);
void printR(stringstream &lineStream, ResistorList *res_head);
void printNode(stringstream &lineStream, Resistor *res, Node *node, const int MaxNodeNumber);
void deleteR(stringstream &lineStream, ResistorList *res_head);

//valid checking
bool NameChecking(stringstream &lineStream, string &name);
bool NameChecking2(stringstream &lineStream, string &name);//For printR
bool NameChecking3(stringstream &lineStream, string &name);//For deleteR
bool NameChecking4(stringstream &lineStream, string &name, int &nodeid);//For printNode
bool ResChecking(stringstream &lineStream, double &resistance);
bool ResChecking2(stringstream &lineStream, double &resistance);//For modifyR
bool NodeChecking(stringstream &lineStream, int &nodeid);
bool Node2Checking(stringstream &lineStream, int &nodeid1, int &nodeid2);
bool TooFewArguChecking(stringstream &lineStream);
bool TooManyArguChecking(stringstream &lineStream);

int Parser();

#endif /* PARSER_H */

