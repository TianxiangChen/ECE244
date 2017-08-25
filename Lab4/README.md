# ECE244 Lab4

 
 File:   main.cpp
 Author: Tianxiang Chen
 Lab4 --- A Resistor Network Simulator
 Created on August 23, 2017, 2:59 PM
 
 I still kept all the error checking from Lab2.
 I did not really follow the error print from the handout. Instead, I added
 many other error checkings display to cover more cases, since this is a self-
 practice, rather than an assignment.
 
 Also, I didnt follow the suggested data structure from the handout,which eases
 the code writing but occupies more space. (It store the resistor info twice,
 at both terminal nodes)
 
 My approach is to create a resistorlist to save all the resistor info. And a
 Nodelist to save all node info. Inside each node in the nodelist, a resistor
 pointer is stored to points to the resistor info in the resistorlist. 

