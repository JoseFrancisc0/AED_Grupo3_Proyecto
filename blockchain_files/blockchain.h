#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "block.h"
#include "../data_structures/avl.h"
#include "../data_structures/hashtable.h"
#include "../data_structures/maxheap.h"
#include "../data_structures/minheap.h"
#include "../data_structures/suffixtree.h"
#include "../data_structures/trie.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <unordered_map>
using namespace std;

class BlockChain {
    private:
        struct Node {
            Block block;
            Node *next = nullptr;

            Node(Block _block) : block(_block) {};
        };

        Node* head = nullptr;
        vector<Block> forGUI; /// Vector of blocks for the GUI representation

        HashTable<string, Transaction> table;
        AVL<string, Transaction> tree;
        Trie trie;
        SuffixTree sTree;
        MaxHeap<string, Transaction> maxHeap;
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

        /// Construye el Trie
        void buildTrie(){
            trie.clear(); /// Reset trie

            Node* current = head;
            while(current != nullptr){
                trie.insert(current->block.getBlockhash());
                current = current->next;
            }
        }

        /// Construye el suffix tree
        void buildSuffixTree(){
            sTree.clear(); /// Reset suffix tree

            Node* current = head;
            while(current != nullptr){
                sTree.insert((current->block.getBlockhash()));
                current = current->next;
            }
        }

        /// Construye el MaxHeap
        void buildMaxHeap(){
            maxHeap.clear(); /// Reset max heap

            Node* current = head;
            while(current != nullptr){
                maxHeap.insert(current->block.getBlockhash(), current->block.getTransaction());
                current = current->next;
            }
        }

        /// Construye el MinHeap
        void buildMinHeap(){
            minHeap.clear(); /// Reset min heap

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
            return tree.search(begin, end);
        }

        /// Starts with X: Trie
        vector<Transaction> starts_with(const string& prefix){
            buildTrie();
            vector<string> hashes = trie.search(prefix);   /// Todos los hashes con el prefijo

            buildHashTable(); /// Busquedas O(1) con los hashes encontrados
            vector<Transaction> found;

            for(const auto& hash : hashes)
                found.push_back(table.search(hash));

            return found;
        }

        /// Contains X: Suffix Tree
        vector<Transaction> contains(const string& pattern){
            buildSuffixTree();
            vector<string> hashes = sTree.search(pattern); /// Todos los hashes con el patron

            buildHashTable(); /// Busquedas O(1) con los hashes encontrados
            vector<Transaction> found;

            for(const auto& hash : hashes)
                found.push_back(table.search(hash));

            return found;
        }

        /// Max value of: Max Heap
        Transaction max_value(){
            buildMaxHeap();
            return maxHeap.getMax();
        }

        /// Min value of: Min Heap
        Transaction min_value(){
            buildMinHeap();
            return minHeap.getMin();
        }

        void modifyTransaction(const string& hash, string newClient, double newAmount, string newLocation){
            Node* current = head;

            /// Recorrer la blockchain
            while (current != nullptr && current->block.getBlockhash() != hash)
                current = current->next;

            if(current != nullptr) {
                if (newClient.empty())
                    newClient = current->block.getTransaction().getClient();
                if (newAmount == 0.0)
                    newAmount = current->block.getTransaction().getAmount();
                if (newLocation.empty())
                    newLocation = current->block.getTransaction().getLocation();

                Transaction newTransaction(newClient, newLocation, newAmount);

                current->block.setTransaction(newTransaction);
            }
            else
                throw std::out_of_range("Block does not exist");
        }

        /// Calculo Transaccional : cantidad por cliente
        double calculateAmountPerClient(string client){
            double amount = 0;
            Node* current = head;

            while(current != nullptr){
                if(current->block.getTransaction().getClient() == client)
                    amount += current->block.getTransaction().getAmount();

                current = current->next;
            }

            return amount;
        }

        /// Calculo Transaccional : cantidad por lugar
        double calculateAmountPerLocation(string location){
            double amount = 0;
            Node* current = head;

            while(current != nullptr){
                if(current->block.getTransaction().getLocation() == location)
                    amount += current->block.getTransaction().getAmount();

                current = current->next;
            }

            return amount;
        }

        /// Calculo Transaccional : el cliente con mas plata
        string getRichestClient(){
            unordered_map<string, double> clientList;
            Node* current = head;

            /// Mapeando los clientes
            while(current != nullptr) {
                Transaction tr = current->block.getTransaction();
                if(tr.getAmount() > 0.0){
                    string client = tr.getClient();
                    double amount = tr.getAmount();
                    clientList[client] += amount;
                }

                current = current->next;
            }

            // Encontrar el cliente con mas plata
            string richest;
            double maxAmount = 0.0;

            for(auto entry : clientList){
                if(entry.second > maxAmount){
                    richest = entry.first;
                    maxAmount = entry.second;
                }
            }

            return richest;
        }

        /// Calculo Transaccional : el lugar con mas plata
        string getRichestLocation(){
            unordered_map<string, double> locationList;
            Node* current = head;

            /// Mapeando los clientes
            while(current != nullptr) {
                Transaction tr = current->block.getTransaction();
                if(tr.getAmount() > 0){
                    string location = tr.getLocation();
                    double amount = tr.getAmount();
                    locationList[location] += amount;
                }

                current = current->next;
            }

            // Encontrar el cliente con mas plata
            string richest;
            double maxAmount = 0.0;

            for(const auto& entry : locationList){
                if(entry.second > maxAmount){
                    richest = entry.first;
                    maxAmount = entry.second;
                }
            }

            return richest;
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

        /// Carga de datos por csv : TESTED
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

        vector<Block> constructGUIBlockVector(){
            forGUI.clear();
            Node* current = head;
            while(current != nullptr) {
                forGUI.push_back(current->block);
                current = current->next;
            }

            return forGUI;
        }

};

#endif //BLOCKCHAIN_H
