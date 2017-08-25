#include "ResAddrList.h"
   
ResAddrList::ResAddrList(){
    head = NULL;
}

ResAddrList::~ResAddrList(){
    ResAddr *prev,*curr;
    prev = NULL;
    curr = head;
    
    while(curr!=NULL){
        prev = curr;
        curr = curr->getNext();
        delete prev;
    }
    head = NULL;
}

void ResAddrList::Insert(Resistor *Addr){
    ResAddr *prev,*curr;
    prev = NULL;
    curr = head;
    
    while(curr!=NULL){
        prev = curr;
        curr = curr->getNext();
    }
    
    //Create the node
    ResAddr *raddr = new ResAddr(Addr);
    if(prev == NULL){//empty list
        head = raddr;
    }
    else{
        prev->setNext(raddr);
    }
}

bool ResAddrList::Delete(Resistor *Addr){
    ResAddr *prev,*curr;
    prev = NULL;
    curr = head;
    bool IsFound = false;//In principle it should always find the addr, just
    //for safety
    
    while(curr!=NULL){
        if(curr->getResAddr()==Addr){
            IsFound = true;
            break;
        }
        prev = curr;
        curr = curr->getNext();
    }
    
    if(!IsFound)//should never enter here
        cout<<"Error: No such addr found in ResAddrList"<<endl;
    else{
         if(prev == head){//only head
            delete head;
            head = NULL;
            return true;
        }
        else{
            prev->setNext(curr->getNext());
            delete curr;
            return true;
        }     
    }
}

void ResAddrList::Print(){
    ResAddr *curr=head;
    while(curr!=NULL){
        curr->getResAddr()->print();
        curr = curr->getNext();
    }
}

ResAddr* ResAddrList::getHead() const{
    return head;
}
