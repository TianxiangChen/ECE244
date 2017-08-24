/*
 * Node.cpp
 */
#include "Node.h"

Node::Node(){
    numRes = 0;
}

Node::~Node(){
    ;
}

   // Updates resIDArray to show the resistor in position rIndex in
   // the resistor array is now connected to this node.
   // Returns true if successful
bool Node::addResistor (int rIndex){
    if(numRes >= MAX_RESISTORS_PER_NODE)
        return false;
    resIDArray[numRes]=rIndex;
    numRes++;
    return true;
} 

int Node::getResNum() const{
    return numRes;
}

int Node::getIndex(int NodeNum) const{
    return resIDArray[NodeNum];
}

int Node::getID() const{
    return ID;
}
void Node::printNode(int nodeid, Resistor *res){
    cout<<"Connections at node "<<nodeid<<": "<<numRes<<" resistor(s)"<<endl;
                for(int i=0; i<numRes;i++){
                    cout<<"  "<<(cout,res[resIDArray[i]]);
                }
}
