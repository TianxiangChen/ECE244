#include "NodeList.h"

NodeList::NodeList(){
    head = NULL;
}

NodeList::~NodeList(){
    Node *prev,*curr;
    prev = NULL;
    curr = head;
    
    while(curr!=NULL){
        prev = curr;
        curr = curr->getNext();
        delete prev;
    }
    head = NULL;
}

void NodeList::Insert(int nodeid, Resistor *addr){
    Node *prev,*curr;
    prev = NULL;
    curr = head;
    
    bool IsFound = false;
    bool Done = false;
    while(curr!=NULL && !IsFound && !Done){
        if(curr->getID()==nodeid){
            IsFound = true;
            break;
        }
        if(curr->getID()>nodeid){
            Done = true;//no such node exists
            break;
        }
        prev = curr;
        curr = curr->getNext();
    }
    
    if(!IsFound || Done){//Create the node
        Node *nod = new Node(nodeid,addr);
        //Node *nod = new Node;
        //nod->setID(nodeid);
        //nod->addRes(addr);
        if(prev == NULL){//empty list, or it should insert at head
            nod->setNext(curr);
            head = nod;
        }
        else{
            prev->setNext(nod);
            nod->setNext(curr);
        }
    }
    else{//the node exists, add the res addr to it
        curr->addRes(addr);
    }
    
}

void NodeList::DeleteAll(){
    Node *curr, *prev;
    prev = NULL;
    curr = head;
    while(curr != NULL){
        prev = curr;
        curr = curr->getNext();
        prev->clear();
    }
}

bool NodeList::Delete(int nodeid, Resistor *res_addr){
    Node *prev,*curr;
    prev = NULL;
    curr = head;
    
    bool IsFound = false;
    bool Done = false;
    while(curr!=NULL){
        if(curr->getID()==nodeid){
            IsFound = true;
            break;
        }
        if(curr->getID()>nodeid){
            Done = true;
            break;//no such node exists
        }
        prev = curr;
        curr = curr->getNext();
    }
    
    if(!IsFound || Done){//this should not happen
        cout<<"Error: no such nodeid found in nodelist"<<endl;
        return false;
    }

    curr->deleteRes(res_addr);
    
    if(curr->getResNum() == 0){
        if(prev == NULL){//at head
            head = curr->getNext();
            delete curr;
        }
        else{
            prev->setNext(curr->getNext());
            delete curr;
        }
    }
    return true;
}

   
void NodeList::Print(string name, int nodeid){
        if(name == "all"){
        cout<<"Print:"<<endl;
        for(Node *curr = head; curr != NULL;curr=curr->getNext()){
            curr->printNode(); 
        }
    }
    else{
            Node *prev,*curr;
            prev = NULL;
            curr = head;

            bool IsFound = false;//should always found
            bool Done = false;
            while(curr!=NULL && !IsFound && !Done){
                if(curr->getID()==nodeid){
                    IsFound = true;
                    break;
                }
                if(curr->getID()>nodeid){
                    Done = true;//no such node exists
                    break;
                }
                prev = curr;
                curr = curr->getNext();
            }

            if(!IsFound){//this should not happen
                Print_NodeNotFound(nodeid);
                return;
            }
            cout<<"Print:"<<endl;
            curr->printNode();
    }
}

bool NodeList::setV(int nodeid, double voltage){
    Node *prev,*curr;
    prev = NULL;
    curr = head;
    
    bool IsFound = false;
    bool Done = false;
    while(curr!=NULL){
        if(curr->getID()==nodeid){
            IsFound = true;
            break;
        }
        if(curr->getID()>nodeid){
            Done = true;//no such node exists
            break;
        }
        prev = curr;
        curr = curr->getNext();
    }
    
    if(!IsFound || Done){//Create the node
        Node *nod = new Node(nodeid,NULL);
        if(prev == NULL){//empty list, or should insert at head
            head = nod;
            head->setNext(curr);
            head->setVoltage(voltage);
            head->setSet();
            head->setResNum(0);
        }
        else{
            prev->setNext(nod);
            nod->setNext(curr);
            nod->setVoltage(voltage);
            nod->setSet();
            nod->setResNum(0);
        }
        cout<<"Set: node "<<nodeid<<" to "<<fixed<<setprecision(2)<<voltage<<" Volts"<<endl;
        return true;
    }
//    if(curr->IsSet()){
//        cout<<"Error: node "<<nodeid<<" has already been set"<<endl;
//        return false;
//    }
    curr->setVoltage(voltage);
    curr->setSet();
    cout<<"Set: node "<<nodeid<<" to "<<fixed<<setprecision(2)<<voltage<<" Volts"<<endl;
    return true;
}
   
