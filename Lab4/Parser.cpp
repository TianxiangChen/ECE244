/*
 * This file implements the parser function of the program
 */
#include "Parser.h"

int Parser() {
    ResistorList *res_head = new ResistorList;
    string line, command;
    cout<<"> ";
    getline (cin, line);
    
    while ( !cin.eof () ) {
        stringstream lineStream (line);
        lineStream >> command;
        if(lineStream.fail()){
            Print_InvalidCom();
        }
        else{
            if (command == "insertR") {
                insertR(lineStream, res_head);
            }
            else if (command == "modifyR") {
                modifyR(lineStream,res_head);
            }
            else if (command == "printR"){
                printR(lineStream,res_head);
            }
            else if (command == "printNode"){
                ;//printNode(lineStream,res,node,MaxNodeNumber);
            }
            else if (command == "deleteR"){
                deleteR(lineStream,res_head);
            }
            else if (command == "setV"){
                ;
            }
            else if (command == "unsetV"){
                ;
            }
            else if (command == "solve"){
                ;
            }
            else
                Print_InvalidCom();
        }
        //one operation done, waiting for the next input.
        cout<<"> ";
        getline (cin, line);
    }
    delete res_head;
//    delete []node;
    res_head=NULL;
//    node=NULL;
    // End input loop until EOF.
    return 0;
}

void insertR(stringstream &lineStream, ResistorList *res_head){
    string name;
    double resistance;
    int nodeid1, nodeid2;
    
    if (TooFewArguChecking(lineStream))
        return;
    if(!NameChecking(lineStream, name))
        return;
    if(!ResChecking(lineStream, resistance))
        return;
    if(!NodeChecking(lineStream, nodeid1))
        return;
    if(!Node2Checking(lineStream, nodeid1, nodeid2))
        return;
    if(TooManyArguChecking(lineStream))
        return;
    
    //Parser checking finishes, start inserting data
    res_head->Insert(name, resistance, nodeid1, nodeid2);
    //res[res_index].setAll(res_index,name,resistance,nodeid1,nodeid2);
    //node[nodeid1].addResistor(res_index);
    //node[nodeid2].addResistor(res_index);
    
}

void modifyR(stringstream &lineStream, ResistorList *res_head){
    string name;
    double resistance;
    
    if (TooFewArguChecking(lineStream))
        return;
    if (!NameChecking(lineStream, name))
        return;
    if(!ResChecking2(lineStream, resistance))
        return;
    if(TooManyArguChecking(lineStream))
        return;
    
    //Parser checking finishes, start modifying the data
    res_head->Modify(name,resistance);
}

void printR(stringstream &lineStream, ResistorList *res_head){
    string name;
    if (TooFewArguChecking(lineStream))
        return;
    if(!NameChecking2(lineStream, name))
        return;
    
    res_head->Print(name);
}

void printNode(stringstream &lineStream, Resistor *res, Node *node,
        const int MaxNodeNumber){
    string name;
    int nodeid;
    if (TooFewArguChecking(lineStream))
        return;
    if(!NameChecking4(lineStream, name,nodeid))
        return;
    
    if(name == "all"){
        cout<<"Print:"<<endl;
        for(int i=0; i<MaxNodeNumber;i++){
            if(node[i].getResNum()>0){
                node[i].printNode(i,res);
//                cout<<"Connections at node "<<i<<": "<<node[i].getResNum()
//                        <<" resistor(s)"<<endl;
//                for(int j=0; j<node[i].getResNum();j++){
//                    cout<<"  "<<(cout,res[node[i].getIndex(j)]);
                }
            
            else
                cout<<"Print:"<<endl<<"Connections at node "<<i
                        <<": 0 resistor(s)"<<endl; 
        }
    }
    else{
        cout<<"Connections at node "<<nodeid<<": "<<node[nodeid].getResNum()
                        <<" resistor(s)"<<endl;
        if(node[nodeid].getResNum()>0){
            for(int i=0; i<node[nodeid].getResNum();i++){
                node[i].printNode(i,res);
//                cout<<"  "<<(cout,res[node[nodeid].getIndex(i)]);
                }
        }
    }
}

