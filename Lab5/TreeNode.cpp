#include "TreeNode.h"

// A useful constructor
TreeNode::TreeNode(DBentry* _entryPtr){
    entryPtr = _entryPtr;
    left = NULL;
    right = NULL;
}

// the destructor
TreeNode::~TreeNode(){
    delete entryPtr;
    entryPtr = NULL;
    left = NULL;
    right = NULL;
}

// sets the left child of the TreeNode.
void TreeNode::setLeft(TreeNode* newLeft){
    left = newLeft;
}

// sets the right child of the TreeNode
void TreeNode::setRight(TreeNode* newRight){
    right = newRight;
}

// gets the left child of the TreeNode.
TreeNode* TreeNode::getLeft() const{
    return left;
}

// gets the right child of the TreeNode
TreeNode* TreeNode::getRight() const{
    return right;
}

// returns a pointer to the DBentry the TreeNode contains. 
DBentry* TreeNode::getEntry() const{
    return entryPtr;
}

bool TreeNode::remove(string name, TreeNode* parent){
    if(this == NULL)
        return false;
    if(name > entryPtr->getName())
        return right->remove(name, this);
    if(name < entryPtr->getName())
        return left->remove(name, this);
    else{//found the node
        if(left==NULL && right==NULL){
            delete this;
            this == NULL;
            if(parent->getLeft() == this)
                parent->setLeft(NULL);
            if(parent->getRight() == this)
                parent->setRight(this);
        }
        else if(left == NULL){//only has right child
            if(parent->getLeft() == this)
                parent->setLeft(right);
            if(parent->getRight() == this)
                parent->setRight(right);
            delete this;
            this == NULL;
        }
        else if(right == NULL){//only has left child
            if(parent->getLeft() == this)
                parent->setLeft(left);
            if(parent->getRight() == this)
                parent->setRight(left);
            delete this;
            this == NULL;
        }
        else if(left != NULL && right != NULL){
            TreeNode *leftmax = left->findMax();
            //a deep copy of data from leftmax to the point we want to delete,
            //using a recursive method, we don't delete the point but modify its
            //value
            entryPtr->setActive(leftmax->getEntry()->getActive());
            entryPtr->setIPaddress(leftmax->getEntry()->getIPaddress());
            entryPtr->setName(leftmax->getEntry()->getName());
            left->remove(leftmax->getEntry()->getName(),this);//recursively remove
            //the node we move to the "deleted" position
        }
        return true;
    }
}

TreeNode* TreeNode::findMax(){//find the max node in the subtree
    if(right == NULL)
        return this;
    return right->findMax();
}