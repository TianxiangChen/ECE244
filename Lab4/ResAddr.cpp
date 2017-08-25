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
