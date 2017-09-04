#include <iostream>
#include <map>
#include <stdlib.h>     /* srand, rand */

using namespace std;

struct node {
public:
    int data;
    node * leftPtr;
    node * rightPtr;
    node * parentPtr;
    int node_height = 0;

    node() {
        this->data = -1;
        this->leftPtr = nullptr;
        this->rightPtr = nullptr;
        this->parentPtr = nullptr;
        this->node_height = 0;
    }

    node(int data) {
        this->data = data;
        this->leftPtr = nullptr;
        this-> rightPtr = nullptr;
        this->parentPtr = nullptr;
        this->node_height = 0;
    }
    node(int data, node * parentPtr) {
        this->data = data;
        this->leftPtr = nullptr;
        this->rightPtr = nullptr;
        this->parentPtr = parentPtr;
        this->node_height = 0;
    }
    node(int data, node * leftPtr, node * rightPtr, node * parentPtr) {
        this->data = data;
        this->leftPtr = leftPtr;
        this->rightPtr = rightPtr;
        this->parentPtr = parentPtr;
        this->node_height = 0;
    }
    void setLeftPtr(node * leftPtr) {
        this->leftPtr=leftPtr;
    }
    void setRightPtr(node * rightPtr) {
        this->rightPtr=rightPtr;
    }
    void setParentPtr(node *& parentPtr) {
        this->parentPtr=parentPtr;
    }
    void setHeight(int height) {
        this->node_height = height;
    }
    int getData() {
        return this->data;
    }
    node * getLeftPtr() {
        return this->leftPtr;
    }
    node * getRightPtr() {
        return this->rightPtr;
    }
    node * getParentPtr() {
        return this->parentPtr;
    }
    int getHeight() {
        return this->node_height;
    }
    void deletePointers() {
        delete this->leftPtr;
        delete this->rightPtr;
        delete this->parentPtr;
    }
    //added functions:
    int height(node * p) {
        return p ? p->node_height : 0;
    }
    int bfactor(node * p) {
        return height(p->rightPtr) - height(p->leftPtr);
    }
    void fixheight(node* p) {
        unsigned char hl = height(p->leftPtr);
        unsigned char hr = height(p->rightPtr);
        p->node_height = (hl>hr ? hl : hr) + 1;
    }

    //right rotation around p, returns new root node
    node* rotateright(node* p) {
        node* q = p->leftPtr;
        p->leftPtr = q->rightPtr;
        q->rightPtr = p;
        fixheight(p);
        fixheight(q);
        return q;
    }
    // the left rotation round q, returns new root node
    node* rotateleft(node* q) {
        node* p = q->rightPtr;
        q->rightPtr = p->leftPtr;
        p->leftPtr = q;
        fixheight(q);
        fixheight(p);
        return p;
    }
    // p node balance
    node* balance(node* p) {
        fixheight(p);
        if( bfactor(p)==2 )
        {
            if( bfactor(p->rightPtr) < 0 )
                p->rightPtr = rotateright(p->rightPtr);
            return rotateleft(p);
        }
        if( bfactor(p)==-2 )
        {
            if( bfactor(p->leftPtr) > 0  )
                p->leftPtr = rotateleft(p->leftPtr);
            return rotateright(p);
        }
        return p; // no balance needed
    }
    // k key insertion in the tree with p root
    node* insert(node* p, int k)
    {
        if( !p ) return new node(k);
        if( k<p->data )
            p->leftPtr = insert(p->leftPtr,k);
        else
            p->rightPtr = insert(p->rightPtr,k);
        return balance(p);
    }
    // searching the node with the minimal key in p tree 
    node* findmin(node* p) {
        return p->leftPtr?findmin(p->leftPtr):p;
    }
    // deleting the node with the minimal key from p tree 
    node* removemin(node* p)
    {
        if( p->leftPtr==0 )
            return p->rightPtr;
        p->leftPtr = removemin(p->leftPtr);
        return balance(p);
    }
    // k key deletion from p tree
    node* remove(node* p, int k) {
        if( !p ) return 0;
        if( k < p->data )
            p->leftPtr = remove(p->leftPtr,k);
        else if( k > p->data )
            p->rightPtr = remove(p->rightPtr,k);	
            else //  k == p->key 
        {
            node* q = p->leftPtr;
            node* r = p->rightPtr;
            delete p;
            if( !r ) return q;
            node* min = findmin(r);
            min->rightPtr = removemin(r);
            min->leftPtr = q;
            return balance(min);
        }
        return balance(p);
    }

};

