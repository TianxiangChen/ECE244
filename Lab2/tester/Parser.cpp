/*
 * ECE244 Lab2
 * Tianxiang Chen
 * 2017/08/19
 * 
 */

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

#define UppBound 5000
#define LowBound 0
using namespace std;

void insertR(stringstream &lineStream);
void modifyR(stringstream &lineStream);
void printR(stringstream &lineStream);
void printNode(stringstream &lineStream);
void deleteR(stringstream &lineStream);

//valid checking
bool NameChecking(stringstream &lineStream, string &name);
void NameChecking2(stringstream &lineStream, string &name);//For printR
void NameChecking3(stringstream &lineStream, string &name);//For deleteR
void NameChecking4(stringstream &lineStream, string &name);//For printNode
bool ResChecking(stringstream &lineStream, double &resistance);
bool ResChecking2(stringstream &lineStream, double &resistance);//For modifyR
bool NodeChecking(stringstream &lineStream, int &nodeid);
bool Node2Checking(stringstream &lineStream, int &nodeid1, int &nodeid2);
bool TooFewArguChecking(stringstream &lineStream);
bool TooManyArguChecking(stringstream &lineStream);


//error printing function
void Print_InvalidCom();
void Print_InvalidArgu();
void Print_NegRes();
void Print_NodeExceed(int nodeid);
void Print_NoAll();
void Print_SameTerminal(int nodeid);
void Print_TooManyArgu();
void Print_ToofewArgu();


int Parser() {
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
            insertR(lineStream);
        }
        else if (command == "modifyR") {
            modifyR(lineStream);
        }
        else if (command == "printR"){
            printR(lineStream);
        }
        else if (command == "printNode"){
            printNode(lineStream);
        }
        else if (command == "deleteR"){
            deleteR(lineStream);
        }
        else
            Print_InvalidCom();
    }
    //one operation done, waiting for the next input.
    cout<<"> ";
    getline (cin, line);
}
// End input loop until EOF.
return 0;
}

int main(){
    Parser();
    return 0;
}
void insertR(stringstream &lineStream){
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
    cout<<"Inserted: resistor "<<name<<" "<<setprecision(2)<<std::fixed
            <<resistance<<" Ohms "<<nodeid1<<" -> "<<nodeid2<<endl;
}

void modifyR(stringstream &lineStream){
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
    cout<<"Modified: resistor "<<name<<" to "<<setprecision(2)<<std::fixed
            <<resistance<<" Ohms"<<endl;
}

void printR(stringstream &lineStream){
    string name;
    if (TooFewArguChecking(lineStream))
        return;
    NameChecking2(lineStream, name);
}

void printNode(stringstream &lineStream){
    string name;
    if (TooFewArguChecking(lineStream))
        return;
    NameChecking4(lineStream, name);
}

void deleteR(stringstream &lineStream){
    string name;
    if (TooFewArguChecking(lineStream))
        return;
    NameChecking3(lineStream, name);
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

void NameChecking2(stringstream &lineStream, string &name){//For printR
    if(TooFewArguChecking(lineStream))
        return;
        
    lineStream >> name;
     if (TooManyArguChecking(lineStream)){
        return;
    }
    if(name == "all")
        cout<<"Print: all resistors"<<endl;
    else
        cout<<"Print: resistor "<<name<<endl;
}

void NameChecking3(stringstream &lineStream, string &name){//For deleteR
    if(TooFewArguChecking(lineStream))
        return;
    
    lineStream >> name;
     if (TooManyArguChecking(lineStream)){
        return;
    }
    if(name == "all")
        cout<<"Deleted: all resistors"<<endl;
    else
        cout<<"Deleted: resistor "<<name<<endl;
}




void NameChecking4(stringstream &lineStream, string &name){//For printNode
    if(TooFewArguChecking(lineStream))
        return;
    
    int nodeid;
    lineStream >> name;
    //if not all, convert into an int nodeid
    if(name != "all"){
        stringstream stoi_convert;//string to integer converter
        stoi_convert << name;
        stoi_convert >> nodeid;
    
        if(stoi_convert.fail()){
            Print_InvalidArgu();
            return;
        }
        else if( stoi_convert.peek()!=' ' && !stoi_convert.eof()){
            Print_InvalidArgu();
            return;
        }
        else if(nodeid<LowBound || nodeid>UppBound){
            Print_NodeExceed(nodeid);
            return;
        }
    }
    
    if (TooManyArguChecking(lineStream)){
        return;
    }
    if(name == "all")
        cout<<"Print: all nodes"<<endl;
    else
        cout<<"Print: node "<<nodeid<<endl;
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
    else if(nodeid<LowBound || nodeid>UppBound){
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
    else if(nodeid2<LowBound || nodeid2>UppBound){
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
void Print_NodeExceed(int nodeid){
    cout<<"Error: node "<<nodeid<<" is out of permitted range "<<LowBound<<
            "-"<<UppBound<<endl;
}
void Print_NoAll(){
    cout<<"Error: resistor name cannot be the keyword \"all\""<<endl;
}
void Print_SameTerminal(int nodeid){
    cout<<"Error: both terminals of resistor connect to node "<<nodeid<<endl;
}
void Print_TooManyArgu(){
    cout<<"Error: too many arguments"<<endl;
}
void Print_ToofewArgu(){
    cout<<"Error: too few arguments"<<endl;
}