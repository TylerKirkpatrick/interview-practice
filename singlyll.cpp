#include <iostream>
#include <string>
#include <map>
#include <stdlib.h>     /* srand, rand */

using namespace std;

struct node {
    public:
        int data;
        node * nextNode;

    node() {
        this->data = -1;
        this->nextNode = nullptr;
    }

    node(int data) {
        this->data = data;
        this->nextNode = nullptr;
    }

};

class SLL {
    public:
        node * head;

    SLL() {
        this->head = new node();
    }

    SLL(int data) {
        this->head = new node(data);
    }

    void addToHead(int data) { 
        node * currentPointer = this->head;
        while(currentPointer->nextNode != nullptr) {
            currentPointer = currentPointer->nextNode;
        }
        //reached the end...
        node * toAdd = new node(data);
        currentPointer->nextNode = toAdd;

    }

    void addToBack(int data) {
        node * toAdd = new node(data);
        node * wasHead = this->head;
        node * wasSecondNode = this->head->nextNode;
        this->head = toAdd; //new head
        toAdd->nextNode = wasHead; //new head points to former head...
        wasHead->nextNode = wasSecondNode; //former head now points to THIRD node

    }

    void addToIndex(int data, int index) {
        if(index == 0) {
            this->addToBack(data);
            return;
        }
        node * currentPointer = this->head;
        int counter = 0;
        while(currentPointer->nextNode != nullptr) {
            if(counter == index -1) {
                // a -> b
                // a -> x -> b , we are adding x...
                node * nodeToAdd = new node(data);

                nodeToAdd->nextNode = currentPointer->nextNode;
                
                currentPointer->nextNode = nodeToAdd;

                return;

            } else {
                currentPointer = currentPointer->nextNode;                
            }

            counter += 1;
        }
        this->addToHead(data);
        

    }

    int  getFirst() {
        int firstData = this->head->data;
        return firstData;
    }

    int getLast() {
        node * currentPointer = this->head;
        while(currentPointer->nextNode != nullptr) {
            currentPointer = currentPointer->nextNode;
        }
        //reached the end...
        return currentPointer->data;
    }

    int getSpecific(int nodeIndex) {
        //0 is first node...
        int counter = 0;
        node * currentPointer = this->head;
        while(counter < nodeIndex) {
            if(currentPointer->nextNode == nullptr) {
                return -1;
            }

            currentPointer = currentPointer->nextNode;
            counter += 1;
        }
        //reached the end...
        return currentPointer->data;
    }

    void printSLL() {
        node * currentPointer = this->head;
        cout<<endl;
        cout<<currentPointer->data<<" -> ";
        while(currentPointer->nextNode != nullptr) {
            cout<<currentPointer->nextNode->data<<" -> ";
            currentPointer = currentPointer->nextNode;
        }
        cout<<endl;
        //reached the end...
        
    }

    void removeIndex(int index) {
        if(index == 0) {
            node * toMakeHead = this->head->nextNode;
            delete this->head;
            this->head = toMakeHead;

        } else {
            node * currentPointer = this->head;
            int counter = 0;

            if(currentPointer->nextNode->nextNode == nullptr) {
                // d -> e -> nullptr
                delete currentPointer->nextNode;
                currentPointer->nextNode = nullptr;
                // d -> nullptr
                return;
            }

            while(currentPointer->nextNode != nullptr) {
                if(counter == index - 1) {
                    // a -> b -> c
                    // to...
                    // a -> c
                    node * toSetAsNext = currentPointer->nextNode->nextNode;
                    delete currentPointer->nextNode;
                    currentPointer->nextNode = toSetAsNext;
                    
                    return;

                }
                currentPointer = currentPointer->nextNode;
                counter += 1;
            }

        }

    }

};

int main() {

    SLL myList(0);
    
    for(int i = 0; i < 1000; i++) {
        myList.addToHead(i);
        int rand_num = rand() % 10 + 1; 
        if(rand_num == 1) {
            myList.addToBack(rand_num);
        } else if(rand_num == 2) {
            myList.addToHead(rand_num);
        }
    }
    

    //myList.addToIndex(100, 3);
    /*
    myList.removeIndex(0);
    myList.removeIndex(0);

    myList.addToBack(2);
    myList.addToBack(1);
    */

    myList.printSLL();
    
    
    
    
    
}