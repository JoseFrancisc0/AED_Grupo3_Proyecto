#ifndef BLOCK_H
#define BLOCK_H

#include "transaction.h"
#include <string>
#include <openssl/sha.h>
using namespace std;

class Block{
    private:
        Transaction transaction;
        string blockhash;
        string prevHash;
    public:
        Block(Transaction _transaction, string _prevHash): transaction(_transaction), prevHash(_prevHash){
            blockhash = calculateHash();
        }

        string calculateHash() const{
            string data = transaction.getSender() + transaction.getRecipient() + to_string(transaction.getAmount()) + prevHash;
            unsigned char hash[SHA256_DIGEST_LENGTH];
            SHA256_CTX sha256;
            SHA256_Init(&sha256);
            SHA256_Update(&sha256, data.c_str(), data.length());
            SHA256_Final(hash, &sha256);

            string hashString(reinterpret_cast<const char*>(hash), SHA256_DIGEST_LENGTH);
            return hashString;
        }

        ~Block() = default;
};

#endif //BLOCK_H