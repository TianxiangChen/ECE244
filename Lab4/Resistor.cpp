/*
 * Resistor.cpp
 */
#include "Resistor.h"

Resistor::Resistor(string name_,double resistance_,int endpoint0, int endpoint1){
    name = name_;
    resistance = resistance_;
    endpointNodeIDs[0] = endpoint0;
    endpointNodeIDs[1] = endpoint1;
    next = NULL;
}

Resistor::Resistor(){
    ;
}

Resistor::~Resistor(){
    ;
}

string Resistor::getName() const{// returns the name
    return(name);
}

double Resistor::getResistance() const{// returns the resistance
    return(resistance);
}
   
Resistor* Resistor::getNext() const{
    return next;
}

void Resistor::setAll(string name_, double resistance_, int endpoints0, int endpoints1){
    name = name_;
    resistance = resistance_;
    endpointNodeIDs[0] = endpoints0;
    endpointNodeIDs[1] = endpoints1;
    next = NULL;
}

void Resistor::setResistance (double resistance_){
    resistance = resistance_;
}

void Resistor::setNext(Resistor *next_){
    next = next_;
}
   // you *may* create either of the below to print your resistor
void Resistor::print (){
    cout<<left<<setw(20)<<name<<" "<<right<<setw(8)<<setprecision(2)
            <<resistance<< " Ohms "<<endpointNodeIDs[0]<<" -> "
            <<endpointNodeIDs[1]<<endl;
}

ostream& operator<<(ostream& out,const Resistor& res){
    cout<<left<<setw(20)<<res.name<<" "<<right<<setw(8)<<setprecision(2)
            <<res.resistance<< " Ohms "<<res.endpointNodeIDs[0]<<" -> "
            <<res.endpointNodeIDs[1]<<endl;
}