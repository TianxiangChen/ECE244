/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "err_display.h"

//Error Printing

void Print_InvalidCom(){
    cout<<"Error: invalid command"<<endl;
}
void Print_InvalidArgu(){
    cout<<"Error: invalid argument"<<endl;
}
void Print_NegRes(){
    cout<<"Error: negative resistance"<<endl;
}
void Print_NodeExceed(const int nodeid){
    cout<<"Error: node "<<nodeid<<" is smaller than 0"<<endl;
}
void Print_NoAll(){
    cout<<"Error: resistor name cannot be the keyword \"all\""<<endl;
}
void Print_SameTerminal(const int nodeid){
    cout<<"Error: both terminals of resistor connect to node "<<nodeid<<endl;
}
void Print_TooManyArgu(){
    cout<<"Error: too many arguments"<<endl;
}
void Print_ToofewArgu(){
    cout<<"Error: too few arguments"<<endl;
}
void Print_Res_Not_Found(const string name){
    cout<<"Error: resistor "<<name<<" not found"<<endl;
}
void Print_Duplicate(const string name){
    cout<<"Error: resistor "<<name<<" already exists"<<endl;
}