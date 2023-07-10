#ifndef BLOCK_H
#define BLOCK_H

#include "transaction.h"
#include <iomanip>
#include <string>
#include <sstream>
#include <openssl/sha.h>
using namespace std;

class Block{
    private:
        Transaction transaction;
        string blockHash;
        string prevHash;
        int nonce; /// Proof of Work Nonce
    public:
        Block(Transaction _transaction, string _prevHash): transaction(_transaction), prevHash(_prevHash){
            mineBlock();
        }

        string calculateHash() const{
            string data = transaction.getClient() + transaction.getLocation() + to_string(transaction.getAmount()) +
                    to_string(transaction.getDate()) + prevHash + to_string(nonce);
            unsigned char hash[SHA256_DIGEST_LENGTH];
            SHA256_CTX sha256;
            SHA256_Init(&sha256);
            SHA256_Update(&sha256, data.c_str(), data.length());
            SHA256_Final(hash, &sha256);

            /// Convertir a hexadecimal
            stringstream ss;
            ss << hex << setfill('0');
            for(unsigned char i : hash)
                ss << setw(2) << static_cast<unsigned int>(i);

            return ss.str();
        }

        /// Proof of Work
        void mineBlock(){
            nonce = 0; /// Reset Nonce
            string target(4, '0'); /// Difficulty = 4
            blockHash = calculateHash(); /// Reset the hash

            while(blockHash.substr(0, target.length()) != target){
                nonce++;
                blockHash = calculateHash();
            }
        }

        void setTransaction(const Transaction& _transaction){
            transaction = _transaction;
        }

        void setPrevHash(const string& _prevHash){
            prevHash = _prevHash;
        }

        string getBlockhash() const{
            return blockHash;
        }

        string getPrevhash() const{
            return prevHash;
        }

        Transaction getTransaction() const{
            return transaction;
        }

        void printBlock(){
            cout << "Nonce: " << nonce << endl;
            cout << "Hash del bloque: " << blockHash << endl;
            cout << "Hash previo: " << prevHash << endl;
            transaction.printTransaction();
        }

        ~Block() = default;
};

#endif //BLOCK_H