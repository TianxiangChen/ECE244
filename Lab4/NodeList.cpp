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
    
    if(!IsFound){//Create the node
        Node *nod = new Node(nodeid,addr);
        if(prev == NULL){//empty list
            head = nod;
            head->setNext(NULL);
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


bool NodeList::Delete(int nodeid, Resistor *res_addr){
    Node *prev,*curr;
    prev = NULL;
    curr = head;
    
    bool IsFound = false;//should always found
    while(curr!=NULL && !IsFound){
        if(curr->getID()==nodeid){
            IsFound = true;
            break;
        }
        if(curr->getID()>nodeid)
            break;//no such node exists
        prev = curr;
        curr = curr->getNext();
    }
    
    if(!IsFound){//this should not happen
        cout<<"Error: no such nodeid found in nodelist"<<endl;
        return false;
    }
    
    curr->deleteRes(res_addr);
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
            
            curr->printNode();

    }
}

bool NodeList::setV(int nodeid, double voltage){
    Node *curr;
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
        curr = curr->getNext();
    }

    if(!IsFound){//this should not happen
        Print_NodeNotFound(nodeid);
        return false;
    }
    if(curr->IsSet()){
        cout<<"Error: node "<<nodeid<<" has already been set"<<endl;
        return false;
    }
    curr->setVoltage(voltage);
    curr->setSet();
    cout<<"Set: node "<<nodeid<<" to "<<voltage<<" Volts"<<endl;
    return true;
}
   
bool NodeList::unsetV(int nodeid){
    Node *curr;
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
        curr = curr->getNext();
    }

    if(!IsFound){//this should not happen
        Print_NodeNotFound(nodeid);
        return false;
    }
    curr->unsetVoltage();
}

void NodeList::solve(){
    bool Has_AtLeast_One_Set = false;
    for(Node *curr = head; curr != NULL; curr = curr->getNext()){
        if(curr->IsSet()){
            Has_AtLeast_One_Set = true;
            break;
        }
    }
    
    if(!Has_AtLeast_One_Set){
        Print_SolveNoSet();
        return;
    }
    double eqvalent_r = 0;//the first term in the equation in the handout
    double eqvalent_I = 0;//the sencond term in the equation in the handout
    initialize_voltage();
    while(!AllNodeConverge()){

        for(Node *curr = head; curr != NULL; curr = curr->getNext()){
            if(!curr->IsSet()){
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
                if(abs(voltage - curr->getVoltage()) <= MIN_ITERATION_CHANGE)
                    curr->setConverge();
                curr->setVoltage(voltage);
            }
        }
    }
    cout<<"Solve:"<<endl;
    for(Node *curr = head; curr != NULL; curr = curr->getNext()){
        cout<<"Node "<<curr->getID()<<": "<<setprecision(2)<<curr->getVoltage()
                <<" V"<<endl;
    }
}

void NodeList::initialize_voltage(){
    Node *curr;
    curr = head;
    
    while(curr!=NULL){
        if(!curr->IsSet()){
            curr->setDiverge();
            curr->setVoltage(0);
        }
        curr = curr->getNext();
    }
}

bool NodeList::AllNodeConverge(){
    Node *curr;
    curr = head;
    
    while(curr!=NULL){

        if(!curr->IsSet()){
            if(!curr->IsConverge())
                return false;
        }
        curr = curr->getNext();
    }
    return true;
}