/*
 * This file implements the parser function of the program
 */
#include "Parser.h"

int Parser() {
    int res_index = 0;
    int MaxNodeNumber = 0, MaxResistors = 0;
    Node *node = new Node [1];
    Resistor *res = new Resistor[1];
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
                insertR(lineStream, node, res, res_index, MaxNodeNumber, MaxResistors);
            }
            else if (command == "modifyR") {
                modifyR(lineStream,res,res_index);
            }
            else if (command == "printR"){
                printR(lineStream,res,res_index);
            }
            else if (command == "printNode"){
                printNode(lineStream,res,node,MaxNodeNumber);
            }
            else if (command == "deleteR"){
                deleteR(lineStream,res,node,MaxNodeNumber,MaxResistors,res_index);
            }
            else if (command == "maxVal"){
                maxVal(lineStream, node, res, MaxNodeNumber, MaxResistors, res_index);
                

            }
            else
                Print_InvalidCom();
        }
        //one operation done, waiting for the next input.
        cout<<"> ";
        getline (cin, line);
    }
    delete []res;
    delete []node;
    res=NULL;
    node=NULL;
    // End input loop until EOF.
    return 0;
}

void insertR(stringstream &lineStream, Node *node, Resistor *res, int &res_index,
        const int MaxNodeNumber, const int MaxResistors){
    string name;
    double resistance;
    int nodeid1, nodeid2;
    
    if (TooFewArguChecking(lineStream))
        return;
    if(!NameChecking(lineStream, name))
        return;
    if(!ResChecking(lineStream, resistance))
        return;
    if(!NodeChecking(lineStream, nodeid1, MaxNodeNumber))
        return;
    if(!Node2Checking(lineStream, nodeid1, nodeid2, MaxNodeNumber))
        return;
    if(TooManyArguChecking(lineStream))
        return;
    if(res_index > MaxResistors - 1){
        Print_Array_Full();
        return;
    }
    if((node[nodeid1].getResNum()== MAX_RESISTORS_PER_NODE) ||
            (node[nodeid2].getResNum()== MAX_RESISTORS_PER_NODE)){
        Print_Node_Full();
        return;
    }
    if(nodeid1 > MaxNodeNumber - 1 ){
        Print_NodeExceed(nodeid1, MaxNodeNumber);
        return;
    }
    if(nodeid2 > MaxNodeNumber - 1 ){
        Print_NodeExceed(nodeid2, MaxNodeNumber);
        return;
    }
    bool IsFound = false;
    for(int i=0;i<res_index;i++){
            if(res[i].getName()==name){
                IsFound = true;
            }
    }
    if(IsFound){
        Print_Duplicate(name);
        return;
    }
    
    //Parser checking finishes, start inserting data
    res[res_index].setAll(res_index,name,resistance,nodeid1,nodeid2);
    node[nodeid1].addResistor(res_index);
    node[nodeid2].addResistor(res_index);
    res_index++;
    cout<<"Inserted: resistor "<<name<<" "<<setprecision(2)<<std::fixed
            <<resistance<<" Ohms "<<nodeid1<<" -> "<<nodeid2<<endl;
}

void modifyR(stringstream &lineStream, Resistor *res, int res_index){
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
    bool IsFound = false;
    for(int i=0;i<res_index;i++){
            if(res[i].getName()==name){
                res[i].setResistance(resistance);
                IsFound = true;
            }
    }
    if(IsFound)
    cout<<"Modified: resistor "<<name<<" to "<<setprecision(2)<<std::fixed
            <<resistance<<" Ohms"<<endl;
    else
        Print_Res_Not_Found();
}

void printR(stringstream &lineStream, Resistor *res, int res_index){
    string name;
    if (TooFewArguChecking(lineStream))
        return;
    if(!NameChecking2(lineStream, name))
        return;
    if(name == "all"){
        cout<<"Print: "<<endl;
        for(int i=0;i<res_index;i++){
            cout<<(cout,res[i]);
            //res[i].print();
        }
    }
    else{
        bool IsFound = false;
        for(int i=0;i<res_index;i++){
            if(res[i].getName()==name){
                cout<<"Print:"<<endl;
                cout<<(cout,res[i]);
                //res[i].print();
                IsFound = true;
            }
        }
        if(!IsFound)
            Print_Res_Not_Found();
    }
}

