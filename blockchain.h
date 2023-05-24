#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "block.h"
#include <vector>
#include <stdexcept>
using namespace std;

class BlockChain{
    private:
        struct Node{
            Block block;
            Node* next;

            Node(const Block& _block): block(_block), next(nullptr){};
        };

        Node* head;

    public:
        BlockChain() : head(nullptr){};

        ~BlockChain(){
            Node* current = head;
            while (current != nullptr){
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }

        void addBlock(const Block& newBlock){
            Node* newNode = new Node(newBlock);
            if(head != nullptr){
                if(!validateBlock(newBlock))
                    throw std::invalid_argument("Invalid Block: previous hash does not match");

                Node* current = head;
                while(current->next != nullptr)
                    current = current->next;

                current->next = newNode;
            }
            else
                head = newNode;
        }

        bool validateBlock(const Block& block){
            Node* temp = head;
            while(temp->next != nullptr)
                temp = temp->next;

            if(block.getPrevhash() == temp->block.getBlockhash())
                return true;
            else
                return false;
        }
};

#endif //BLOCKCHAIN_H
