/* 
 * File:   Parser.h
 * Author: Tianxiang Chen
 *
 * Created on August 25, 2017, 4:33 PM
 */

#ifndef PARSER_H
#define PARSER_H

#include <sstream>
#include <iostream>
#include <string>
#include <iomanip>
#include "TreeDB.h"

using namespace std;

void Parser();

void insert(stringstream &lineStream, TreeDB *tree);
void find(stringstream &lineStream, TreeDB *tree);
void remove(stringstream &lineStream, TreeDB *tree);
void printall(TreeDB *tree);
void printprobes(stringstream &lineStream, TreeDB *tree);
void removeall(TreeDB *tree);
void countactive(TreeDB *tree);
void updatestatus(stringstream &lineStream, TreeDB *tree);

bool active_converter(string status);

#endif /* PARSER_H */