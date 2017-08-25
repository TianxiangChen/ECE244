#include "ResistorList.h"

ResistorList::ResistorList(){
    head = NULL;
}

ResistorList::~ResistorList(){
    Resistor *prev,*curr;
    prev = NULL;
    curr = head;
    
    while(curr!=NULL){
        prev = curr;
        curr = curr->getNext();
        delete prev;
    }
    head = NULL;
}

void ResistorList::Insert(string name_, double resistance_, int endpoint0,
        int endpoint1, NodeList *nlist){    
    Resistor *prev,*curr;
    prev = NULL;
    curr = head;
    
    while(curr!=NULL){
        if(curr->getName() == name_){
            Print_Duplicate(name_);
            return;
        }
        prev = curr;
        curr = curr->getNext();
    }
    
    Resistor *res = new Resistor(name_,resistance_,endpoint0,endpoint1);
    
    if(prev==NULL){//empty list
        head = res;
    }
    else{
        prev->setNext(res);
    }
    
    nlist->Insert(endpoint0, res);
    nlist->Insert(endpoint1, res);
    cout<<"Inserted: resistor "<<name_<<" "<<setprecision(2)<<std::fixed
            <<resistance_<<" Ohms "<<endpoint0<<" -> "<<endpoint1<<endl;
}

bool ResistorList::Delete(string name_, NodeList *nlist){
    if(name_ == "all"){
        //All resistors cleared and Node array updated so we have an empty network
        delete this;
        cout<<"Deleted: all resistors"<<endl;
        return true;
    }
    else{//a specified name
        Resistor *prev,*curr;
        prev = NULL;
        curr = head;
        if(head == NULL){
            cout<<"Empty List"<<endl;
            return false;
        }
        while(curr!=NULL){
            if(curr->getName() == name_){
                if(prev==NULL){//at head
                    head = curr->getNext();
                }
                else{
                    prev->setNext(curr->getNext());       
                }
                nlist->Delete(curr->getNode1(),curr);
                nlist->Delete(curr->getNode2(),curr);
                delete curr;
                cout<<"Deleted: resistor "<<name_<<endl;
                return true;
            }
            prev = curr;
            curr = curr->getNext();
        }
        Print_Res_Not_Found(name_);
        return false;
    }
}
bool ResistorList::Modify(string name_, double resistance_){
    Resistor *temp = Find(name_);
    if(temp==NULL){//check if the resistor is  in the list
        Print_Res_Not_Found(name_);
        return false;
    }
    else{
        temp->setResistance(resistance_);
        cout<<"Modified: resistor "<<name_<<" to "<<setprecision(2)<<std::fixed
            <<resistance_<<" Ohms"<<endl;
        return true;
    }
}
   
bool ResistorList::Print(string name_){
    if(name_ == "all"){
        Print_NoAll();
        return false;
    }
    Resistor *temp = Find(name_);
    if(temp==NULL){//check if the resistor is  in the list
        Print_Res_Not_Found(name_);
        return false;
    }
    else{
        cout<<"Print:"<<endl;
        temp->print();
        return true;
    }
}

Resistor* ResistorList::Find(string name_){
    Resistor *curr;
    curr = head;
    while(curr!=NULL){
        if(curr->getName() == name_)
            return curr;
        curr = curr->getNext();
    }
    return NULL;
}