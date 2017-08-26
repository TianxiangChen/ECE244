/*
 * This file implements the parser function of the program
 */
#include "Parser.h"


void Parser() {
    TreeDB *tree = new TreeDB();
    string line, command;
    cout<<"> ";
    getline (cin, line);
    
    while ( !cin.eof () ) {
        stringstream lineStream (line);
        lineStream >> command;

        if (command == "insert") {
            insert(lineStream, tree);
        }
        else if (command == "find") {
            find(lineStream, tree);
        }
        else if (command == "remove"){
            remove(lineStream, tree);
        }
        else if (command == "printall"){
            printall(tree);
        }
        else if (command == "printprobes"){
            printprobes(lineStream, tree);
        }
        else if (command == "removeall"){
            removeall(tree);
        }
        else if (command == "countactive"){
            countactive(tree);
        }
        else if (command == "updatestatus"){
            updatestatus(lineStream, tree);
        }
        else
            ;
        
        //one operation done, waiting for the next input.
        cout<<"> ";
        getline (cin, line);
    }
    delete tree;
    tree = NULL;
    // End input loop until EOF.
}

void insert(stringstream &lineStream, TreeDB *tree){
    string name;
    unsigned int IPaddress;
    string status;
    bool active;
    
    lineStream >> name;
    lineStream >> IPaddress;
    lineStream >> status;
    active=active_converter(status);
    
    DBentry *newEntry = new DBentry(name, IPaddress, active);
    tree->insert(newEntry);
}

void find(stringstream &lineStream, TreeDB *tree){
    string name;
    lineStream >> name;
    cout<<tree->find(name);

}

void remove(stringstream &lineStream, TreeDB *tree){
    string name;
    lineStream >> name;
    tree->remove(name);
}

void printall(TreeDB *tree){
    tree->printall();
}

void printprobes(stringstream &lineStream, TreeDB *tree){
    string name;
    lineStream >> name;
    tree->printProbes(name);
}

void removeall(TreeDB *tree){
    tree->clear();
}

void countactive(TreeDB *tree){
    tree->countActive();
}

void updatestatus(stringstream &lineStream, TreeDB *tree){
    string name, status;
    bool active;
    lineStream >> name;
    lineStream >> status;
    active = active_converter(status);
    tree->updatestatus(name, active);
}

bool active_converter(string status){
    if(status == "active")
        return true;
    else if(status == "inactive")
        return false;
    else{
        cout<<"Wrong status type input"<<endl;
        return false;
    }
}