class AVLTree {
private:
    node * root;

public:
    AVLTree() {
        this->root = nullptr;
    }
    AVLTree(int data) {
        this->root = new node(data);
    }
    ~AVLTree() {
        delete this->root; //? Might need to go through and delete all of the nodes :/
    }
    node * getRoot() {
        return this->root;
    }
    void addNode(int data) {
        
        this->root = this->root->insert(this->root, data);
        /*
        if(this->root == nullptr) {
            this->root = new node(data);
        } else {
            if(data < this->root->getData()) {
                //left side...
                if(this->root->getLeftPtr() == nullptr) {
                    node * newPtr = new node(data);
                    this->root->setLeftPtr(newPtr);
                    newPtr->setParentPtr(this->root);
                    return;
                }
                node * currentPtr = this->root->getLeftPtr();
                while(currentPtr != nullptr) {
                    if(data < currentPtr->getData()) {
                        if(currentPtr->getLeftPtr() == nullptr) {
                            //finally found our home...
                            node * newPtr = new node(data);
                            currentPtr->setLeftPtr(newPtr);
                            newPtr->setParentPtr(currentPtr);
                            return;
                        }
                        currentPtr = currentPtr->getLeftPtr();
                    } else {
                        if(currentPtr->getRightPtr() == nullptr) {
                            //finally found our home...
                            node * newPtr = new node(data);
                            currentPtr->setRightPtr(newPtr);
                            newPtr->setParentPtr(currentPtr);
                            return;
                        }
                        currentPtr = currentPtr->getRightPtr();
                    }
                }

            } else {
                //right side...
                node * currentPtr = this->root->getRightPtr();
                while(currentPtr != nullptr) {
                    if(data < currentPtr->getData()) {
                        if(currentPtr->getLeftPtr() == nullptr) {
                            //finally found our home...
                            node * newPtr = new node(data);
                            currentPtr->setLeftPtr(newPtr);
                            newPtr->setParentPtr(currentPtr);
                            return;
                        }
                        currentPtr = currentPtr->getLeftPtr();
                    } else {
                        if(currentPtr->getRightPtr() == nullptr) {
                            //finally found our home...
                            node * newPtr = new node(data);
                            currentPtr->setRightPtr(newPtr);
                            newPtr->setParentPtr(currentPtr);
                            return;
                        }
                        currentPtr = currentPtr->getRightPtr();
                    }
                }


            }//end if right side
        }
        */
    }//end addNode

    //visits the left branch, then middle, then right branch
    void inOrder(node * root) {
        if(root != nullptr) {
            inOrder(root->leftPtr);
            cout<< root->data << " -> ";
            inOrder(root->rightPtr);
        }
    }

    //visits the middle node before its two(or one) child node(s)
    void preOrder(node * root) {
        if(root != nullptr) {
            cout<< root->data << " -> ";
            preOrder(root->leftPtr);
            preOrder(root->rightPtr);
        }
    }

    //visits the middle node after its child nodes...
    //here, the root node is ALWAYS the LAST node visited!!!
    void postOrder(node * root) {
        cout<<"iteration"<<endl;
        if(root != nullptr) {
            postOrder(root->leftPtr);            
            postOrder(root->rightPtr);
            cout<< root->data << " -> ";
        }
    }

};

int main() {
    AVLTree avl;

    int rand_num = 0;
    for(int i = 0; i < 100; i++) {
        rand_num = rand() % 1000 + 1;
        avl.addNode(rand_num);
    }

    avl.postOrder(avl.getRoot());

    return 0;

}