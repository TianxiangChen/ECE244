#include "TreeDB.h"

// the default constructor, creates an empty database.
TreeDB::TreeDB(){
    root = NULL;
    active = 0;
}

// the destructor, deletes all the entries in the database.
TreeDB::~TreeDB(){
    if (root == NULL)
        return;
    // Helper function, facilitates recursion.
    // Make a private function of class Tree.
    delTree (root);
    root = NULL;
    active = 0;
    
}

// delete helper function
void TreeDB::delTree (TreeNode *st_root){
    if (st_root == NULL)
        return;
    // Basis: at end of branch
    delTree (st_root->getLeft());
    delTree (st_root->getRight());
    // All nodes below st_root done, safe to delete
    delete st_root;
    st_root = NULL;
}
   
void TreeDB::clear(){
    this->~TreeDB();
    cout<<"Success"<<endl;
}

void TreeDB::active_plus_one(){
    active++;
}

void TreeDB::active_minus_one(){
    active--;
}

void TreeDB::printall(){
    if(root == NULL)
        return;
    print(root);
}
//a helper function for print
void TreeDB::print(TreeNode *curr){
    if(curr->getLeft() != NULL)
        print(curr->getLeft());
    curr->getEntry()->print();
    if(curr->getRight() != NULL)
        print(curr->getRight());
}

bool TreeDB::insert(DBentry* newEntry){
    TreeNode *ins = new TreeNode (newEntry);
    if (root == NULL) { // Basis
    root = ins;
    root->setLeft(NULL);
    root->setRight(NULL);
    if(ins->getEntry()->getActive())
        active_plus_one();
    cout<<"Success"<<endl;
    return true;
    }
    // Private helper function for recursion
    return insert_in_bst (ins, root);

}

// a helper function for insert
bool TreeDB::insert_in_bst (TreeNode *ins, TreeNode *curr){
    if (ins->getEntry()->getName() == curr->getEntry()->getName()){
        cout<<"Error: entry already exists"<<endl;
        delete ins;
        return false; // No repeat insertions
    }
    if (ins->getEntry()->getName() < curr->getEntry()->getName()) { // Go left
        if (curr->getLeft() == NULL){
            curr->setLeft(ins); // Found spot
            if(ins->getEntry()->getActive())
                active_plus_one();
            cout<<"Success"<<endl;
            return true;
        }
        else
            insert_in_bst (ins, curr->getLeft());
    }
    else {
        if (curr->getRight() == NULL){
            curr->setRight(ins);    // Found spot
            if(ins->getEntry()->getActive())
                active_plus_one();
            cout<<"Success"<<endl;
            return true;
        }
        else
            insert_in_bst (ins, curr->getRight());
    }        
}

DBentry* TreeDB::find(string name){
    if(root == NULL){
        cout<<"Error: entry does not exist"<<endl;
        return NULL;
    }
    return find_in_bst(name,root);
}

