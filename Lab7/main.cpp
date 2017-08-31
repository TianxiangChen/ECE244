/* 
 * File:   main.cpp
 * Author: Tianxiang Chen
 * Lab7 --- Graphically Display the Resistor Network
 * Created on August 30, 2017, 2:59 PM
 * 
 * I still kept all the error checking from Lab2
 * I did not really follow the error print from the handout. Instead, I added
 * many other error checkings display to cover more cases, since this is a self-
 * practice, rather than an assignment
 * 
 * Also, I didnt follow the suggested data structure from the handout,which eases
 * the code writing but occupies more space. (It store the resistor info twice,
 * at both terminal nodes)
 * 
 * My approach is to create a resistorlist to save all the resistor info. And a
 * Nodelist to save all node info. Inside each node in the nodelist, a resistor
 * pointer is stored to points to the resistor info in the resistorlist.
 * 
 * This is the bonus lab based on Lab4. It adds a draw function, which displays
 * the whole network using a graphic library provided.
 */

#include <cstdlib>
#include "Parser.h"
using namespace std;
    
    

/*
 * 
 */
int main(int argc, char** argv) {
    Parser();
    return 0;
}

