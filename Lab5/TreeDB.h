#ifndef _TREEDB_H
#define _TREEDB_H

#include "TreeNode.h"
#include "DBentry.h"

class TreeDB {

private:
   TreeNode* root;
   int active;
   // You will need to add additional private functions

public:
   // the default constructor, creates an empty database.
   TreeDB();

   // the destructor, deletes all the entries in the database.
   ~TreeDB();
   
   // delete helper function
   void delTree (TreeNode *st_root);
   
   // deletes all the entries in the database.
   void clear();
   
   // inserts the entry pointed to by newEntry into the database. 
   // If an entry with the same key as newEntry's exists 
   // in the database, it returns false. Otherwise, it returns true.
   bool insert(DBentry* newEntry); 

   // a helper function for insert
   bool insert_in_bst (TreeNode *ins, TreeNode *curr);
   // searches the database for an entry with a key equal to name.
   // If the entry is found, a pointer to it is returned.
   // If the entry is not found, the NULL pointer is returned.
   DBentry* find(string name);

   //a helper function for find
   DBentry* find_in_bst(string name, TreeNode *curr);
   
   void active_plus_one();
   void active_minus_one();
   
   void printall();
   //a helper function for print
   void print(TreeNode *curr);
   
   
   
   // deletes the entry with the specified name (key)  from the database.
   // If the entry was indeed in the database, it returns true.
   // Returns false otherwise.
   bool remove(string name);
   
   //a helper function for remove
   bool remove_in_bst(string name, TreeNode *prev, TreeNode *curr);
    
   // prints the number of probes for a specified name
   void printProbes(string name);
   // a helper function to print the  probesCount
   void printProbesHelper(string name, TreeNode *curr, int probe);
   
   // computes and prints out the total number of active entries
   // in the database (i.e. entries with active==true).
   void countActive () const;
   
   
   // updates the status of a required name
   void updatestatus(string name, bool status);
   // Prints the entire tree, in ascending order of key/name
   //friend ostream& operator<< (ostream& out, const TreeDB& rhs);
}; 

// You *may* choose to implement the function below to help print the 
// tree.  You do not have to implement this function if you do not wish to.
//ostream& operator<< (ostream& out, TreeNode* rhs);   
   
#endif 