//a helper function for find
DBentry* TreeDB::find_in_bst(string name, TreeNode *curr){
    if(curr->getEntry()->getName() == name){//found
                return curr->getEntry();
    }
    else if(curr->getEntry()->getName() > name){//go left
        if(curr->getLeft() == NULL){//nothing left
            cout<<"Error: entry does not exist"<<endl;
            return NULL;
        }
        else
            return find_in_bst(name,curr->getLeft());
    }
    else if(curr->getEntry()->getName() < name){//go right
        if(curr->getRight() == NULL){//nothing left
            cout<<"Error: entry does not exist"<<endl;
            return NULL;
        }
        else
            return find_in_bst(name,curr->getRight());
    }
}
/*
bool TreeDB::remove(string name){
    if(root == NULL){
        cout<<"Error: entry does not exist"<<endl;
        return false;
    }
    else if (root->getEntry()->getName() == name){//delete root
        if(root->getEntry()->getActive())//active minus one
            active_minus_one();
        if(root->getLeft() == NULL && root->getRight() == NULL){//only root
            delete root;
            root = NULL;
            cout<<"Success"<<endl;
            return true;
        }
        else if(root->getLeft() == NULL){//no left child, use right's leftmost one
            if(root->getRight()->getLeft() == NULL){//right child has no left child
                TreeNode *temp = root;
                root = root->getRight();
                delete temp;
                temp = NULL;
            }
            else{//right child has left child
                TreeNode *prev = root->getRight();
                TreeNode *curr = root->getRight()->getLeft();
                while(curr->getLeft() != NULL){
                    prev = curr;
                    curr = curr->getLeft();
                }//found right's leftmost child at curr
                if(curr->getRight() != NULL)
                    prev->setLeft(curr->getRight());
                else
                    prev->setLeft(NULL);
                TreeNode *temp = root;
                curr->setRight(root->getRight());
                root = curr;
                delete temp;
                temp = NULL;
            }
            cout<<"Success"<<endl;
            return true;
        }
        else{//has left child
            if(root->getLeft()->getRight() == NULL){//left child has no right child
                TreeNode *temp = root;
                root->getLeft()->setRight(root->getRight());
                root = root->getLeft();
                delete temp;
                temp = NULL;
            }
            else{//left child has right child
                TreeNode *prev = root->getLeft();
                TreeNode *curr = root->getLeft()->getRight();
                while(curr->getRight() != NULL){
                    prev = curr;
                    curr = curr->getRight();
                }//found left's rightmost child at curr
                if(curr->getLeft() != NULL)
                    prev->setRight(curr->getRight());
                else
                    prev->setRight(NULL);
                TreeNode *temp = root;
                curr->setRight(root->getRight());
                root = curr;
                delete temp;
                temp = NULL;
            }
            cout<<"Success"<<endl;
            return true;
        }
    }
    else{
        TreeNode *prev = NULL;
        TreeNode *curr = root;
        remove_in_bst(name,prev,curr);
    }
}*/
bool TreeDB::remove(string name){
    if(root == NULL){
        cout<<"Error: entry does not exist"<<endl;
        return false;
    }
    else if (root->getEntry()->getName() == name){//delete root
        if(root->getEntry()->getActive())//active minus one
            active_minus_one();
        if(root->getLeft() == NULL && root->getRight() == NULL){//only root
            delete root;
            root = NULL;
            cout<<"Success"<<endl;
            return true;
        }
        else if(root->getLeft() == NULL){//no left child, use right
            TreeNode *temp = root;
            root = root->getRight();
            delete temp;
            temp = NULL;
        }
        else if(root->getRight() == NULL){//no right child, use left
            TreeNode *temp = root;
            root = root->getLeft();
            delete temp;
            temp = NULL;
        }
        else{//both right and left
            if(root->getLeft()->getRight() == NULL){//left child has no right child
                TreeNode *temp = root;
                root->getLeft()->setRight(root->getRight());
                root = root->getLeft();
                delete temp;
                temp = NULL;
            }
            else{//left child has right child
                TreeNode *prev = root->getLeft();
                TreeNode *curr = root->getLeft()->getRight();
                while(curr->getRight() != NULL){
                    prev = curr;
                    curr = curr->getRight();
                }//found left's rightmost child at curr
                if(curr->getLeft() != NULL)
                    prev->setRight(curr->getRight());
                else
                    prev->setRight(NULL);
                TreeNode *temp = root;
                curr->setRight(root->getRight());
                root = curr;
                delete temp;
                temp = NULL;
            }
            cout<<"Success"<<endl;
            return true;
        }
    }
    else{
        TreeNode *prev = NULL;
        TreeNode *curr = root;
        remove_in_bst(name,prev,curr);
    }
}


