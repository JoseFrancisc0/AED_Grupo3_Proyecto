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

        void addTransaction(Transaction _transaction); /// Inserta transacciones
        int getTransactionCount(); /// El nro de transacciones (y de bloques)
        Block getLatestBlock(); /// El bloque mas reciente
        Block getBlockByIndex(); /// Busca por indice
        Block search(int key); /// Equal to X
        vector<Block> range_search(int begin, int end); /// Between X and Y
        void cascadeRecalculation(); /// Recalculo en cascada
        Block deleteRecordatIndex(int key); /// Elimina registros por indice
        bool validateBlockchain(); /// Validacion de la blockchain
        void loadFromTextfile(); /// Carga de datos por csv
};

#endif //BLOCKCHAIN_H