void printNode(stringstream &lineStream, Resistor *res, Node *node,
        const int MaxNodeNumber){
    string name;
    int nodeid;
    if (TooFewArguChecking(lineStream))
        return;
    if(!NameChecking4(lineStream, name, MaxNodeNumber,nodeid))
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

void deleteR(stringstream &lineStream, Resistor *&res, Node *&node, 
        const int MaxNodeNumber, const int MaxResistors, int &res_index){
    string name;
    if (TooFewArguChecking(lineStream))
        return;
    if(!NameChecking3(lineStream, name))
        return;
    if(name == "all"){
        //All resistors cleared and Node array updated so we have an empty network
        delete []res;
        delete []node;
        res=NULL;
        node=NULL;
        node=new Node[MaxNodeNumber];
        res=new Resistor[MaxResistors];
        res_index = 0;
        cout<<"Deleted: all resistors"<<endl;
    }
    else
        Print_InvalidCom();
}

void maxVal(stringstream &lineStream,Node *&node, Resistor *&res, int &MaxNodeNumber
, int &MaxResistors, int &res_index){
    if(!NodeNumChecking(lineStream, MaxNodeNumber))
        return;
    if(!ResNumChecking(lineStream, MaxResistors))
        return;
    if(TooManyArguChecking(lineStream))
        return;
    delete []res;
    delete []node;
    res=NULL;
    node=NULL;
    res_index = 0;
    node=new Node[MaxNodeNumber];
    res=new Resistor[MaxResistors];
    cout<<"New network: max node number is "<<MaxNodeNumber<<"; max resistors is "
            <<MaxResistors<<endl;
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

bool NameChecking4(stringstream &lineStream, string &name, const int MaxNodeNumber
, int &nodeid){//For printNode
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
        else if(nodeid<LowBound || nodeid>MaxNodeNumber){
            Print_NodeExceed(nodeid,MaxNodeNumber);
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

bool NodeChecking(stringstream &lineStream, int &nodeid, const int MaxNodeNumber){
    lineStream >> nodeid;
    if(lineStream.fail()){
        Print_InvalidArgu();
        return false;
    }
    else if( lineStream.peek()!=' ' && !lineStream.eof()){
        Print_InvalidArgu();
        return false;
    }
    else if(nodeid<LowBound || nodeid>MaxNodeNumber-1){
        Print_NodeExceed(nodeid, MaxNodeNumber-1);
        return false;
    }
    else if (TooFewArguChecking(lineStream)){
        return false;
    }
    return true;
}

bool Node2Checking(stringstream &lineStream, int &nodeid1, int &nodeid2,
        const int MaxNodeNumber){
    lineStream >> nodeid2;
    if(lineStream.fail()){
        Print_InvalidArgu();
        return false;
    }
    else if( lineStream.peek()!=' ' && !lineStream.eof()){
        Print_InvalidArgu();
        return false;
    }
    else if(nodeid2<LowBound || nodeid2>MaxNodeNumber-1){
        Print_NodeExceed(nodeid2, MaxNodeNumber);
        return false;
    }
    else if(nodeid1 == nodeid2){
        Print_SameTerminal(nodeid1);
        return false;
    }
    return true;
}

bool NodeNumChecking(stringstream &lineStream, int &num){
    lineStream >> num;
    if(lineStream.fail()){
        Print_InvalidArgu();
        return false;
    }
    else if( lineStream.peek()!=' ' && !lineStream.eof()){
        Print_InvalidArgu();
        return false;
    }
    else if(num <= 0){
        Print_NegMaxVal();
        return false;
    }
    else if (TooFewArguChecking(lineStream)){
        return false;
    }
    return true;
}

bool ResNumChecking(stringstream &lineStream, int &num){
    lineStream >> num;
    if(lineStream.fail()){
        Print_InvalidArgu();
        return false;
    }
    else if( lineStream.peek()!=' ' && !lineStream.eof()){
        Print_InvalidArgu();
        return false;
    }
    else if(num <= 0){
        Print_NegMaxVal();
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


//Error Printing
void Print_InvalidCom(){
    cout<<"Error: invalid command"<<endl;
}
void Print_InvalidArgu(){
    cout<<"Error: invalid argument"<<endl;
}
void Print_NegRes(){
    cout<<"Error: negative resistance"<<endl;
}
void Print_NodeExceed(const int nodeid, const int MaxNodeNumber){
    cout<<"Error: node "<<nodeid<<" is out of permitted range "<<LowBound<<
            "-"<<MaxNodeNumber-1<<endl;
}
void Print_NoAll(){
    cout<<"Error: resistor name cannot be the keyword \"all\""<<endl;
}
void Print_SameTerminal(const int nodeid){
    cout<<"Error: both terminals of resistor connect to node "<<nodeid<<endl;
}
void Print_TooManyArgu(){
    cout<<"Error: too many arguments"<<endl;
}
void Print_ToofewArgu(){
    cout<<"Error: too few arguments"<<endl;
}
void Print_NegMaxVal(){
    cout<<"Error: maxVal arguments must be greater than 0"<<endl;;
}
void Print_Array_Full(){
    cout<<"Error: resistor array is full"<<endl;
}
void Print_Node_Full(){
    cout<<"Error: node is full"<<endl;
}
void Print_Res_Not_Found(){
    cout<<"Error: resistor name not found"<<endl;
}
void Print_Duplicate(string name){
    cout<<"Error: resistor "<<name<<" already exists"<<endl;
}