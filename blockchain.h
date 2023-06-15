#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "avl.h"
#include "block.h"
#include "hashtable.h"
#include "minheap.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
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
        MinHeap<string, Transaction> minHeap;

        /// Construye el hash tabla
        void buildHashTable(){
            table.clear(); /// Reset table

            Node* current = head;
            while(current != nullptr){
                table.insert(current->block.getBlockhash(), current->block.getTransaction());
                current = current->next;
            }
        }

        /// Construye el AVL
        void buildAVL(){
            tree.clear(); /// Reset avl

            Node* current = head;
            while(current != nullptr){
                tree.insert(current->block.getBlockhash(), current->block.getTransaction());
                current = current->next;
            }
        }

        /// Construye el MinHeap
        void buildMinHeap(){
            minHeap.clear();

            Node* current = head;
            while(current != nullptr){
                minHeap.insert(current->block.getBlockhash(), current->block.getTransaction());
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

                table.insert(newBlock.getBlockhash(), _transaction); /// Actualiza tabla hash
            }
            else { /// Insertar bloque al final
                Node *temp = head;
                while (temp->next != nullptr)
                    temp = temp->next;

                Block newBlock(_transaction, temp->block.getBlockhash());
                Node* newNode = new Node(newBlock);

                temp->next = newNode;
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

        /// Equal to X: Hash Table
        Transaction search(const string& key){
            buildHashTable();
            return table.search(key);
        }

        /// Between X and Y: AVL Tree
        vector<Transaction> range_search(const string& begin, const string& end){
            buildAVL();
            return tree.range_search(begin, end);
        }

        /// Recalculo en cascada; valida la blockchain
        void cascadeRecalculation(){
            Node* current = head;

            /// Si head es eliminado, nuevo head pasa a ser Genesis block
            if(!current->block.getPrevhash().empty())
                current->block.setPrevHash("");

            while(current != nullptr){
                Block& block = current->block;

                Node* nextNode = current->next;
                if(nextNode != nullptr){
                    Block& nextBlock = nextNode->block;
                    nextBlock.setPrevHash(block.getBlockhash());
                }

                block.mineBlock();

                current = current->next;
            }
        }

        /// Elimina registros por indice: NO HACE RECALCULO EN CASCADA
        void deleteRecordatIndex(int index){
            if(index < 0 || index >= getBlockCount())
                throw std::out_of_range("Invalid index.");

            /// delete head
            if(index == 0){
                Node* temp = head;
                head = head->next;
                delete temp;
                return;
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
            delete current;
        }

        /// Carga de datos por csv : NO TESTEADO TODAVIA
        void loadFromCSV(const string& csv){
            ifstream file(csv);
            if(!file.is_open())
                throw std::runtime_error("Failed to open file " + csv);

            string line;
            while(getline(file, line)){
                stringstream ss(line);
                string _client, _location, _amountStr;
                if(getline(ss, _client, ',') && getline(ss, _location, ',') && getline(ss, _amountStr, ',')){
                    double _amount = stod(_amountStr);
                    Transaction _transaction(_client, _location, _amount);
                    addTransaction(_transaction);
                }
            }

            file.close();
        }

        void printBlockchain(){
            Node* current = head;
            int i = 1;
            cout << "|------BLOCKCHAIN------|" << endl;
            while(current != nullptr){
                cout << "BLOQUE " << i << ":" << endl;
                current->block.printBlock();
                cout << '\n';
                current = current->next;
                i++;
            }
        }
};

#endif //BLOCKCHAIN_H
