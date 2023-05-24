#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "block.h"
#include <vector>
using namespace std;

class BlockChain{
    private:
        struct Node{
            Block block;
            Node* next = nullptr;

            Node(Block _block) : block(_block){};
        };
        Node* head = nullptr;

    public:
        BlockChain() = default;

        ~BlockChain(){
            Node* current = head;
            while(current != nullptr){
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
};

#endif //BLOCKCHAIN_H