bool NodeList::unsetV(int nodeid){
//    Node *curr;
//    curr = head;
//
//    bool IsFound = false;
//    bool Done = false;
//    while(curr!=NULL && !IsFound && !Done){
//        if(curr->getID()==nodeid){
//            IsFound = true;
//            break;
//        }
//        if(curr->getID()>nodeid){
//            Done = true;//no such node exists
//            break;
//        }
//        curr = curr->getNext();
//    }
//
//    if(!IsFound || Done){
//        Print_NodeNotFound(nodeid);
//        return false;
//    }
    
    /**newly added b/c testcase1*/
    Node *prev,*curr;
    prev = NULL;
    curr = head;
    
    bool IsFound = false;
    bool Done = false;
    while(curr!=NULL){
        if(curr->getID()==nodeid){
            IsFound = true;
            break;
        }
        if(curr->getID()>nodeid){
            Done = true;//no such node exists
            break;
        }
        prev = curr;
        curr = curr->getNext();
    }
    if(!IsFound || Done){//Create the node
        Node *nod = new Node(nodeid, NULL);
        if(prev == NULL){//empty list, or should insert at head
            head = nod;
            head->setNext(curr);
            head->setResNum(0);
            head->unsetVoltage();
        }
        else{
            prev->setNext(nod);
            nod->setNext(curr);
            nod->setResNum(0);
            nod->unsetVoltage();
        }
    }
    else
    /**newly added b/c testcase1*/
    curr->unsetVoltage();
    return true;
}

void NodeList::solve(){
    bool Has_AtLeast_One_Set = false;
    for(Node *curr = head; curr != NULL; curr = curr->getNext()){
        if(curr->IsSet() && curr->getResNum()>0){
            Has_AtLeast_One_Set = true;
            break;
        }
    }
    if(!Has_AtLeast_One_Set){
        Print_SolveNoSet();
        return;
    }
    initialize_voltage();
    while(!AllNodeConverge()){        
                for(Node *curr = head; curr != NULL; curr = curr->getNext()){
            if(!curr->IsSet() && curr->getResNum()>0){
                double eqv_r = 0;//the first term of the formula in the handout
                double eqv_i = 0;//the second term of the formula in the handout
                double voltage = 0;
                ResAddr *resaddr_curr = curr->getHead()->getHead();
                while(resaddr_curr != NULL){
                    int node;
                    eqv_r = eqv_r + 1 / resaddr_curr->getResAddr()->getResistance();
                    node = resaddr_curr->getResAddr()->getTheOtherNode(curr->getID());
                    
                    Node *curr_temp;
                    curr_temp = head;
                    
                    bool isfound =false;
                    while(curr_temp != NULL){
                        if(curr_temp->getID() == node){
                            isfound =true;
                            break;
                        }
                        curr_temp = curr_temp->getNext();
                    }
                    
                    eqv_i = eqv_i + curr_temp->getVoltage() / 
                            resaddr_curr->getResAddr()->getResistance();
                    resaddr_curr = resaddr_curr->getNext();
                }
                eqv_r = 1 / eqv_r;
                voltage = eqv_r * eqv_i;
                if(abs(voltage - curr->getVoltage()) <= MIN_ITERATION_CHANGE){
                //if(voltage - curr->getVoltage() <= MIN_ITERATION_CHANGE && voltage - curr->getVoltage() >= -1*MIN_ITERATION_CHANGE){
                    curr->setConverge();
                }
                else{
                    curr->setDiverge();
                }
                curr->setVoltage(voltage);                
            }
        }
    }
    cout<<"Solve:"<<endl;
    for(Node *curr = head; curr != NULL; curr = curr->getNext()){
        if(curr->getResNum()>0)
            cout<<"  Node "<<curr->getID()<<": "<<setprecision(2)<<curr->getVoltage()
                <<" V"<<endl;
    }
}

void NodeList::initialize_voltage(){
    Node *curr;
    curr = head;
    
    while(curr!=NULL){
        if(!curr->IsSet() && curr->getResNum()>0){
            curr->setDiverge();
            curr->setVoltage(0);
        }
        //curr->setVoltageCal(curr->getVoltage());
        curr = curr->getNext();
    }
}

bool NodeList::AllNodeConverge(){
    Node *curr;
    curr = head;
    
    while(curr!=NULL){

        if(!curr->IsSet()&& curr->getResNum()>0){
            if(!curr->IsConverge())
                return false;
        }
        curr = curr->getNext();
    }
    return true;
}