//a helper function for remove
bool TreeDB::remove_in_bst(string name, TreeNode *prev, TreeNode *curr){
    if(curr->getEntry()->getName() == name){//found
        if(curr->getEntry()->getActive())
            active_minus_one();
        if(curr->getLeft() == NULL && curr->getRight() == NULL){//leaf
            if(prev->getEntry()->getName() > curr->getEntry()->getName())
                prev->setLeft(NULL);
            else
                prev->setRight(NULL);
            delete curr;
            curr = NULL;
        }
        else if(curr->getLeft() == NULL){//no left child, use right child
            if(prev->getEntry()->getName() > curr->getEntry()->getName())
                prev->setLeft(curr->getRight());
            else
                prev->setRight(curr->getRight());
            delete curr;
            curr = NULL;           
        }
        else if(curr->getRight() == NULL){//no right child, use left child
            if(prev->getEntry()->getName() > curr->getEntry()->getName())
                prev->setLeft(curr->getLeft());
            else
                prev->setRight(curr->getLeft());
            delete curr;
            curr = NULL; 
        }
        else{//has left child and right child
            if(curr->getLeft()->getRight() == NULL){//left child has no right child
                if(prev->getEntry()->getName() > curr->getEntry()->getName()){
                    prev->setLeft(curr->getLeft());
                    curr->getLeft()->setRight(curr->getRight());
                }
                else{
                    prev->setRight(curr->getRight());
                    curr->getLeft()->setLeft(curr->getLeft());
                }
                delete curr;
                curr = NULL;
            }
            else
            {
                TreeNode *prev_temp = curr;
                TreeNode *curr_temp = curr->getLeft();
                while(curr_temp->getRight() != NULL){
                    curr_temp = prev_temp;
                    curr_temp = curr_temp->getRight();
                }//found left's rightmost child at curr_temp
                if(curr_temp->getLeft() == NULL)
                    prev_temp->setRight(NULL);
                else//right's leftmost one has a right child
                    prev_temp->setRight(curr_temp->getLeft());
                if(prev->getEntry()->getName() > curr->getEntry()->getName()){
                    prev->setLeft(curr_temp);
                    curr_temp->setLeft(curr->getLeft());
                    curr_temp->setRight(curr->getRight());
                }
                else{
                    prev->setRight(curr_temp);
                    curr_temp->setLeft(curr->getLeft());
                    curr_temp->setRight(curr->getRight());
                }
                delete curr;
                curr = NULL;
            }
        }
        cout<<"Success"<<endl;       
        return true;
    }
    else if(curr->getEntry()->getName() > name){//go left
        if(curr->getLeft() == NULL){//nothing left
            cout<<"Error: entry does not exist"<<endl;
            return false;
        }
        else
            remove_in_bst(name,curr,curr->getLeft());
    }
    else if(curr->getEntry()->getName() < name){//go right
        if(curr->getRight() == NULL){//nothing left
            cout<<"Error: entry does not exist"<<endl;
            return false;
        }
        else
            remove_in_bst(name,curr,curr->getRight());
    }
}

// prints the number of probes for a specified name
void TreeDB::printProbes(string name){
    int probe = 1;
    if(root == NULL)
        cout<<"Error: entry does not exist"<<endl;
    if(root->getEntry()->getName() == name){
        cout<<probe<<endl;
        return;
    }
    printProbesHelper(name, root, probe);
}

// a helper function to print the  probesCount
void TreeDB::printProbesHelper(string name, TreeNode *curr, int probe){
    if(curr->getEntry()->getName() == name){
        cout<<probe<<endl;
        return;
    }
    
    if(curr->getLeft()== NULL && curr->getRight() == NULL &&
            curr->getEntry()->getName() != name){
        cout<<"Error: entry does not exist"<<endl;
        return;
    }
    
    if(curr->getEntry()->getName() > name)
        printProbesHelper(name, curr->getLeft(), probe+1);
    else if(curr->getEntry()->getName() < name)
        printProbesHelper(name, curr->getRight(), probe+1);
}
   
void TreeDB::countActive () const{
    cout<<active<<endl;
}

void TreeDB::updatestatus(string name, bool status){
    DBentry *temp = find(name);
    if(temp != NULL){
        if(status == true){
            if(temp->getActive() == false)
                active_plus_one();
        }
        if(status == false){
            if(temp->getActive() == true)
                active_minus_one();
        }
        temp->setActive(status);
        cout<<"Success"<<endl;
    }
}

// Prints the entire tree, in ascending order of key/name
//friend ostream& operator<< (ostream& out, const TreeDB& rhs);