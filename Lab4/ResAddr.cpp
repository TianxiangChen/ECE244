#include "ResAddr.h"

ResAddr::ResAddr(){
    Addr = NULL;
    next = NULL;
}

ResAddr::~ResAddr(){
    Addr = NULL;
    next = NULL;
}

ResAddr::ResAddr(Resistor* Addr_){
    Addr = Addr_;
    next = NULL;
}

Resistor* ResAddr:: getResAddr() const{
    return Addr;
}

ResAddr* ResAddr::getNext() const{
    return next;
}

void ResAddr::setNext(ResAddr *next_){
    next = next_;
}

void ResAddr::setAddr(Resistor *Addr_){
    Addr = Addr_;
}