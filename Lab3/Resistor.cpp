/*
 * Resistor.cpp
 */
#include "Resistor.h"

Resistor::Resistor(int rIndex_,string name_,double resistance_,int endpoints_[2]){
    name = name_;
    resistance = resistance_;
    endpointNodeIDs[0] = endpoints_[0];
    endpointNodeIDs[1] = endpoints_[1];
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
   
int Resistor::getIndex() const{// returns the index
    return(index);
}

void Resistor::setAll(int index_, string name_, double resistance_, int endpoints0, int endpoints1){
    index = index_;
    name = name_;
    resistance = resistance_;
    endpointNodeIDs[0] = endpoints0;
    endpointNodeIDs[1] = endpoints1;
}

void Resistor::setResistance (double resistance_){
    resistance = resistance_;
}

void Resistor::setIndex (int index_){
    index = index_;
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