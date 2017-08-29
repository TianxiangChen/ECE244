#include "Node.h"

Node::Node(){
    numRes = 0;
    head = NULL;
    next = NULL;
    set = false;
    voltage = 0;
    converge = false;
}

Node::~Node(){
    if(head != NULL){
        delete head;
    }
    numRes = 0;
    next = NULL;
    head = NULL;
    set = false;
    voltage = 0;
    converge = false;
}

Node::Node(int ID_, Resistor *addr){
    ID = ID_;
    numRes = 1;
    next = NULL;
    if(addr != NULL){
        if(head==NULL){ 
            head = new ResAddrList;
        }
        head->Insert(addr);
    }
    else
        head = NULL;
}



int Node::getResNum() const{
    return numRes;
}

int Node::getID() const{
    return ID;
}

Node* Node::getNext() const{
    return next;
}

double Node::getVoltage() const{
    return voltage;
}

ResAddrList* Node::getHead() const{
    return head;
}

bool Node::IsSet() const{
    return set;
}

bool Node::IsConverge() const{
    return converge;
}

void Node::setID(int nodeid){
    ID=nodeid;
}

void Node::addResNum(){
    numRes++;
}

void Node::addRes(Resistor *addr){
    numRes++;
    if(head==NULL){
        head = new ResAddrList;
    }
    head->Insert(addr);
}

void Node::deleteRes(Resistor *addr){
    if(head->Delete(addr));
        numRes--;
}

void Node::setResNum(int num){
    numRes = num;
}

void Node::setNext(Node* next_){
    next = next_;
}

void Node::setSet(){
    set = true;
}

void Node::setUnset(){
    set = false;
}

void Node::setVoltage(double voltage_){
    voltage = voltage_;
}

void Node::unsetVoltage(){
    voltage = 0;
    set = false;
    cout<<"Unset: the solver will determine the voltage of node "<<ID<<endl;
}
   
void Node::setConverge(){
    converge = true;
}

void Node::setDiverge(){
    converge = false;
}

void Node::printNode(){
    //cout<<"Connections at node "<<ID<<": "<<numRes<<" resistor(s)"<<endl;
    if(numRes == 0)
        return;
    cout<<"Connections at node "<<ID<<": "<<numRes<<" resistor(s)"<<endl;
    head->Print();
}

void Node::clear(){
    if(head != NULL){
        delete head;
    }
    numRes = 0;
    head = NULL;
}