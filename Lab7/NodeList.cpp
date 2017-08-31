#include <valarray>

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

bool NodeList::set_draw_coords (float& xleft, float& ybottom, float& xright,
float& ytop){
    int node_num = 0, res_num = 0;//count # of res and node so decide the size
    //of the drawing window
    Node *curr;
    curr = head;
    while(curr!=NULL){

        if(curr->getResNum()>0){
            node_num++;
            for(ResAddr *curr_res=curr->getHead()->getHead(); curr_res != NULL;
                    curr_res = curr_res->getNext())
                res_num++;
        }
        curr = curr->getNext();
    }
    res_num /=2;//res counts twice
    
    if(res_num == 0)
        return false;//no resistor, so do not print
    
    xleft = 0;
    ybottom = 0;//these two are fixed
    xright = node_num * 80 + 20 *2;
    ytop = res_num * 80 + 40*2;
    return true;
}

void NodeList::draw(int num_node, int num_res, easygl *window){
    window->gl_clearscreen();//reset the screen
    
    int i=0;//a variable to determine the position for x-axis, could be num_node visited
    int j=0;//a variable to determine the position for y-axis, could be num_res visited
    for(Node* curr=head; curr!=NULL; curr=curr->getNext()){
        /*a for loop is used here purely for the node which is not efficient,
         but seems I have to do this since I cannot set the priority of the layer
         and the node has to be the bottom layer*/
        if(curr->getResNum()!=0){
            /*draw the node rectangles*/
            window->gl_setcolor(DARKGREY);
            window->gl_fillrect(20+30+80*i, 80*num_res+40, 20+30+80*i+20, 40);
            //this function draws from top left to bottom right
        }
        i++;
    }
        
    i=0;//reset the counter for num_node resited
    for(Node* curr=head; curr!=NULL; curr=curr->getNext()){ 
        string output;//the output text
        stringstream convert;//a conversion for output text
        /*draw the resistors*/
        window->gl_setcolor(BLACK);
        for(ResAddr *res_curr=curr->getHead()->getHead(); res_curr!=NULL;
                res_curr=res_curr->getNext()){
            if(curr->getID() < res_curr->getResAddr()->getTheOtherNode(curr->getID())){//only draw when at the node smaller 
                //than the other one. eg, draw res b/t node 1&2 when at 1.
                double xcen1 = 20 + 80*i + 40;
                double ycen1 = 40 + 40 + 80*j;

                /*find the index of nodeid2*/
                int index = 0;
                bool IsFound = false;
                for(Node *curr_temp=head; curr_temp!=NULL && !IsFound;
                        curr_temp = curr_temp->getNext()){
                    if(curr_temp->getID() == res_curr->getResAddr()->getTheOtherNode(curr->getID()))
                        IsFound = true; 
                    index++;
                }
                double xcen2 = 20 + 80*(index-1) + 40;
                double ycen2 = ycen1;
                
                /*drawing the circle for resistor connection*/
                window->gl_fillarc(xcen1,ycen1,2,0,360);
                window->gl_fillarc(xcen2,ycen2,2,0,360);
                
                /*label the resistor*/
                double res_xcen = (xcen1+xcen2)/2;
                double res_ycen = (ycen1+ycen2)/2;
                convert.clear();
                convert<<setprecision(2)<<std::fixed<<res_curr->getResAddr()->getResistance();
                convert>>output;
                window->gl_setfontsize(16);
                window->gl_drawtext(res_xcen,res_ycen-8,"Resistor: " + 
                res_curr->getResAddr()->getName() + " = " + output + " Ohms");
                
                /*draw the resistor, the resistor is design to be made of lines
                 connecting with each other with an angle of 60 degree, each one
                 is length of 4*/
                double length = 4;
                double x_start = res_xcen - length/2 * sin(30*PI/180);
                double x_end = res_xcen + length/2 * sin(30*PI/180);
                double y_start = res_ycen - length/2 * sin(60*PI/180);
                double y_end = res_ycen + length/2 * sin(60*PI/180);
                window->gl_drawline(x_start, y_start, x_end, y_end);
                window->gl_drawline(x_start+2*length*sin(30*PI/180), y_start,
                        x_end+2*length*sin(30*PI/180), y_end);
                window->gl_drawline(x_start-2*length*sin(30*PI/180), y_start,
                        x_end-2*length*sin(30*PI/180), y_end);
                x_start = res_xcen - length/2 * sin(30*PI/180) * 7;
                x_end = res_xcen - length/2 * sin(30*PI/180) * 5;
                y_start = res_ycen + length/2 * sin(60*PI/180);
                y_end = res_ycen - length/2 * sin(60*PI/180);
                window->gl_drawline(x_start, y_start, x_end, y_end);
                window->gl_drawline(x_start+2*length*sin(30*PI/180), y_start,
                        x_end+2*length*sin(30*PI/180), y_end);
                window->gl_drawline(x_start+4*length*sin(30*PI/180), y_start,
                        x_end+4*length*sin(30*PI/180), y_end);
                window->gl_drawline(x_start+6*length*sin(30*PI/180), y_start,
                        x_end+6*length*sin(30*PI/180), y_end);
                window->gl_drawline(x_start, y_start, 
                        x_start-length/2 * sin(30*PI/180), y_start-length/2 * sin(60*PI/180));
                window->gl_drawline(x_start-length/2 * sin(30*PI/180), y_start-length/2 * sin(60*PI/180),
                        xcen1,ycen1);//draw the line connecting the node to left of the res
                window->gl_drawline(x_end+6*length*sin(30*PI/180), y_end,
                        x_end+6.5*length*sin(30*PI/180), y_end+length/2 * sin(60*PI/180));
                window->gl_drawline(xcen2, ycen2,
                        x_end+6.5*length*sin(30*PI/180), y_end+length/2 * sin(60*PI/180));
                //draw the line connecting the node to left of the res
                j++;
            }
        }

        /*display the node name*/
        window->gl_setcolor(BLACK);
        window->gl_setfontsize(16);
        convert.clear();
        convert<<curr->getID();
        convert>>output;
        window->gl_drawtext(20+30+80*i+10,20,"Node " + output);

        /*display the node voltage*/
        convert.clear();
        //convert<<setprecision(2)<<std::fixed<<curr->getVoltage()<<"V";
        convert<<setprecision(2)<<std::fixed<<curr->getVoltage();
        convert>>output;
        if(!curr->IsSet())
            window->gl_setcolor(RED);//Red for unsetted voltage
        window->gl_drawtext(20+30+80*i+10,30,output + "V");
        i++;
    }
    
    /*display the title*/
    double x = (num_node * 80 + 20 *2)/2;
    double y = num_res * 80 + 40*2 - 20;
    window->gl_setcolor(BLACK);
    window->gl_setfontsize(20);
    window->gl_drawtext(x,y+4,"Resistor Network");
    window->gl_setfontsize(14);
    stringstream convert;
    string n_res, n_node;
    convert.clear();
    convert << num_res;
    convert >> n_res;
    convert.clear();
    convert << num_node;
    convert >> n_node;
    window->gl_drawtext(x,y-4,n_res+" resistor(s), "+n_node+" node(s)");
    
    /*display the footer*/
    window->gl_setfontsize(14);
    window->gl_drawtext(x,10,"Note: Red voltages mean unset(based on calculation if solve function has been run.");
}