void deleteR(stringstream &lineStream, ResistorList *res_head){
    string name;
    if (TooFewArguChecking(lineStream))
        return;
    if(!NameChecking3(lineStream, name))
        return;
    
    res_head->Delete(name);
}


//Valid Checking
bool NameChecking(stringstream &lineStream, string &name){
    lineStream >> name;
    if(name =="all"){
        Print_NoAll();
        return false;
    }
    else if (TooFewArguChecking(lineStream)){
        return false;
    }
    return true;
}

bool NameChecking2(stringstream &lineStream, string &name){//For printR
    if(TooFewArguChecking(lineStream))
        return false;
        
    lineStream >> name;
     if (TooManyArguChecking(lineStream)){
        return false;
    }
    return true;
}

bool NameChecking3(stringstream &lineStream, string &name){//For deleteR
    if(TooFewArguChecking(lineStream))
        return false;
    
    lineStream >> name;
     if (TooManyArguChecking(lineStream)){
        return false;
    }
    return true;
}

bool NameChecking4(stringstream &lineStream, string &name, int &nodeid){//For printNode
    if(TooFewArguChecking(lineStream))
        return false;
    
    lineStream >> name;
    //if not all, convert into an int nodeid
    if(name != "all"){
        stringstream stoi_convert;//string to integer converter
        stoi_convert << name;
        stoi_convert >> nodeid;
    
        if(stoi_convert.fail()){
            Print_InvalidArgu();
            return false;
        }
        else if( stoi_convert.peek()!=' ' && !stoi_convert.eof()){
            Print_InvalidArgu();
            return false;
        }
        else if(nodeid<LowBound){
            Print_NodeExceed(nodeid);
            return false;
        }
        
    }
    
    if (TooManyArguChecking(lineStream)){
        return false;
    }
    return true;
}

bool ResChecking(stringstream &lineStream, double &resistance){
    lineStream >> resistance;
    if(lineStream.fail()){
        Print_InvalidArgu();
        return false;
    }
    else if( lineStream.peek()!=' ' && !lineStream.eof()){
        Print_InvalidArgu();
        return false;
    }
    else if (resistance < 0){
        Print_NegRes();
        return false;
    }
    else if (TooFewArguChecking(lineStream)){
        return false;
    }
    return true;
}

bool ResChecking2(stringstream &lineStream, double &resistance){//For modifyR
        lineStream >> resistance;
    if(lineStream.fail()){
        Print_InvalidArgu();
        return false;
    }
    else if( lineStream.peek()!=' ' && !lineStream.eof()){
        Print_InvalidArgu();
        return false;
    }
    else if (resistance < 0){
        Print_NegRes();
        return false;
    }
    return true;
}

bool NodeChecking(stringstream &lineStream, int &nodeid){
    lineStream >> nodeid;
    if(lineStream.fail()){
        Print_InvalidArgu();
        return false;
    }
    else if( lineStream.peek()!=' ' && !lineStream.eof()){
        Print_InvalidArgu();
        return false;
    }
    else if(nodeid<LowBound){
        Print_NodeExceed(nodeid);
        return false;
    }
    else if (TooFewArguChecking(lineStream)){
        return false;
    }
    return true;
}

bool Node2Checking(stringstream &lineStream, int &nodeid1, int &nodeid2){
    lineStream >> nodeid2;
    if(lineStream.fail()){
        Print_InvalidArgu();
        return false;
    }
    else if( lineStream.peek()!=' ' && !lineStream.eof()){
        Print_InvalidArgu();
        return false;
    }
    else if(nodeid2<LowBound){
        Print_NodeExceed(nodeid2);
        return false;
    }
    else if(nodeid1 == nodeid2){
        Print_SameTerminal(nodeid1);
        return false;
    }
    return true;
}

bool TooFewArguChecking(stringstream &lineStream){
    
    if (lineStream.eof()){
        Print_ToofewArgu();
        return true;
    }

    char anything;
    lineStream >> anything;
    if(lineStream.fail()){
            Print_ToofewArgu();
            return true;
    }
    
    lineStream.putback(anything);
    return false;
}

bool TooManyArguChecking(stringstream &lineStream){
    if (!lineStream.eof()){
        string anything;
        lineStream >> anything;
        if(!lineStream.fail()){
            Print_TooManyArgu();
            return true;
        }
    }
    return false;
}