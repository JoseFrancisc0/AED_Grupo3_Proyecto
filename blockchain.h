#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "block.h"
#include "hashtable.h"
#include <vector>
#include <stdexcept>
using namespace std;

class BlockChain {
    private:
        struct Node {
            Block block;
            Node *next = nullptr;

            Node(Block _block) : block(_block) {};
        };

        Node *head = nullptr;
        HashTable<string, Transaction> table;

        void constructHashTable(){
            Node* current = head;

            while(current != nullptr){
                const Block& nodeBlock = current->block;
                const string& key = nodeBlock.getBlockhash();
                const Transaction& value = nodeBlock.getTransaction();

                table.insert(key, value);

                current = current->next;
            }
        }

    public:
        BlockChain() = default;

        ~BlockChain() {
            Node *current = head;
            while (current != nullptr) {
                Node *temp = current;
                current = current->next;
                delete temp;
            }
        }

        /// Inserta transacciones
        void addTransaction(Transaction _transaction) {
            if (head == nullptr) { /// Blockchain vacia : bloque genesis
                Block newBlock(_transaction, "");
                Node *newNode = new Node(newBlock);
                head = newNode;
            } else { /// Insertar bloque al final
                Block newBlock(_transaction, head->block.getPrevhash());
                Node *newNode = new Node(newBlock);

                Node *temp = head;
                while (temp->next != nullptr)
                    temp = temp->next;

                temp->next = newNode;
            }
        }

        /// El nro de transacciones (y de bloques)
        int getBlockCount(){
            int count = 0;
            if(head == nullptr)
                return count;

            Node* current = head;
            while(current->next != nullptr){
                count++;
                current = current->next;
            }

            return count;
        }

        /// El bloque mas reciente
        Block getLatestBlock(){
            if(head == nullptr)
                throw std::out_of_range("BlockChain is empty.");

            Node* current = head;
            while(current->next != nullptr)
                current = current->next;

            return current->block;
        }

        /// Equal to X: Hash Table
        Transaction searchByKey(string key);
        Transaction searchByIndex(int index);

        vector<Block> range_search(int begin, int end); /// Between X and Y: AVL Tree
        void cascadeRecalculation(); /// Recalculo en cascada
        Block deleteRecordatIndex(int key); /// Elimina registros por indice

        /// Validacion de la blockchain
        bool validateBlockchain(){
            Node* current = head;
            while(current->next != nullptr){
                if(current->block.getBlockhash() != current->block.calculateHash()) /// Check current hash validity
                    return false;

                if(current->block.getBlockhash() != current->next->block.getPrevhash()) /// Check previous hash validity
                    return false;

                current = current->next;
            }

            return true;
        }

        void loadFromTextfile(); /// Carga de datos por csv
};

#endif //BLOCKCHAIN_H
