#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "avl.h"
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
        AVL<string, Transaction> tree;

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

                table.insert(newBlock.getBlockhash(), _transaction); /// Actualiza tabla hash
            }
            else { /// Insertar bloque al final
                Block newBlock(_transaction, head->block.getPrevhash());
                Node *newNode = new Node(newBlock);

                Node *temp = head;
                while (temp->next != nullptr)
                    temp = temp->next;

                temp->next = newNode;

                table.insert(newBlock.getBlockhash(), _transaction); /// Actualiza tabla hash
                tree.insert(newBlock.getBlockhash(), _transaction); /// Actualiza arbol AVL
            }
        }

        /// El nro de transacciones (y de bloques)
        int getBlockCount(){
            int count = 0;
            if(head == nullptr)
                return count;

            Node* current = head;
            while(current != nullptr){
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
        Transaction search(const string& key){
            return table.search(key);
        }

        /// Between X and Y: AVL Tree
        vector<Transaction> range_search(const string& begin, const string& end){
            return tree.range_search(begin, end);
        }

        /// Recalculo en cascada
        void cascadeRecalculation(){
            Node* current = head;

            /// Si head es eliminado, nuevo head pasa a ser Genesis block
            if(!current->block.getPrevhash().empty())
                current->block.setPrevHash("");

            while(current != nullptr){
                Block& block = current->block;

                block.mineBlock();

                Node* nextNode = current->next;
                if(nextNode != nullptr){
                    Block& nextBlock = nextNode->block;
                    nextBlock.setPrevHash(block.getBlockhash());
                }

                current = current->next;
            }
        }

        /// Elimina registros por indice
        Block deleteRecordatIndex(int index){
            if(index < 0 || index >= getBlockCount())
                throw std::out_of_range("Invalid index.");

            /// delete head
            if(index == 0){
                Node* temp = head;
                head = head->next;
                Block deletedBlock = temp->block;
                delete temp;
                return deletedBlock;
            }

            Node* prev = nullptr;
            Node* current = head;
            int currentIndex = 0;
            while(currentIndex < index && current != nullptr){
                prev = current;
                current = current->next;
                currentIndex++;
            }

            prev->next = current->next;
            Block deletedBlock = current->block;
            delete current;
            table.remove(deletedBlock.getBlockhash()); /// Actualiza tabla hash
            tree.remove(deletedBlock.getBlockhash()); /// Actualiza arbol AVL

            cascadeRecalculation(); /// Recalcula al final
            return deletedBlock;
        }

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
